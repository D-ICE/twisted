//
// Created by camille on 10/09/2019.
//

#include <memory>
#include <fstream>
#include <iostream>
#include "twisted/SimplifiedHarrisSpectrum.h"


int main() {

    std::cout << " ====================================== Test : Harris spectrum ========================== " << std::endl;

    double meanWindSpeed = 40.;
    bool active_log = true;

    auto wind_simulator = std::make_shared<twisted::SimplifiedHarrisSpectrum>(0.05, 2.1, 100, 1.);
    wind_simulator->Initialize();

    double dt = 0.01;
    double time = 0.;

    std::ofstream myfile;
    myfile.open("WindGust.log");
    myfile << "time;MeanWindSpeed;WindSpeed;Delta;Turb;" << std::endl;
    myfile << "s;m/s;m/s;m/s;m/s;" << std::endl;

    while (time < 600.) {
        wind_simulator->Update(dt, time, meanWindSpeed);

        std::cout << "time : " << time << ";"
                  << "MeanWindSpeed : " << wind_simulator->GetMeanValue() << ";"
                  << "WindSpeed : " << wind_simulator->GetValue() << ";"
                  << "Diff : " << wind_simulator->GetDifference() << ";"
                  << "Turbulence : " << wind_simulator->GetTurbulence()
                  << std::endl;

        if (active_log) {
            myfile << time << ";" << wind_simulator->GetMeanValue()
                           << ";" << wind_simulator->GetValue()
                           << ";" << wind_simulator->GetDifference()
                           << ";" << wind_simulator->GetTurbulence()
                           << ";" << std::endl;
        }

        time += dt;
    }

    myfile.close();

    std::cout << " ================================================ End =================================== " << std::endl;
    return 0;
}
