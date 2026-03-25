#pragma once

#include "t_rtos_mpu6050_config.h"
#include "sw/widget/rtos_widget.h"
#include "sw/ui_core/rtos_ui_core.h"
#include "t_rtos_mpu6050_main_classes.h"


class my_mpu_console_widget : public rtos_Widget
{
private:
    /* data */
public:
    my_mpu_console_widget(my_rtos_MPU6050Model *my_mpu);
    ~my_mpu_console_widget();

    void get_value_of_interest();
    void draw();
};