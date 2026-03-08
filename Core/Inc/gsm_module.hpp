#pragma once

#include <string>

/*-----------------------------------------------------------
 * GSMModule Driver Interface
 *
 * Provides an abstraction for communicating with a GSM
 * modem (e.g., SIM800 / SIM900) using AT commands over UART.
 *
 * Responsibilities:
 * - Send SMS alerts
 * - Communicate with GSM modem
 * - Trigger emergency notifications
 *
 * The implementation typically uses UART HAL drivers
 * (e.g., HAL_UART_Transmit) to send AT commands.
 *
 * Note:
 * GSM module must be powered, initialized, and registered
 * to the cellular network before sending messages.
 *----------------------------------------------------------*/
class GSMModule
{
public:

    /*-------------------------------------------------------
     * sendSOS()
     *
     * Sends an emergency SMS message using the GSM modem.
     *
     * Parameters:
     *   message - Text message to send via SMS.
     *
     * Operation:
     *   AT+CMGF=1             -> Enable SMS text mode
     *   AT+CMGS=\"<number>\"   -> Specify recipient
     *   <message>              -> SMS body
     *   CTRL+Z                -> Send message
     *
     * This function should be non-blocking when used
     * in RTOS environments or executed within a dedicated
     * communication task.
     *------------------------------------------------------*/
    void sendSOS(const std::string& message) noexcept;
};
