#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_main_classes.h"

extern my_rtos_MPU6050Model mpu;
extern SemaphoreHandle_t data_ready_semaphore;
void mpu_6050_INT_callback(uint gpio, uint32_t events);

void my_mpu_reading_task(void *probe)
{
    while (true)
    {
        xSemaphoreTake(data_ready_semaphore,portMAX_DELAY););
        if (probe != NULL)
            ((Probe *)probe)->hi();
        struct_I2CXferResult result = mpu.get_measures();
        if (probe != NULL)
            ((Probe *)probe)->lo();
        if (result.error)
            printf("i2c error : %s \n", result.context.c_str());
        mpu.print_measures();
    }
}
