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

my_mpu6050_screen_controller::my_mpu6050_screen_controller()
: rtos_UIModelManager()
{
}

my_mpu6050_screen_controller::~my_mpu6050_screen_controller()
{
}

void my_mpu6050_screen_controller::process_control_event(struct_ControlEventData control_event)
{
    switch (control_event.event)
    {
        case UIControlEvent::INCREMENT:
            increment_focus();
            printf("increment focus index, current focus index is %d\n", this->get_current_focus_index());
            break;
        case UIControlEvent::DECREMENT:
            decrement_focus();
            printf("decrement focus index, current focus index is %d\n", this->get_current_focus_index());
            break;
    default:
        break;
    }

}
