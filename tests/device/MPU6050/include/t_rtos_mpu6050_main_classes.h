#pragma once

#include "t_rtos_mpu6050_config.h"

#include "device/MPU6050/mpu6050.h"
#include "sw/ui_core/rtos_ui_core.h"



class my_rtos_MPU6050Model : public MPU6050, public rtos_Model
{
private:
    /* data */
public:
    my_rtos_MPU6050Model(HW_I2C_Master *master, struct_ConfigMPU6050 default_config, gpio_irq_callback_t call_back);
    ~my_rtos_MPU6050Model();
    void int_handle();

    void print_measures();
    void print_raw_data();
};
