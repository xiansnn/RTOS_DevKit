#pragma once
#include "t_rtos_mpu6050_config.h"
#include "device/switch_button/rtos_switch_button.h"
#include "sw/ui_core/rtos_ui_core.h"


class my_mpu6050_controller : public rtos_UIControlledModel
{
private:
    MPU6050 * controlled_mpu;
public:
    my_mpu6050_controller(MPU6050* my_mpu);
    ~my_mpu6050_controller();

    void process_control_event(struct_ControlEventData control_event);
};