#pragma once

#include "t_rtos_mpu6050_config.h"

void idle_task(void *robe);
void my_mpu_reading_task(void *probe);

void my_mpu_printing_task(void *probe);


void my_mpu_calibration_task( void* probe);// TODO: try to find how to code this task such that it can be started and stopped by an later extenal event, such as a button press, and not run continuously.  