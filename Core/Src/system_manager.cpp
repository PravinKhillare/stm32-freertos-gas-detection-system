#include "system_manager.hpp"

/*-----------------------------------------------------------
 * System Safety Configuration
 *----------------------------------------------------------*/

// Gas level threshold for triggering danger condition
// This value should be calibrated according to sensor
// characteristics and safety requirements.
constexpr int GAS_DANGER_THRESHOLD = 700;

/*-----------------------------------------------------------
 * SystemManager::isDanger()
 *
 * Determines whether the current gas level represents
 * a dangerous condition.
 *
 * Parameters:
 *   gasLevel - Measured gas concentration value
 *              from ADC or sensor driver.
 *
 * Returns:
 *   true  -> Gas level exceeds safety threshold
 *   false -> Gas level is within safe limits
 *
 * Note:
 * The threshold value should be adjusted based on
 * sensor calibration and environmental conditions.
 *----------------------------------------------------------*/
bool SystemManager::isDanger(int gasLevel)
{
    return gasLevel > GAS_DANGER_THRESHOLD;
}
