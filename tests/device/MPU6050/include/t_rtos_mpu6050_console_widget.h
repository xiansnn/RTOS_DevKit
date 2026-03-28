#pragma once

#include "t_rtos_mpu6050_config.h"
#include "sw/widget/rtos_widget.h"



class my_mpu_console_widget : public rtos_Widget
{
private:
    /* data */
public:
    my_mpu_console_widget(MPU6050 *my_mpu);
    ~my_mpu_console_widget();

    void get_value_of_interest();
    void draw();
};