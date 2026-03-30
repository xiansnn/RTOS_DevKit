#include "t_rtos_mpu6050_control.h"


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
        /* reset et init mpu*/
        break;
    case UIControlEvent::RELEASED_AFTER_SHORT_TIME:
        controlled_mpu->launch_calibration( );
        break;
    default:
        break;
    }
}



