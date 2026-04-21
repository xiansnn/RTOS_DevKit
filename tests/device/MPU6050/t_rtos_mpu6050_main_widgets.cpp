#include "t_rtos_mpu6050_main_widgets.h"
#include <math.h>
#include <string>

struct_ConfigTextWidget cfg_monitoring_text{
    .number_of_column = 10,
    .number_of_line = 4,
    .widget_anchor_x = 0,
    .widget_anchor_y = 0,
    .font = font_12x16};

struct_ConfigGraphicWidget cfg_spirit_level{
    .canvas_width_pixel = SPIRIT_LEVEL_WIDGET_SIZE,
    .canvas_height_pixel = SPIRIT_LEVEL_WIDGET_SIZE,
    .canvas_foreground_color = SPIRIT_LEVEL_REF_CIRCLE_COLOR,
    .canvas_background_color = SPIRIT_LEVEL_BACKGROUND_COLOR,
    .widget_anchor_x = 0,
    .widget_anchor_y = 0,
    .widget_with_border = true};
MonitoringWidgets::MonitoringWidgets(rtos_Model *actual_displayed_model, struct_ConfigTextWidget text_cfg, CanvasFormat canvas_format, rtos_DisplayDevice *display_device)
    : rtos_TextWidget(actual_displayed_model, text_cfg, canvas_format, display_device)
{
}

MonitoringWidgets::~MonitoringWidgets()
{
}

void MonitoringWidgets::get_value_of_interest()
{
    this->measures = ((MPU6050 *)actual_rtos_displayed_model)->data;
}

void MonitoringWidgets::draw()
{
    p4.hi();
    this->writer->clear_text_buffer();
    this->get_value_of_interest();

    switch (widget_id)
    {
    case 0:
        sprintf(this->writer->text_buffer,
                "Ax= %+4.2f\nAy= %+4.2f\nAz= %+4.2f",
                measures.g_x, measures.g_y, measures.g_z);
        break;
    case 1:
        sprintf(this->writer->text_buffer,
                "Gx=%+5.2f\nGy=%+5.2f\nGz=%+5.2f",
                measures.gyro_x, measures.gyro_y, measures.gyro_z);
        break;
    case 2:
        sprintf(this->writer->text_buffer,
                "G-> %+4.2f",
                sqrt(pow(measures.g_x, 2) + pow(measures.g_y, 2) + pow(measures.g_z, 2)));

        break;
    case 3:
        sprintf(this->writer->text_buffer,
                "T= %+3.1f\xF8\x43",
                measures.temp_out);
        break;

    default:
        break;
    }
    this->writer->write();
    this->writer->draw_border();
    p4.lo();
}

SpiritLevelWidget::SpiritLevelWidget(rtos_Model *actual_displayed_model, struct_ConfigGraphicWidget graph_cfg, CanvasFormat canvas_format, rtos_DisplayDevice *display_device)
    : rtos_GraphicWidget(actual_displayed_model, graph_cfg, canvas_format, display_device)
{
}

SpiritLevelWidget::~SpiritLevelWidget()
{
}

void SpiritLevelWidget::get_value_of_interest()
{
    this->measures = ((MPU6050 *)actual_rtos_displayed_model)->data;
}

void SpiritLevelWidget::draw()
{
    this->drawer->clear_widget();
    this->get_value_of_interest();
    // draw

    this->drawer->rect(0, 0, this->drawer->canvas->canvas_width_pixel, this->drawer->canvas->canvas_height_pixel, true, SPIRIT_LEVEL_BACKGROUND_COLOR);
    // draw bubble
    int spirit_level_center_x = SPIRIT_LEVEL_WIDGET_SIZE / 2;
    int spirit_level_center_y = SPIRIT_LEVEL_WIDGET_SIZE / 2;
    int bubble_center_x = spirit_level_center_x * (1 + measures.g_y);
    int bubble_center_y = spirit_level_center_y * (1 + measures.g_x);
    this->drawer->circle(SPIRIT_LEVEL_RADIUS - 1, bubble_center_x, bubble_center_y, true, SPIRIT_LEVEL_BUBBLE_COLOR);
    // draw ref cercle
    this->drawer->circle(SPIRIT_LEVEL_RADIUS, spirit_level_center_x, spirit_level_center_y, false, SPIRIT_LEVEL_REF_CIRCLE_COLOR);

    this->drawer->draw_border(this->drawer->canvas->fg_color);
}
