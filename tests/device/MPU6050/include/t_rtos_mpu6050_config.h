#pragma once
#include "device/MPU6050/mpu6050.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "utilities/probe/probe.h"

extern Probe p1;
extern Probe p4;
extern Probe p5;
extern Probe p6;
extern Probe p7;

// #define SHOW_PRINT_MEASURES
#define SHOW_MONITORING_WIDGET
// #define SHOW_ROTATION
#define SHOW_SPIRIT_LEVEL_WIDGET


//------------------MPU6050----------------------
#define GPIO_MPU_INT 21 // gpio connnected to MPU INT pin
#define GPIO_MPU_RESET 18 // gpio connnected to MPU reset switch
#define MPU_SAMPLE_RATE_Hz 10

//--------------display
#define SSD1306_CANVAS_FORMAT CanvasFormat::MONO_VLSB
#define ST7735_GRAPHICS_CANVAS_FORMAT CanvasFormat::RGB565_16b
#define ST7735_TEXT_CANVAS_FORMAT CanvasFormat::RGB565_16b

// #define ST7735_128x128
#define ST7735_128x160

#ifdef ST7735_128x128
#define DEVICE_DISPLAY_TYPE ST7735DisplayType::ST7735_144_128_RGB_128_GREENTAB
#define DEVICE_DISPLAY_ROTATION ST7735Rotation::_90
#define DEVICE_DISPLAY_HEIGHT 128
#endif
#ifdef ST7735_128x160
#define DEVICE_DISPLAY_TYPE ST7735DisplayType::ST7735_177_160_RGB_128_GREENTAB
#define DEVICE_DISPLAY_ROTATION ST7735Rotation::_180
#define DEVICE_DISPLAY_HEIGHT 160
#endif

