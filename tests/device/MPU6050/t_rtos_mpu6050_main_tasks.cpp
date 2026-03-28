#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_console_widget.h"

extern MPU6050 mpu;
extern my_mpu_console_widget console_widget;
void mpu_6050_DATA_READY_INT_callback(uint gpio, uint32_t events);

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

void mpu_process_measures_task(void *probe)
{
    if (probe != NULL)
        ((Probe *)probe)->hi();
    mpu.process_measures_task(probe);
    if (probe != NULL)
        ((Probe *)probe)->lo();
}

void my_mpu_printing_task(void *probe)
{
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (probe != NULL)
            ((Probe *)probe)->hi();
        console_widget.draw();
        if (probe != NULL)
            ((Probe *)probe)->lo();
    }
}