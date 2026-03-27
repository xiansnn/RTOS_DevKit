#pragma once

#include "t_rtos_mpu6050_config.h"

void idle_task(void *robe);

void my_mpu_process_measures_task(void *probe);

void my_mpu_printing_task(void *probe);
