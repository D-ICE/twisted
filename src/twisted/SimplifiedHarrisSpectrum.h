
#ifndef TWISTED_SIMPLIFIEDHARRISSPECTRUM_H
#define TWISTED_SIMPLIFIEDHARRISSPECTRUM_H

#include <iostream>
#include <random>
#include <math.h>

#include "twisted/WindSimulatorBase.h"


namespace twisted {

    class SimplifiedHarrisSpectrum : public WindSimulatorBase {

    protected:

        /// Random number Generator
        std::mt19937 randomGenerator;

        /// Buffer of Random phase numbers
        std::vector<double> m_PhaseRandomBuffer;

        /// Buffer of random pulsation number
        std::vector<double> m_PulsationRandomBuffer;

        /// indicates if the filter is initialized
        bool m_is_initialized;

        /// Minimal pulsation of spectral decomposition
        double m_omegaMin;
        /// Maximal pulsation of spectral decomposition
        double m_omegaMax;
        /// Pulsation delta of spectral decomposition
        double m_dOmega;

        /// Mean Speed Value in m/s
        double m_MeanWindSpeedValue;

        /// Mean Speed Saturated in m/s
        double m_MeanWindSpeedSaturated;

        /// Simulated Mean Speed Value in m/s
        double m_SimulatedWindSpeedValue;

        /// Turbulence Speed value in m/s
        double m_TurbulenceWindSpeedValue;

        /// Saturation for Mean Wind Speed Change
        double m_wind_speed_velocity_change_saturation;


    public:

        /// Constructors
        SimplifiedHarrisSpectrum();

        /// Constructor with more input parameters
        SimplifiedHarrisSpectrum(double wMin, double wMax, unsigned int windowSize, double ramp);

        /// Initialization
        void Initialize() override;

        /// Main Function
        void Update(double dt, double simulated_time, double meanWindSpeedValue) override;

        /// Return mean value
        double GetMeanValue() const override;

        /// Return current value
        double GetValue() const override;

        /// Return difference between mean and simulated value
        double GetDifference() const override;

        /// Return turbulence value
        double GetTurbulence() const override;


    };

    inline double SimplifiedHarrisSpectrum::GetMeanValue() const {
        return m_MeanWindSpeedValue;
    }

    inline double SimplifiedHarrisSpectrum::GetValue() const {
        return m_SimulatedWindSpeedValue;
    }

    inline double SimplifiedHarrisSpectrum::GetDifference() const {
        return m_MeanWindSpeedValue - m_SimulatedWindSpeedValue;
    }

    inline double SimplifiedHarrisSpectrum::GetTurbulence() const{
        return m_TurbulenceWindSpeedValue;
    }




    /// Saturate the input between min & max
    /// \param value is the value to be saturated
    /// \param value_min
    /// \param value_max
    /// \return
    template<typename T>
    T Saturate(T value, T value_min, T value_max){
        T out = fmin(value_max,value);
        out = fmax(value_min,out);
        return out;
    }
}

#endif //TWISTED_SIMPLIFIEDHARRISSPECTRUM_H
