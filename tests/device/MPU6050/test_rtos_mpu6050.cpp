#include "t_rtos_mpu6050_config.h"

#include "hardware/gpio.h"
#include <stdio.h>

#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_console_widget.h"
#include "t_rtos_mpu6050_control.h"

Probe p0 = Probe(0);
Probe p1 = Probe(1);
// Probe p2 = Probe(2); I2C SDA
// Probe p3 = Probe(3); I2C SCL
Probe p4 = Probe(4);
Probe p5 = Probe(5);
// Probe p6 = Probe(6); MPU_INT
Probe p7 = Probe(7);

//--------------- setup I2C Master connected to MPU---------------------
void i2c_irq_handler();
struct_ConfigMasterI2C cfg_mpu6050_i2c{
    .i2c = i2c1,
    .sda_pin = 2,
    .scl_pin = 3,
    .baud_rate = I2C_STANDARD_MODE,
    .i2c_tx_master_handler = i2c_irq_handler};

rtos_HW_I2C_Master i2c_mpu_master = rtos_HW_I2C_Master(cfg_mpu6050_i2c);

void i2c_irq_handler()
{
    i2c_mpu_master.i2c_dma_isr();
};
//--------------- setup MPU---------------------
struct_ConfigMPU6050 cfg_mpu_device{
    .SAMPLE_RATE_Hz = MPU_SAMPLE_RATE_Hz,
    .DLPF_BW = 5};

void test_rtos_mpu6050_shared_IRQ_callback(uint gpio, uint32_t events);
MPU6050 mpu = MPU6050(&i2c_mpu_master, cfg_mpu_device, GPIO_MPU_INT, test_rtos_mpu6050_shared_IRQ_callback);
my_mpu6050_controller mpu_controller = my_mpu6050_controller(&mpu);

//--------------- setup launch_calibration switch---------------------
struct_rtosConfigSwitchButton cfg_central_switch{
    .debounce_delay_us = 5000,
    .long_release_delay_us = 1000000,
    .long_push_delay_ms = 1500,
    .time_out_delay_ms = 5000};

rtos_SwitchButton central_switch = rtos_SwitchButton(GPIO_MPU_RESET, &test_rtos_mpu6050_shared_IRQ_callback,
                                                     mpu_controller.control_event_input_queue,
                                                     cfg_central_switch);

//--------------- setup console widget---------------------
my_mpu_console_widget console_widget = my_mpu_console_widget(&mpu);

//-------------------- IRQ callback--------------------
void test_rtos_mpu6050_shared_IRQ_callback(uint gpio, uint32_t event_mask)
{
    struct_SwitchButtonIRQData data;
    data.event_mask = event_mask;
    data.current_time_us = time_us_32();
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    switch (gpio)
    {
    case GPIO_MPU_INT:
        p1.hi();
        mpu.data_ready_isr();
        p1.lo();
        break;
    case GPIO_MPU_RESET:
        gpio_set_irq_enabled(GPIO_MPU_RESET, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, false);
        xQueueSendFromISR(central_switch.IRQdata_input_queue, &data, &pxHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(&pxHigherPriorityTaskWoken);
        gpio_set_irq_enabled(GPIO_MPU_RESET, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        break;
    default:
        break;
    }
};

//-----------------------------main--------------------------
int main()
{
#if defined(ENABLE_PRINT_MEASURES)
    stdio_init_all();
    xTaskCreate(my_mpu_printing_task, "mpu_printing", 256, &p4, 5, &console_widget.task_handle);
#endif // ENABLE_PRINT_MEASURES

    xTaskCreate(mpu_process_measures_task, "mpu_process_measures", 256, &p7, 5, NULL);

    xTaskCreate(central_switch_process_irq_event_task, "mpu_reset", 256, NULL, 4, NULL);
    xTaskCreate(mpu_controller_task, "mpu_cntrl", 256, &p5, 6, NULL);

    xTaskCreate(idle_task, "idle_task", 256, &p0, 0, NULL);
    vTaskStartScheduler();

    while (true)
        tight_loop_contents();
}
