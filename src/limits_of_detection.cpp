#include "limits_of_detection/limits_of_detection.hpp"
#include <cmath>
#include <boost/math/distributions/normal.hpp>
#include <iostream>
#include <stdexcept>

namespace LOD {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float calculateActivityLLD(float detector_surface_area, float LLD){
    return (detector_surface_area*LLD)/60.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float calculateDwellTime(float activityLLD, float efficiency, float relative_std){
    if (efficiency <= 0.0f || efficiency >= 1.0f)
    {
        throw std::invalid_argument("[calculateDwellTime()]: 'efficiency' parameter is outside of the acceptable range, (0-1)");
    }
    return 1 / (activityLLD * efficiency * std::pow(relative_std,2));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float calculateDetectorVelocity(float activityLLD, float efficiency, float detector_length, float relative_std){
    if (efficiency <= 0.0f || efficiency >= 1.0f)
    {
        throw std::invalid_argument("[calculateDetectorVelocity()]: 'efficiency' parameter is outside of the acceptable range, (0-1)");
    }

    if (relative_std <= 0.0f || relative_std >= 1.0f)
    {
        throw std::invalid_argument("[calculateDetectorvelocity()]: 'relative_std' parameter is outside of the acceptable range, (0-1)");
    }
    return (activityLLD * efficiency * detector_length* std::pow(relative_std,2));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float calculateLC(float alpha, float bckg_count_rate, float bckg_count_time){
    if (alpha < 0.0f || alpha >= 50.0f)
    {
        throw std::invalid_argument("[calculateLC()]: 'alpha' parameter is outside of the acceptable range, [0-50)");
    }

    if (bckg_count_rate < 0.0f)
    {
        throw std::invalid_argument("[calculateLC()]: 'bckg_count_rate' parameter can't be negative");
    }

    if (bckg_count_time < 0.0f)
    {
        throw std::invalid_argument("[calculateLC()]: 'bckg_count_time' parameter can't be negative");
    }

    const boost::math::normal_distribution<> norm_dist(0.0, 1.0);
    const double K_alpha = std::abs(boost::math::quantile(norm_dist, alpha/100.0f));

    return bckg_count_rate + (K_alpha * sqrt(bckg_count_rate/bckg_count_time));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float calculateLD(float Lc, float alpha, float beta, float measured_dwell_time){
    if (alpha < 0.0f || alpha >= 50.0f)
    {
        throw std::invalid_argument("[calculateLD()]: 'alpha' parameter is outside of the acceptable range, [0-50)");
    }

    if (beta < 0.0f || beta >= 50.0f)
    {
        throw std::invalid_argument("[calculateLD()]: 'beta' parameter is outside of the acceptable range, [0-50)");
    }

    if (measured_dwell_time < 0.0f)
    {
        throw std::invalid_argument("[calculateLD()]: 'measured_dwell_time' parameter can't be negative");
    }

    const boost::math::normal_distribution<> norm_dist(0.0, 1.0);
    const double K_alpha = std::abs(boost::math::quantile(norm_dist, alpha/100.0f));
    const double K_beta = std::abs(boost::math::quantile(norm_dist, beta/100.0f));

    // Terms (first, second.....) used in calculating the Limit of Detection
    const float first = (std::pow(K_beta,2))/2.0f;
    const float second_third = 1.0f/measured_dwell_time;   // same term is used in the second and third
    const float fourth = (4.0f*Lc) / ( (std::pow(K_beta,2)) * measured_dwell_time);
    const float fifth = ( 4.0f*(std::pow(Lc,2)) ) / ((std::pow(K_alpha*K_beta,2)) );

    return Lc + first * (second_third + sqrt(second_third + fourth + fifth));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}   // LOD namespace
