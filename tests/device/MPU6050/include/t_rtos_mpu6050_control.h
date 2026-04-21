#pragma once
#include "t_rtos_mpu6050_config.h"
#include "t_rtos_mpu6050_main_widgets.h"
#include "device/switch_button/rtos_switch_button.h"
#include "device/rotary_encoder/rtos_rotary_encoder.h"
#include "sw/ui_core/rtos_ui_core.h"

void ky040_encoder_irq_call_back(uint gpio, uint32_t event_mask);

class my_mpu6050_controller : public rtos_UIControlledModel
{
private:
    MPU6050 *controlled_mpu;
    
    public:
    my_mpu6050_controller(MPU6050 *my_mpu);
    ~my_mpu6050_controller();
    
    void process_control_event(struct_ControlEventData control_event);
};

class my_mpu6050_screen_controller : public rtos_UIControlledModel, public core_IncrementControlledModel
{
    private:
    MonitoringWidgets *controlled_widget;
    /* data */
public:
    my_mpu6050_screen_controller(MonitoringWidgets *controlled_widget, int min_value, int max_value, bool is_wrappable = true);
    ~my_mpu6050_screen_controller();
    void process_control_event(struct_ControlEventData control_event);
};
