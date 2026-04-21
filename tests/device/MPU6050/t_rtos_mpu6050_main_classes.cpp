#include "t_rtos_mpu6050_main_classes.h"

#include "t_rtos_mpu6050_control.h"

extern MPU6050 mpu;
extern rtos_SwitchButton central_switch;
extern rtos_HW_I2C_Master i2c_mpu_master;
extern rtos_RotaryEncoder encoder;

//--------------- setup I2C Master connected to MPU---------------------
void i2c_mpu_irq_handler()
{
    i2c_mpu_master.i2c_dma_isr();
};

struct_ConfigMasterI2C cfg_mpu6050_i2c{
    .i2c = i2c1,
    .sda_pin = 2,
    .scl_pin = 3,
    .baud_rate = I2C_STANDARD_MODE,
    .i2c_tx_master_handler = i2c_mpu_irq_handler};

//--------------- setup MPU---------------------
struct_ConfigMPU6050 cfg_mpu_device{
    .SAMPLE_RATE_Hz = MPU_SAMPLE_RATE_Hz,
    .DLPF_BW = 5};

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
        mpu.data_ready_isr();
        break;
    case GPIO_MPU_RESET:
        gpio_set_irq_enabled(GPIO_MPU_RESET, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, false);
        xQueueSendFromISR(central_switch.IRQdata_input_queue, &data, &pxHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(&pxHigherPriorityTaskWoken);
        gpio_set_irq_enabled(GPIO_MPU_RESET, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        break;
    case GPIO_SCREEN_ENCODER_CLK:
        xQueueSendFromISR(encoder.IRQdata_input_queue, &data, &pxHigherPriorityTaskWoken);
        break;
    default:
        break;
    }
};
