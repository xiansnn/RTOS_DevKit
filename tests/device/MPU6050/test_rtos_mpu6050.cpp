#include "t_rtos_mpu6050_config.h"

#include "hardware/gpio.h"
#include <stdio.h>

#include "t_rtos_mpu6050_main_classes.h"
#include "t_rtos_mpu6050_main_tasks.h"

Probe p0 = Probe(0);
Probe p1 = Probe(1);
Probe p4 = Probe(4);
Probe p5 = Probe(5);

extern struct_ConfigMasterI2C cfg_i2c;
extern struct_ConfigMPU6050 mpu_cfg;

SemaphoreHandle_t data_ready_semaphore = xSemaphoreCreateBinary();

void mpu_6050_INT_callback(uint gpio, uint32_t events);
HW_I2C_Master master = HW_I2C_Master(cfg_i2c);
my_rtos_MPU6050Model mpu = my_rtos_MPU6050Model(&master, mpu_cfg, mpu_6050_INT_callback);

void mpu_6050_INT_callback(uint gpio, uint32_t events)
{
    p1.hi();
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_FALL, false);
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(data_ready_semaphore,&pxHigherPriorityTaskWoken);
    gpio_set_irq_enabled(gpio, GPIO_IRQ_EDGE_FALL, true);
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
