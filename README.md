# stm32-freertos-gas-detection-system
Features  Real-time gas/smoke detection using ADC sensors  FreeRTOS task-based architecture  Alarm triggering (buzzer)  Automatic door/window opening using servo motors  SOS SMS alert via GSM module  Safety threshold monitoring  Non-blocking RTOS design  Queue-based inter-task communication

## Features
- Smoke detection using MQ2 gas sensor
- Real-time monitoring with FreeRTOS
- SMS emergency alert
- Automatic door/window opening
- Buzzer alarm
- 
**Hardware Components      Component	Purpose**
STM32 (F4 / F1 / F7)	    Main controller
MQ2 Gas Sensor	          Smoke/Gas detection
GSM Module (SIM800L)	    Send SOS SMS
Buzzer	                  Alarm
Servo Motor	              Open door/windows
ADC	                      Read gas sensor
UART	                    GSM communication
PWM	                      Servo control

**System Architecture**
_FreeRTOS Tasks_
+----------------------+
| GasSensorTask        |
| Reads ADC value      |
+----------+-----------+
           |
           v
+----------------------+
| SafetyMonitorTask    |
| Detects gas level    |
+----------+-----------+
           |
           v
+----------------+   +---------------+   +---------------+
| AlarmTask      |   | GSMTask       |   | ServoTask     |
| Activate buzzer|   | Send SOS SMS  |   | Open doors    |
+----------------+   +---------------+   +---------------+
_Communication via FreeRTOS Queue_

Gas Sensor (MQ2)
       │
       ▼
ADC Conversion
       │
       ▼
FreeRTOS GasTask
       │
       ▼
Queue → System Manager
       │
 ┌─────┼──────────────┐
 ▼     ▼              ▼
Alarm  GSM SMS       Servo Motors
                     (Door/Window)

## Hardware

- STM32F4
- MQ2 Gas Sensor
- SIM800L GSM Module
- Servo Motor
- Buzzer
