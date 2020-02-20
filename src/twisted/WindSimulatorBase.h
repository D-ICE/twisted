//
// Created by camille on 11/09/2019.
//

#ifndef TWISTED_WINDSIMULATORBASE_H
#define TWISTED_WINDSIMULATORBASE_H

namespace twisted {
    /**
     * This class defined the basis structure of the spectrum classes.
     * It contains pure virtual methods which must be defined in the child classes.
     */
    class WindSimulatorBase {

    public:
        /// Default constructor
        WindSimulatorBase() = default;

        /// This method contains all functions which will be applied during the initialization stage
        virtual void Initialize() = 0;

        /// This method contains all functions which will be applied during the update
        virtual void Update(double dt, double simulated_time, double meanWindSpeedValue) = 0;

        /// Return the mean value of the time series
        virtual double GetMeanValue() const = 0;

        /// Return the instantaneous value of the time series
        virtual double GetValue() const = 0;

        /// Return the difference between mean and simulated value
        virtual double GetDifference() const = 0;

        /// Return turbulence value
        virtual double GetTurbulence() const = 0;
    };


}

#endif //TWISTED_WINDSIMULATORBASE_H
