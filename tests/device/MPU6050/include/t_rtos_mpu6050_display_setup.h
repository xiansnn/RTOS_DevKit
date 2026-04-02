#pragma once

#include "t_rtos_mpu6050_config.h"

#include "device/ST7735/st7735.h"
#include "device/SSD1306/ssd1306.h"


extern rtos_GraphicDisplayGateKeeper SPI_display_gate_keeper ;




void end_of_TX_DMA_xfer_handler();
void SPI_display_gate_keeper_task(void *probe);


extern rtos_GraphicDisplayGateKeeper I2C_display_gate_keeper;
extern rtos_HW_I2C_Master i2c_display_master;


void I2C_display_gate_keeper_task(void *probe);
void i2c_display_irq_handler();

