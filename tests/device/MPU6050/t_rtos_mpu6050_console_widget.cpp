#include "t_rtos_mpu6050_console_widget.h"

#include <math.h>

my_mpu_console_widget::my_mpu_console_widget(MPU6050 *my_mpu)
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
    MPU6050 *mpu = (MPU6050 *)this->actual_rtos_displayed_model;
    struct_MPUData data = mpu->data;

    printf("Temp= %+3.1f\t Ax= %+3.2f\tAy= %+3.2f\tAz= %+3.2f",data.temp_out, data.g_x, data.g_y, data.g_z);
    printf("\tG-> %+3.2f", sqrt(pow(data.g_x, 2) + pow(data.g_y, 2) + pow(data.g_z, 2)));
    printf("\tGx= %+4.2f\tGy= %+4.2f\tGz= %+4.2f", data.gyro_x, data.gyro_y, data.gyro_z);
    printf("\n\n");

    /*
    print_raw_data()
    {
        my_rtos_MPU6050Model *mpu = (my_rtos_MPU6050Model *)this->actual_rtos_displayed_model;
        struct_RawData raw = mpu->raw;
        printf("Temp = %4x\tAcc [X = %4x\t\tY = %4x\t\tZ = %4x ]",raw.temp_out raw.g_x, raw.g_y, raw.g_z);
        printf("\t\t\tGyro [X = %4x\t\tY = %4x\t\tZ = %4x ]", raw.gyro_x, raw.gyro_y, raw.gyro_z);
        printf("\n\n");
    }
    */
}
