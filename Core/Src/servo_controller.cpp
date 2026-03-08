#include "servo_controller.hpp"
#include "stm32f4xx_hal.h"

/*-----------------------------------------------------------
 * External Timer Handle
 *
 * Defined in STM32CubeMX generated code (tim.c).
 * TIM1 is used to generate PWM signals for servo motors.
 *----------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;

/*-----------------------------------------------------------
 * Hardware Configuration
 *----------------------------------------------------------*/

// PWM channels controlling actuators
#define DOOR_SERVO_CHANNEL    TIM_CHANNEL_1
#define WINDOW_SERVO_CHANNEL  TIM_CHANNEL_2

// PWM compare value corresponding to "open position"
// (Value depends on timer configuration and servo calibration)
constexpr uint16_t SERVO_OPEN_POSITION = 200;

/*-----------------------------------------------------------
 * ServoController::openDoors()
 *
 * Sets PWM duty cycle to move door servo to the OPEN position.
 *
 * Operation:
 * - Updates PWM compare value for TIM1 Channel 1
 * - Servo rotates to predefined open angle
 *
 * Note:
 * Timer PWM must already be started using:
 * HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1)
 *----------------------------------------------------------*/
void ServoController::openDoors()
{
    __HAL_TIM_SET_COMPARE(&htim1, DOOR_SERVO_CHANNEL, SERVO_OPEN_POSITION);
}

/*-----------------------------------------------------------
 * ServoController::openWindows()
 *
 * Sets PWM duty cycle to move window servo to the OPEN position.
 *
 * Operation:
 * - Updates PWM compare value for TIM1 Channel 2
 * - Servo rotates to predefined open angle
 *
 * Note:
 * Timer PWM must already be started using:
 * HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2)
 *----------------------------------------------------------*/
void ServoController::openWindows()
{
    __HAL_TIM_SET_COMPARE(&htim1, WINDOW_SERVO_CHANNEL, SERVO_OPEN_POSITION);
}
