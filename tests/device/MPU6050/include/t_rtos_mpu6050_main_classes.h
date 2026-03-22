#pragma once

#include "t_rtos_mpu6050_config.h"

#include "device/MPU6050/mpu6050.h"
#include "sw/ui_core/rtos_ui_core.h"

class my_rtos_MPU6050Model : public MPU6050, public rtos_Model
{
private:

public:
    my_rtos_MPU6050Model(HW_I2C_Master *i2c_mpu_master, struct_ConfigMPU6050 default_config, int gpio_data_ready_irq, gpio_irq_callback_t data_ready_irq_call_back);
    ~my_rtos_MPU6050Model();

    void print_measures();
    void print_raw_data();
};
