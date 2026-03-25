#include "t_rtos_mpu6050_main_classes.h"

#include <math.h>

extern rtos_HW_I2C_Master i2c_mpu_master;

void i2c_irq_handler()
{
    i2c_mpu_master.i2c_dma_isr();
};

struct_ConfigMasterI2C cfg_mpu6050_i2c{
    .i2c = i2c1,
    .sda_pin = 2,
    .scl_pin = 3,
    .baud_rate = I2C_STANDARD_MODE,
    .i2c_tx_master_handler = i2c_irq_handler};

struct_ConfigMPU6050 mpu_cfg{
    .SAMPLE_RATE_Hz = MPU_SAMPLE_RATE_Hz,
    .DLPF_BW = 5};

my_rtos_MPU6050Model::my_rtos_MPU6050Model(HW_I2C_Master *master, struct_ConfigMPU6050 default_config, int gpio_data_ready_irq, gpio_irq_callback_t data_ready_irq_call_back)
    : MPU6050(master, default_config, gpio_data_ready_irq, data_ready_irq_call_back), rtos_Model()
{
}

my_rtos_MPU6050Model::~my_rtos_MPU6050Model()
{
}
