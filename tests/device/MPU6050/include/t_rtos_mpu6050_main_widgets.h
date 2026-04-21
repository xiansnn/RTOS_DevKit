#pragma once

#include "t_rtos_mpu6050_config.h"
#include "sw/widget/rtos_widget.h"
#include <string>

// TODO add widget for gyro, accell, temp and G vector
//  TODO widget n° 0, 1, 2 etc dependant du focus du controller

class MonitoringWidgets : public rtos_TextWidget
{
private:
    struct_MPUData measures;
    int widget_id = 1; // 0 for accell, 1 for gyro, 2 for G vector, 3 for temp

public:
    MonitoringWidgets(rtos_Model *actual_displayed_model,
                      struct_ConfigTextWidget text_cfg,
                      CanvasFormat canvas_format,
                      rtos_DisplayDevice *display_device);
    ~MonitoringWidgets();
    void get_value_of_interest();
    void draw();
};

class SpiritLevelWidget : public rtos_GraphicWidget
{
private:
    struct_MPUData measures;

public:
    SpiritLevelWidget(rtos_Model *actual_displayed_model,
                      struct_ConfigGraphicWidget graph_cfg,
                      CanvasFormat canvas_format,
                      rtos_DisplayDevice *display_device);
    ~SpiritLevelWidget();
    void get_value_of_interest();
    void draw();
};
