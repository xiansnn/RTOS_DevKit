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

#define ENABLE_PRINT_MEASURES


#define GPIO_MPU_INT 21 // gpio connnected to MPU INT pin
#define MPU_SAMPLE_RATE_Hz 20

