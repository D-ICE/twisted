#include <math.h>
#include "twisted/SimplifiedHarrisSpectrum.h"

#define KNOTS_TO_METERS_PER_SECONDS 0.5144444444444444


namespace twisted {

/// Default Constructor
    SimplifiedHarrisSpectrum::SimplifiedHarrisSpectrum() :
            SimplifiedHarrisSpectrum(0.001, 1.0, 100, 2.) {
    }

/// Constructor with specification of min/max pulsation
    SimplifiedHarrisSpectrum::SimplifiedHarrisSpectrum(double wMin, double wMax, unsigned int windowSize, double ramp_up) :
            randomGenerator(84531942),
            m_omegaMin(wMin),
            m_omegaMax(wMax),
            m_MeanWindSpeedValue(0.),
            m_MeanWindSpeedSaturated(0.),
            m_wind_speed_velocity_change_saturation(ramp_up),
            m_is_initialized(false){
        m_PhaseRandomBuffer.resize(windowSize);
        m_PulsationRandomBuffer.resize(windowSize);
        m_dOmega = (wMax - wMin) / ((double) windowSize);

    }

/// Initialize
    void SimplifiedHarrisSpectrum::Initialize() {

        std::uniform_real_distribution<> distribPulsation(0., 1.0);
        std::uniform_real_distribution<> distribPhase(-M_PI, +M_PI);

        for (unsigned int iW = 0; iW < m_PulsationRandomBuffer.size(); iW++) {
            m_PhaseRandomBuffer[iW] = distribPhase(randomGenerator);
            m_PulsationRandomBuffer[iW] = (iW + 1 + distribPulsation(randomGenerator)) * m_dOmega;
        }
    }


/// Update the new Value
    void SimplifiedHarrisSpectrum::Update(double dt, double time, double meanWindSpeedValue) {
        m_MeanWindSpeedValue = meanWindSpeedValue;

        if (m_wind_speed_velocity_change_saturation>0. && m_is_initialized) {
            m_MeanWindSpeedSaturated = Saturate(m_MeanWindSpeedValue,
                                                           m_MeanWindSpeedSaturated -
                                                           dt * m_wind_speed_velocity_change_saturation,
                                                           m_MeanWindSpeedSaturated +
                                                           dt * m_wind_speed_velocity_change_saturation);

        }
        else {
            m_MeanWindSpeedSaturated = m_MeanWindSpeedValue;
            m_is_initialized = true;
        }

        double meanValueInKnot = m_MeanWindSpeedSaturated/KNOTS_TO_METERS_PER_SECONDS;

        double result_knot = 0;
        double spectrum = 0;
        double amplitude = 0;


        double Cd = 0.0035;
        double Lv = 1800;
        double A = 4.0 * Cd * Lv * (meanValueInKnot) / (pow(2.0, (5.0 / 6.0)));
        double B = pow(Lv, 2) / (8.0 * pow(M_PI * meanValueInKnot, 2));


        for (int iW = 0; iW < m_PulsationRandomBuffer.size(); iW++) {
            spectrum = A / pow((1.0 + B * pow(m_PulsationRandomBuffer[iW], 2)), (5.0 / 6.0));
            amplitude = sqrt(2.0 * spectrum * (m_dOmega)); // in knots
            result_knot += amplitude * cos(m_PulsationRandomBuffer[iW] * time + m_PhaseRandomBuffer[iW]);
        }

        m_TurbulenceWindSpeedValue = result_knot*KNOTS_TO_METERS_PER_SECONDS;

        m_SimulatedWindSpeedValue = m_MeanWindSpeedSaturated + m_TurbulenceWindSpeedValue;

    }
}
