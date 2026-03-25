#include "t_rtos_mpu6050_console_widget.h"

#include <math.h>

my_mpu_console_widget::my_mpu_console_widget(my_rtos_MPU6050Model *my_mpu)
    : rtos_Widget(my_mpu)
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
    my_rtos_MPU6050Model *mpu = (my_rtos_MPU6050Model *)this->actual_rtos_displayed_model;
    struct_MPUData data = mpu->data;

    printf("AccX = %+.2f\tY = %+.2f\tZ = %+.2f", data.g_x, data.g_y, data.g_z);
    printf("\tvecteur G: %+.2f", sqrt(pow(data.g_x, 2) + pow(data.g_y, 2) + pow(data.g_z, 2)));
    printf("\tGyroX = %+.2f\tY = %+.2f\tZ = %+.2f", data.gyro_x, data.gyro_y, data.gyro_z);
    printf("\n\n");

    /*
    print_raw_data()
    {
        my_rtos_MPU6050Model *mpu = (my_rtos_MPU6050Model *)this->actual_rtos_displayed_model;
        struct_RawData raw = mpu->raw;
        printf("Acc [X = %4x\t\tY = %4x\t\tZ = %4x ]", raw.g_x, raw.g_y, raw.g_z);
        printf("\t\t\tGyro [X = %4x\t\tY = %4x\t\tZ = %4x ]", raw.gyro_x, raw.gyro_y, raw.gyro_z);
        printf("\n\n");
    }
    */
}
