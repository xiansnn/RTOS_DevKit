#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_console_widget.h"
#include "t_rtos_mpu6050_control.h"

extern MPU6050 mpu;
extern rtos_SwitchButton central_switch;
extern my_mpu_console_widget console_widget;

void test_rtos_mpu6050_shared_IRQ_callback(uint gpio, uint32_t events);

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

void central_switch_process_irq_event_task(void *)
{
    central_switch.rtos_process_IRQ_event();
}

void mpu_process_measures_task(void *probe)
{
    mpu.process_measures_task(probe);
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