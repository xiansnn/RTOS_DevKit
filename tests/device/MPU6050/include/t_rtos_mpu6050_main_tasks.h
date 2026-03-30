#pragma once

#include "t_rtos_mpu6050_config.h"

void idle_task(void *robe);

void mpu_process_measures_task(void *probe);

void central_switch_process_irq_event_task(void *);

void mpu_controller_task(void* probe);

void my_mpu_printing_task(void *probe);
