#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_main_classes.h"

extern my_rtos_MPU6050Model mpu;
void mpu_6050_data_ready_INT_callback(uint gpio, uint32_t events);

void idle_task(void *probe)
{
    while (true)
    {
        if (probe != NULL)
        {
            ((Probe *)probe)->hi();
            ((Probe *)probe)->lo();
        }
    }
}

void my_mpu_reading_task(void *probe)
{
    mpu.calibrate();

    while (true)
    {
        xSemaphoreTake(mpu.data_ready_semaphore, portMAX_DELAY);
        if (probe != NULL)
            ((Probe *)probe)->hi();
        mpu.get_measures();
        if (probe != NULL)
            ((Probe *)probe)->lo();

        if (probe != NULL)
            ((Probe *)probe)->hi();
        mpu.print_measures();
        if (probe != NULL)
            ((Probe *)probe)->lo();
    }
}
