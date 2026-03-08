cmake_minimum_required(VERSION 3.20)

project(GasDetectionSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    gas_detection
    Core/Src/main.cpp
    Core/Src/gas_sensor.cpp
    Core/Src/alarm.cpp
    Core/Src/gsm_module.cpp
    Core/Src/servo_controller.cpp
    Core/Src/system_manager.cpp
)
