#include "gas_sensor.hpp"
#include "stm32f4xx_hal.h"   // Adjust depending on MCU family

// External ADC handle defined in HAL initialization
extern ADC_HandleTypeDef hadc1;

/*-----------------------------------------------------------
 * Constructor
 *
 * Initializes gas sensor hardware interface.
 * ADC peripheral initialization is assumed to be done
 * during system startup (MX_ADC_Init or BSP init).
 *----------------------------------------------------------*/
GasSensor::GasSensor()
{
    // No initialization required here if ADC is already
    // configured during system startup.
}

/*-----------------------------------------------------------
 * readGasLevel()
 *
 * Reads gas sensor analog value using ADC.
 *
 * Steps:
 * 1. Start ADC conversion
 * 2. Wait for conversion completion
 * 3. Read converted digital value
 *
 * Returns:
 * ADC converted value (typically 0–4095 for 12-bit ADC)
 *----------------------------------------------------------*/
uint16_t GasSensor::readGasLevel()
{
    uint16_t gasValue = 0;

    /* Start ADC conversion */
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
        return 0; // ADC start failed
    }

    /* Wait for conversion to complete */
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK)
    {
        return 0; // Conversion timeout/failure
    }

    /* Read ADC converted value */
    gasValue = static_cast<uint16_t>(HAL_ADC_GetValue(&hadc1));

    return gasValue;
}
