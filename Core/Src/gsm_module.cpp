#include "gsm_module.hpp"
#include "stm32f4xx_hal.h"

#include <cstring>

/*-----------------------------------------------------------
 * External UART handle
 * Defined in STM32CubeMX generated code
 *----------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

/*-----------------------------------------------------------
 * GSM AT Command Configuration
 *----------------------------------------------------------*/

// Destination phone number for SOS
constexpr const char* SOS_PHONE_NUMBER = "+911234567890";

// Control character to end SMS message
constexpr uint8_t CTRL_Z = 0x1A;

/*-----------------------------------------------------------
 * Helper Function
 *
 * Sends a null-terminated string over UART.
 *----------------------------------------------------------*/
static HAL_StatusTypeDef sendUART(const char* data)
{
    return HAL_UART_Transmit(
        &huart2,
        reinterpret_cast<uint8_t*>(const_cast<char*>(data)),
        strlen(data),
        1000
    );
}

/*-----------------------------------------------------------
 * GSMModule::sendSOS()
 *
 * Sends an SMS message using GSM module (SIM800/SIM900 etc.)
 *
 * Steps:
 * 1. Set SMS mode to text
 * 2. Set destination phone number
 * 3. Send message body
 * 4. Send CTRL+Z to transmit message
 *
 * Example AT sequence:
 *   AT+CMGF=1
 *   AT+CMGS="+911234567890"
 *   <message>
 *   CTRL+Z
 *
 * Note:
 * GSM module must be initialized and registered
 * to network before calling this function.
 *----------------------------------------------------------*/
void GSMModule::sendSOS(const std::string& message)
{
    char commandBuffer[64];

    /* Set GSM module to SMS text mode */
    sendUART("AT+CMGF=1\r\n");

    /* Configure destination phone number */
    snprintf(commandBuffer, sizeof(commandBuffer),
             "AT+CMGS=\"%s\"\r\n", SOS_PHONE_NUMBER);

    sendUART(commandBuffer);

    /* Send SMS message content */
    HAL_UART_Transmit(
        &huart2,
        (uint8_t*)message.c_str(),
        message.length(),
        1000
    );

    /* Send CTRL+Z to transmit SMS */
    HAL_UART_Transmit(&huart2, (uint8_t*)&CTRL_Z, 1, 1000);
}
