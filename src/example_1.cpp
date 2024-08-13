#include <iostream>
#include "limits_of_detection.hpp"

// Example Program for calculating the limits of detection.  This script assumes it is using the ludlum air proportional detector
// that is currently on Magni.  LLD is LANL's LLD.  rsd, alpha, and beta, is user specified. Lastly, it is using background radiation
// data that was recorded for about an hour in the NRG lab.

int main() {

    // Parameters
    float e = 0.07;
    float SA_d =  1023;
    float l_d = 23.39;
    float LLD = 100/100;

    float rsd = 0.3;
    float alpha = 49;
    float beta = 49;

    float t_b = 3627.1;
    float bckg_counts = 541;
    float bckg_count_rate = bckg_counts/ t_b;

    // Outputs
    float t_dwell;
    float t_dm;
    float v;
    float Lc;
    float Ld;

    float activityLLD = LOD::calculateActivityLLD(SA_d, LLD);

    t_dwell = LOD::calculateDwellTime(activityLLD, e, rsd);
    std::cout << "Dwell Time: " << t_dwell << std::endl;

    v = LOD::calculateDetectorVelocity(activityLLD, e, l_d, rsd);
    std::cout << "Detector Velocity: " << v << std::endl;

    Lc = LOD::calculateLC(alpha, bckg_count_rate, t_b);
    std::cout << "Critical Limit (LC): " << Lc << std::endl;

    Ld = LOD::calculateLD(Lc, alpha, beta, t_dwell);
    std::cout << "Detection Limit (LD): " << Ld << std::endl;

    return 0;
}
