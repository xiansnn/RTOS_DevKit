#pragma once

#include "t_rtos_mpu6050_config.h"
#include "sw/widget/rtos_widget.h"
#include <string>

class MonitoringWidgets : public rtos_TextWidget
{
private:
    struct_MPUData measures;
    std::string Ax_string, Ay_string, Az_string, Gx_string, Gy_string, Gz_string, temp_string, vectG_string;

public:
    MonitoringWidgets(rtos_Model *actual_displayed_model,
                      struct_ConfigTextWidget text_cfg,
                      CanvasFormat canvas_format,
                      rtos_DisplayDevice *display_device);
    ~MonitoringWidgets();
    void get_value_of_interest();
    void draw();
};
