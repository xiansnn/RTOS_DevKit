#include "t_rtos_mpu6050_console_widget.h"

#include <math.h>

my_mpu_console_widget::my_mpu_console_widget(my_rtos_MPU6050Model *my_mpu)
:rtos_Widget(my_mpu)
{
}

my_mpu_console_widget::~my_mpu_console_widget()
{
}

void my_mpu_console_widget::get_value_of_interest()
{
}

void my_mpu_console_widget::draw()
{
    my_rtos_MPU6050Model* mpu = (my_rtos_MPU6050Model*) this->actual_rtos_displayed_model;
    mpu->print_measures();
}
