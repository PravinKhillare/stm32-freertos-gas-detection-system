#pragma once

/*-----------------------------------------------------------
 * Alarm Driver Interface
 *
 * This class provides an abstraction layer for controlling
 * an alarm device (buzzer, siren, or warning indicator)
 * connected to the microcontroller GPIO.
 *
 * The implementation typically drives a GPIO pin HIGH
 * to activate the alarm and LOW to deactivate it.
 *
 * Hardware configuration (GPIO port/pin setup) must be
 * completed during system initialisation (MX_GPIO_Init).
 *----------------------------------------------------------*/

class Alarm
{
public:

    /*-------------------------------------------------------
     * trigger()
     *
     * Activates the alarm output.
     * This usually sets the associated GPIO pin HIGH,
     * causing the buzzer or alarm indicator to turn ON.
     *
     * This function should be non-blocking and safe
     * to call from RTOS tasks.
     *------------------------------------------------------*/
    void trigger() noexcept;
};
