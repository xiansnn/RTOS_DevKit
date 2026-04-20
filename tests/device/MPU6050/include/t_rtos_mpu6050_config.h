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

//----------options----------------------------------
// #define SHOW_PRINT_MEASURES
#define SHOW_MONITORING_WIDGET
// #define SHOW_ROTATION
#define SHOW_SPIRIT_LEVEL_WIDGET

//---------------spirit level configuration------------
#define SPIRIT_LEVEL_WIDGET_SIZE 128
#define SPIRIT_LEVEL_RADIUS 20
#define SPIRIT_LEVEL_REF_CIRCLE_COLOR ColorIndex::RED
#define SPIRIT_LEVEL_BUBBLE_COLOR ColorIndex::BLACK
#define SPIRIT_LEVEL_BACKGROUND_COLOR ColorIndex::PHOSPHOR

//TODO changer affichage avec encodeur


//------------------MPU6050 configuration------------
#define GPIO_MPU_INT 21 // gpio connnected to MPU INT pin
#define GPIO_MPU_RESET 18 // gpio connnected to MPU reset switch
#define MPU_SAMPLE_RATE_Hz 10

//------------------encoder button configuration------------
#define GPIO_SCREEN_ENCODER_CLK 19
#define GPIO_SCREEN_ENCODER_DT 20
#define TIMEOUT_GLOBAL_DELAY_ms 5000
#define TIMEOUT_SWITCH_DELAY_ms 1000
#define TIMEOUT_UI_MANAGER_DELAY_ms TIMEOUT_GLOBAL_DELAY_ms - TIMEOUT_SWITCH_DELAY_ms


//-------------- SSD1306 display configuration------------
#define SSD1306_CANVAS_FORMAT CanvasFormat::MONO_VLSB

//-------------- ST7735 display configuration------------
#define ST7735_GRAPHICS_CANVAS_FORMAT CanvasFormat::RGB565_16b
#define ST7735_TEXT_CANVAS_FORMAT CanvasFormat::RGB565_16b
//---------ST7735 options----------

// #define ST7735_128x128
#ifdef ST7735_128x128
#define DEVICE_DISPLAY_TYPE ST7735DisplayType::ST7735_144_128_RGB_128_GREENTAB
#define DEVICE_DISPLAY_ROTATION ST7735Rotation::_90
#define DEVICE_DISPLAY_HEIGHT 128
#endif
#define ST7735_128x160
#ifdef ST7735_128x160
#define DEVICE_DISPLAY_TYPE ST7735DisplayType::ST7735_177_160_RGB_128_GREENTAB
#define DEVICE_DISPLAY_ROTATION ST7735Rotation::_180
#define DEVICE_DISPLAY_HEIGHT 160
#endif

