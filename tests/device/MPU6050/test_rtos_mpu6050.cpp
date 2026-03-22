#include "t_rtos_mpu6050_config.h"

#include "hardware/gpio.h"
#include <stdio.h>

#include "t_rtos_mpu6050_main_classes.h"
#include "t_rtos_mpu6050_main_tasks.h"

Probe p0 = Probe(0);
Probe p1 = Probe(1);
Probe p4 = Probe(4);
Probe p5 = Probe(5);

extern struct_ConfigMasterI2C cfg_mpu6050_i2c;
extern struct_ConfigMPU6050 mpu_cfg;

void mpu_6050_data_ready_INT_callback(uint gpio, uint32_t events);
rtos_HW_I2C_Master i2c_mpu_master = rtos_HW_I2C_Master(cfg_mpu6050_i2c);
my_rtos_MPU6050Model mpu = my_rtos_MPU6050Model(&i2c_mpu_master, mpu_cfg, MPU_INT, mpu_6050_data_ready_INT_callback);

void mpu_6050_data_ready_INT_callback(uint gpio, uint32_t events)
{
    p1.hi();
    mpu.data_ready_isr();
    p1.lo();
}
int main()
{
    stdio_init_all();

    xTaskCreate(my_mpu_reading_task, "mpu_reading", 256, &p5, 5, NULL);

    xTaskCreate(idle_task, "idle_task", 256, &p0, 0, NULL);
    vTaskStartScheduler();

    while (true)
        tight_loop_contents();
}
