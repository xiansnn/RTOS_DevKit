#include "t_rtos_mpu6050_main_classes.h"

#include <math.h>

struct_ConfigMasterI2C cfg_i2c{
    .i2c = i2c1,
    .sda_pin = 2,
    .scl_pin = 3,
    .baud_rate = I2C_STANDARD_MODE};

struct_ConfigMPU6050 mpu_cfg{
    .SAMPLE_RATE_Hz = MPU_SAMPLE_RATE_Hz,
    .DLPF_BW = 5};

my_rtos_MPU6050Model::my_rtos_MPU6050Model(HW_I2C_Master *master, struct_ConfigMPU6050 default_config, int gpio_data_ready_irq, gpio_irq_callback_t data_ready_irq_call_back)
    : MPU6050(master, default_config, gpio_data_ready_irq, data_ready_irq_call_back), rtos_Model()
{}

my_rtos_MPU6050Model::~my_rtos_MPU6050Model()
{
}


void my_rtos_MPU6050Model::print_measures()
{
    printf("AccX = %+.2f\tY = %+.2f\tZ = %+.2f", data.g_x, data.g_y, data.g_z);
    printf("\tvecteur G: %+.2f", sqrt(pow(data.g_x, 2) + pow(data.g_y, 2) + pow(data.g_z, 2)));
    printf("\tGyroX = %+.2f\tY = %+.2f\tZ = %+.2f", data.gyro_x, data.gyro_y, data.gyro_z);
    printf("\n\n");
}

void my_rtos_MPU6050Model::print_raw_data()
{
    printf("Acc [X = %4x\t\tY = %4x\t\tZ = %4x ]", raw.g_x, raw.g_y, raw.g_z);
    printf("\t\t\tGyro [X = %4x\t\tY = %4x\t\tZ = %4x ]", raw.gyro_x, raw.gyro_y, raw.gyro_z);
    printf("\n\n");
}
