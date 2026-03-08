#pragma once

#include <cstdint>

/*-----------------------------------------------------------
 * SystemManager
 *
 * Responsible for evaluating system safety conditions
 * based on sensor inputs.
 *
 * In this system it determines whether the detected gas
 * level represents a dangerous situation.
 *
 * This class acts as a decision layer between:
 *
 *   Sensor Drivers  →  System Logic  →  Safety Actions
 *
 * Example actions triggered when danger is detected:
 *   - Activate alarm
 *   - Send SOS message via GSM
 *   - Open emergency ventilation (doors/windows)
 *----------------------------------------------------------*/
class SystemManager
{
public:

    /*-------------------------------------------------------
     * isDanger()
     *
     * Evaluates the gas sensor reading and determines
     * whether it exceeds the safety threshold.
     *
     * Parameters:
     *   gasLevel - ADC value representing gas concentration
     *
     * Returns:
     *   true  -> Dangerous gas level detected
     *   false -> Gas level within safe limits
     *
     * Note:
     * The threshold value is defined in the implementation
     * file and should be calibrated according to the sensor
     * characteristics.
     *------------------------------------------------------*/
    bool isDanger(uint16_t gasLevel);
};
