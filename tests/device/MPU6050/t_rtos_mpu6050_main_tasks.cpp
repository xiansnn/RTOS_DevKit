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
    // size_t nb_sample;
    // float accel_x{};
    // float accel_y{};
    // float accel_z{};
    // float gyro_x{};
    // float gyro_y{};
    // float gyro_z{};
    mpu.is_data_ready(); // reset Data ready IRQ

    while (true)
    {
        xSemaphoreTake(mpu.data_ready_semaphore, portMAX_DELAY);
        switch (mpu.calibration_status)
        {
        case CalibrationStatus::REQUIRED:
            if (probe != NULL)
                ((Probe *)probe)->hi();
            mpu.read_registers_all_raw_data();
            mpu.calibration_status = CalibrationStatus::IN_PROGRESS;
            if (probe != NULL)
                ((Probe *)probe)->lo();
            break;
        case CalibrationStatus::IN_PROGRESS:
            if (probe != NULL)
                ((Probe *)probe)->hi();
            mpu.process_calibration();
            if (probe != NULL)
                ((Probe *)probe)->lo();
            break;
        case CalibrationStatus::DONE:
            if (probe != NULL)
                ((Probe *)probe)->hi();
            mpu.get_measures();
            mpu.notify_all_linked_widget_task();
            if (probe != NULL)
                ((Probe *)probe)->lo();

            break;
        default:
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