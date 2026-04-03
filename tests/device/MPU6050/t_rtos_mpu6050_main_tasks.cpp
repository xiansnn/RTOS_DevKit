#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_console_widget.h"
#include "t_rtos_mpu6050_control.h"
#include "t_rtos_mpu6050_main_widgets.h"

extern MPU6050 mpu;
extern rtos_SwitchButton central_switch;
extern my_mpu_console_widget console_widget;
extern my_mpu6050_controller mpu_controller;
extern MonitoringWidgets my_monitoring_widget;
extern rtos_GraphicDisplayGateKeeper I2C_display_gate_keeper;
extern SpiritLevelWidget my_spirit_level_widget;
extern rtos_GraphicDisplayGateKeeper SPI_display_gate_keeper;

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

void mpu_controller_task(void *probe)
{
    struct_ControlEventData data;
    while (true)
    {
        xQueueReceive(mpu_controller.control_event_input_queue, &data, portMAX_DELAY);
        if (probe != NULL)
            ((Probe *)probe)->hi();
        mpu_controller.process_control_event(data);
        if (probe != NULL)
            ((Probe *)probe)->lo();
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

void my_mpu_monitoring_task(void *probe)
{
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (probe != NULL)
            ((Probe *)probe)->hi();
        my_monitoring_widget.draw();
        if (probe != NULL)
            ((Probe *)probe)->lo();
        I2C_display_gate_keeper.send_widget_data(&my_monitoring_widget);
    }
}

void my_mpu_spirit_level_task(void *probe)
{
    my_spirit_level_widget.display_device->clear_device_screen_buffer();
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (probe != NULL)
            ((Probe *)probe)->hi();
        my_spirit_level_widget.draw();
        if (probe != NULL)
            ((Probe *)probe)->lo();
        SPI_display_gate_keeper.send_widget_data(&my_spirit_level_widget);
    }
}
