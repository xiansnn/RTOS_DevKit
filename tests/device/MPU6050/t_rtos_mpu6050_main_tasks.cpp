#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_main_classes.h"
#include "t_rtos_mpu6050_console_widget.h"

extern my_rtos_MPU6050Model mpu;
extern my_mpu_console_widget console_widget;
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
    if (probe != NULL)
        ((Probe *)probe)->hi();

    mpu.process_calibration();

    if (probe != NULL)
        ((Probe *)probe)->lo();

    while (true)
    {
        xSemaphoreTake(mpu.data_ready_semaphore, portMAX_DELAY);
        if (probe != NULL)
            ((Probe *)probe)->hi();

        mpu.get_measures();
        
        if (probe != NULL)
            ((Probe *)probe)->lo();

        mpu.notify_all_linked_widget_task();
    }
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
