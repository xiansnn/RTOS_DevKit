add_executable(test_rtos_mpu6050_irq   test_rtos_mpu6050.cpp
            t_rtos_mpu6050_main_tasks.cpp
            t_rtos_mpu6050_console_widget.cpp
            t_rtos_mpu6050_control.cpp
            t_rtos_mpu6050_main_classes.cpp
               )
include_directories(test_rtos_mpu6050_irq PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include  )
target_link_libraries(test_rtos_mpu6050_irq 
            pico_stdlib 
            device_mpu6050 
            rtos_ui_core 
            rtos_hw_i2c
            rtos_widget
            device_rtos_switch_button
            FreeRTOS-Kernel-Heap4 
            utilities_probe
            )