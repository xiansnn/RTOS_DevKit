#include "t_rtos_mpu6050_control.h"

struct_rtosConfigSwitchButton cfg_central_switch{
    .debounce_delay_us = 5000,
    .long_release_delay_us = 1000000,
    .long_push_delay_ms = 1500,
    .time_out_delay_ms = 5000};

struct_rtosConfigSwitchButton cfg_encoder_clk{
    .debounce_delay_us = 5000,
    .long_release_delay_us = 1000000,
    .long_push_delay_ms = 1000,
    .time_out_delay_ms = TIMEOUT_SWITCH_DELAY_ms};



my_mpu6050_controller::my_mpu6050_controller(MPU6050 *my_mpu)
{
    controlled_mpu = my_mpu;
}

my_mpu6050_controller::~my_mpu6050_controller()
{
}

void my_mpu6050_controller::process_control_event(struct_ControlEventData control_event)
{
    switch (control_event.event)
    {
    case UIControlEvent::LONG_PUSH:
        controlled_mpu->lauch_soft_reset();
        break;
    case UIControlEvent::RELEASED_AFTER_SHORT_TIME:
        controlled_mpu->launch_calibration();
        break;
    default:
        break;
    }
}



my_mpu6050_screen_controller::my_mpu6050_screen_controller(MonitoringWidgets *controlled_widget, int min_value, int max_value, bool is_wrappable)
    :rtos_UIControlledModel(), core_IncrementControlledModel(min_value, max_value, is_wrappable)
{
    this->controlled_widget = controlled_widget;
}

my_mpu6050_screen_controller::~my_mpu6050_screen_controller()
{
}

void my_mpu6050_screen_controller::process_control_event(struct_ControlEventData control_event)
{
    switch (control_event.event)
    {
        case UIControlEvent::INCREMENT:
            increment_value();
            // printf("increment widget index, current widget index is %d\n", this->get_value());
            break;
        case UIControlEvent::DECREMENT:
            decrement_value();
            // printf("decrement widget index, current widget index is %d\n", this->get_value());
            break;
    default:
        break;
    }
    this->controlled_widget->widget_id = this->get_value();

}
