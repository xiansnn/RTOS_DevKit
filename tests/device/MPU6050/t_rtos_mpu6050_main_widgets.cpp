#include "t_rtos_mpu6050_main_widgets.h"
#include <math.h>
#include <string>


struct_ConfigTextWidget cfg_monitoring_text {
    .number_of_column = 16,
    .number_of_line = 8,
    .widget_anchor_x = 0,
    .widget_anchor_y = 0,
    .font = font_8x8
};

MonitoringWidgets::MonitoringWidgets(rtos_Model *actual_displayed_model, struct_ConfigTextWidget text_cfg, CanvasFormat canvas_format, rtos_DisplayDevice *display_device)
:rtos_TextWidget(actual_displayed_model,text_cfg,canvas_format,display_device)
{
}

MonitoringWidgets::~MonitoringWidgets()
{
}

void MonitoringWidgets::get_value_of_interest()
{
    this->measures = ((MPU6050*)actual_rtos_displayed_model)->data;
    Ax_string = std::to_string(measures.g_x);
    Ay_string = std::to_string(measures.g_y);
    Az_string = std::to_string(measures.g_z);
    Gx_string = std::to_string(measures.gyro_x);
    Gy_string = std::to_string(measures.gyro_y);
    Gz_string = std::to_string(measures.gyro_z);
    temp_string = std::to_string(measures.temp_out);
}

void MonitoringWidgets::draw()
{
    this->writer->clear_text_buffer();
    this->get_value_of_interest();

    sprintf(this->writer->text_buffer,"Temp = %+.2f\nAx = %+.2f\nAy = %+.2f\nAz = %+.2f\n", measures.temp_out, measures.g_x, measures.g_y, measures.g_z);
    sprintf(this->writer->text_buffer,"Gx = %+.2f\nGy = %+.2f\nGz = %+.2f\n", measures.gyro_x, measures.gyro_y, measures.gyro_z);
    sprintf(this->writer->text_buffer,"vecteur G: %+.2f", sqrt(pow(measures.g_x, 2) + pow(measures.g_y, 2) + pow(measures.g_z, 2)));

    this->writer->write();
    this->writer->draw_border();

}
