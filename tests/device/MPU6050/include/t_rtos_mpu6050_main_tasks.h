#pragma once

#include "t_rtos_mpu6050_config.h"

void idle_task(void *pxProbe);
void my_mpu_reading_task(void *);