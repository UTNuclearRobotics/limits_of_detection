#ifndef LIMITS_OF_DETECTION_H
#define LIMITS_OF_DETECTION_H

namespace LOD {

//////////////////
//   Functions  //   
//////////////////

/**
 * @brief Calculates the activity from the LLD.
 *
 * Calculates the activity level that is deemed as a detection from the LLD. The LLD is generalized for any detector size. This function multiplies the LLD and the detector's detection surface area. Lastly, it converts DPM to DPS.
 * 
 * @param[in] detector_surface_area [float] The detector's detection surface area. Units: (cm^2)
 * @param[in] LLD [float] Facility Detection Policy, or in other words, the Lower Limit of Detection. Units: (DPM/cm^2)
 * 
 * @return [float] Activity level that is deemed as a detection using a detector with a specified size. Units: (DPS)
 */
float calculateActivityLLD(float detector_surface_area, float LLD);




/**
 * @brief Calculates the Dwell Time.
 *
 * Calculates the minimum dwell time for a detector to appropriately assess whether the surface is contaminated. This time satisfies the relative std requirement.
 * @param[in] activityLLD [float] Activity level that is deemed as a detection using a detector with a specified size. Units: (DPS)
 * @param[in] efficiency [float] The detector's detection efficiency. Range: (0-1).
 * @param[in] relative_std [float] The relative standard deviation, user-defined. Range: (0-1).  Values closer to 0 represent a precise measurement while values closer to 1 represent an imprecise measurement.
 * 
 * @return [float] Dwell time, the minimum amount of time required to dwell over a surface. Units: (s)]
 * 
 * @throws std::invalid_argument: The 'efficiency' parameter has to be within the range of (0-1)
 * 
 * @note TODO:Additional notes or remarks about the function.
 * @warning TODO:Any warnings or important considerations.
 */
float calculateDwellTime(float activityLLD, float efficiency, float relative_std);



/**
 * @brief Calculates the detector velocity.
 *
 * Calculates the detector velocity required to appropriately assess whether the surface is contaminated. This velocity satisfies the relative_std. Calculated using the dwell time and detector length. Units: (cm/s)
 * 
 * @param[in] activityLLD [float] Activity level that is deemed as a detection using a detector with a specified size. Units: (DPS)
 * @param[in] efficiency [float] The detector's detection efficiency. Range: (0-1).
 * @param[in] detector_length [float] The length of the detector. Units: (cm)
 * @param[in] relative_std [float] The relative standard deviation, user-defined. Range: (0-1).  Values closer to 0 represent a precise measurement while values closer to 1 represent an imprecise measurement.
 * 
 * @return [float] Ideal detector velocity.
 * 
 * @throws std::invalid_argument: The 'efficiency' parameter has to be within the range of (0-1)
 * @throws std::invalid_argument: The 'relative_std' parameter has to be within the range of (0-1)
 */
float calculateDetectorVelocity(float activityLLD, float efficiency, float detector_length, float relative_std); 



/**
 * @brief Calculates the Critical Limit
 *
 * Calculates the critical limit of detection. This limit is used to assess a potential contaminated surface, however might be a fluke due to radiation and its probabilistic nature. 
 * 
 * @param[in] alpha [float] Confidence user-defined parameter that considers false positive counts. Range: [0-50].
 * @param[in] bckg_count_rate [float] The room's background count rate. Units: (cps)
 * @param[in] bckg_count_time [float] The room's time used for calculating the background count rate. Units: (s).  A longer count time creates a more precise background count rate.
 * 
 * @return [float] The critical limit used for assessing a surface as potentially contaminated. Think of it as the first red flag. Units: (cps)
 * 
 * @throws std::invalid_argument: The 'alpha' parameter has to be within the range of [0-50)
 * @throws std::invalid_argument: The 'bckg_count_rate' parameter can't be negative
 * @throws std::invalid_argument: The 'bckg_count_time' parameter can't be negative
 * 
 */
float calculateLC(float alpha, float bckg_count_rate, float bckg_count_time);



/**
 * @brief Calculates the Detection Limit
 *
 * Calculates the detection limit. A surface with a count rate above this limit will be deemed as contaminated.
 * 
 * @param[in] Lc [float] The critical limit used for assessing a surface as potentially contaminated. Think of it as the first red flag. Units: (cps)
 * @param[in] alpha [float] Confidence user-defined parameter that considers false positive counts. Range: [0-50].
 * @param[in] beta [float] Confidence user-defined parameter that considers false negative counts. Range: [0-50].
 * @param[in] measured_dwell_time [float] The time spent over a surface. Different than the dwell time, since dwell time is a recommnded time, while this is a active measurement. Units: (s)
 * 
 * @return [float] A detection limit that marks the count rate at which a surface will be considered contaminated. Units: (cps)
 * 
 * @throws std::invalid_argument: The 'alpha' parameter has to be within the range of [0-50)
 * @throws std::invalid_argument: The 'beta' parameter has to be within the range of [0-50)
 * @throws std::invalid_argument: The 'measured_dwell_time' value can't be negative
 * 
 */
float calculateLD(float Lc, float alpha, float beta, float measured_dwell_time);


}   // LOD namespace

#endif // LIMITS_OF_DETECTION_H
