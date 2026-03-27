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

void my_mpu_process_measures_task(void *probe)
{
    mpu.is_data_ready(); // reset Data ready IRQ

    while (true)
    {
        xSemaphoreTake(mpu.data_ready_semaphore, portMAX_DELAY);
        switch (mpu.calibration_status)
        {
        case CalibrationStatus::REQUIRED:
            mpu.process_calibration();
            break;
        case CalibrationStatus::DONE:
            mpu.get_measures();
            mpu.notify_all_linked_widget_task();
            break;
        default:
            mpu.is_data_ready(); // reset Data ready IRQ
            break;
        }
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