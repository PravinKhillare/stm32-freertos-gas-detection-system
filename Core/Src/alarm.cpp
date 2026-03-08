#include "alarm.hpp"
#include "stm32f4xx_hal.h"   // Adjust depending on MCU family

/*-----------------------------------------------------------
 * Hardware Configuration
 *----------------------------------------------------------*/

// GPIO port and pin connected to the alarm/buzzer
#define ALARM_GPIO_PORT   GPIOB
#define ALARM_GPIO_PIN    GPIO_PIN_0

/*-----------------------------------------------------------
 * Alarm::trigger()
 *
 * Activates the alarm output.
 * This typically drives a buzzer or warning indicator.
 *
 * Operation:
 * - Sets GPIO pin HIGH
 * - Alarm remains active until explicitly cleared
 *
 * Note:
 * GPIO must be configured as OUTPUT during system
 * initialization (usually in MX_GPIO_Init()).
 *----------------------------------------------------------*/
void Alarm::trigger()
{
    HAL_GPIO_WritePin(ALARM_GPIO_PORT, ALARM_GPIO_PIN, GPIO_PIN_SET);
}
