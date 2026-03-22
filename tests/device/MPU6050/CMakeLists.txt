# add_executable(test_mpu6050   test_mpu6050.cpp   )
# target_link_libraries(test_mpu6050 
#             pico_stdlib 
#             device_mpu6050 
#             hw_i2c 
#             utilities_probe
#             )
# #-------------------------------------------------------------------------------------
add_executable(test_mpu6050_irq   test_mpu6050_irq.cpp   )
target_link_libraries(test_mpu6050_irq 
            pico_stdlib 
            device_mpu6050  
            hw_i2c 
            utilities_probe
            )
#-------------------------------------------------------------------------------------
add_executable(test_rtos_mpu6050_irq   test_rtos_mpu6050.cpp
            t_rtos_mpu6050_main_classes.cpp
            t_rtos_mpu6050_main_tasks.cpp
               )
include_directories(test_rtos_mpu6050_irq PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include  )
target_link_libraries(test_rtos_mpu6050_irq 
            pico_stdlib 
            device_mpu6050 
            rtos_ui_core 
            rtos_hw_i2c 
            FreeRTOS-Kernel-Heap4 
            utilities_probe
            )