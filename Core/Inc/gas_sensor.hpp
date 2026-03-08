#pragma once

#include "stm32f4xx_hal.h"
#include <cstdint>

/*-----------------------------------------------------------
 * GasSensor
 *
 * Driver class is responsible for reading gas sensor values
 * using the MCU ADC peripheral.
 *
 * The ADC peripheral is assumed to be initialised during
 * system startup (typically via STM32CubeMX generated code).
 *
 * Hardware Layer:
 *   Gas Sensor -> Analog Signal -> ADC Peripheral
 *----------------------------------------------------------*/
class GasSensor
{
public:

    /*-------------------------------------------------------
     * Constructor
     *
     * Initialises the gas sensor driver. The ADC peripheral
     * must already be configured before creating this object.
     *------------------------------------------------------*/
    GasSensor();

    /*-------------------------------------------------------
     * readGasLevel()
     *
     * Performs an ADC conversion and returns the measured
     * gas level from the sensor.
     *
     * Returns:
     *   ADC digital value (typically 0–4095 for 12-bit ADC)
     *------------------------------------------------------*/
    uint16_t readGasLevel();

private:

    /*-------------------------------------------------------
     * ADC Handle
     *
     * Reference to the ADC peripheral used for sensor reading.
     * The handle is defined in STM32 HAL initialization code.
     *------------------------------------------------------*/
    ADC_HandleTypeDef* adcHandle;
};
