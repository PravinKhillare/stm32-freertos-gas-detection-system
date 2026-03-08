#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "gas_sensor.hpp"
#include "alarm.hpp"
#include "gsm_module.hpp"
#include "servo_controller.hpp"
#include "system_manager.hpp"

/*-----------------------------------------------------------
 * Configuration Constants
 *----------------------------------------------------------*/

constexpr uint16_t GAS_THRESHOLD = 700;      // Smoke detection threshold
constexpr uint8_t  GAS_QUEUE_LENGTH = 10;    // Queue capacity
constexpr uint32_t SENSOR_PERIOD_MS = 500;   // Sensor sampling interval

/*-----------------------------------------------------------
 * Global FreeRTOS Objects
 *----------------------------------------------------------*/

// Queue used to transfer gas sensor data between tasks
static QueueHandle_t gasQueue = nullptr;

/*-----------------------------------------------------------
 * Hardware Interface Objects
 *----------------------------------------------------------*/

static GasSensor       gasSensor;
static Alarm           alarm;
static GSMModule       gsm;
static ServoController servo;

/*-----------------------------------------------------------
 * Task: GasSensorTask
 *
 * Periodically reads gas level from sensor and sends
 * the value to the system task via a queue.
 *----------------------------------------------------------*/

void GasSensorTask(void *arg)
{
    (void)arg; // unused parameter

    uint16_t gasLevel = 0;

    for (;;)
    {
        /* Read gas concentration from sensor */
        gasLevel = gasSensor.readGasLevel();

        /* Send value to queue (blocks if queue full) */
        xQueueSend(gasQueue, &gasLevel, portMAX_DELAY);

        /* Delay until next sensor sampling cycle */
        vTaskDelay(pdMS_TO_TICKS(SENSOR_PERIOD_MS));
    }
}

/*-----------------------------------------------------------
 * Task: SystemTask
 *
 * Receives gas levels from queue and performs actions
 * when threshold is exceeded.
 *----------------------------------------------------------*/

void SystemTask(void *arg)
{
    (void)arg;

    uint16_t gasLevel = 0;

    for (;;)
    {
        /* Wait for new gas sensor data */
        if (xQueueReceive(gasQueue, &gasLevel, portMAX_DELAY) == pdPASS)
        {
            /* Check if smoke/gas exceeds threshold */
            if (gasLevel > GAS_THRESHOLD)
            {
                /* Trigger safety mechanisms */

                alarm.trigger();                         // Activate alarm
                gsm.sendSOS("Smoke detected in room!");  // Send emergency message

                servo.openDoors();                       // Open doors
                servo.openWindows();                     // Open windows
            }
        }
    }
}

/*-----------------------------------------------------------
 * System Initialization
 *----------------------------------------------------------*/

int main(void)
{
    /* Create queue for gas sensor readings */
    gasQueue = xQueueCreate(GAS_QUEUE_LENGTH, sizeof(uint16_t));

    configASSERT(gasQueue != nullptr); // Ensure queue creation succeeded

    /* Create Gas Sensor Task */
    BaseType_t status;

    status = xTaskCreate(
        GasSensorTask,
        "GasSensorTask",
        512,
        nullptr,
        2,
        nullptr
    );

    configASSERT(status == pdPASS);

    /* Create System Control Task */
    status = xTaskCreate(
        SystemTask,
        "SystemTask",
        512,
        nullptr,
        3,  // Higher priority for safety logic
        nullptr
    );

    configASSERT(status == pdPASS);

    /* Start FreeRTOS Scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for (;;)
    {
    }
}
