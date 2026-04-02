#include "t_rtos_mpu6050_config.h"

#include <stdio.h>

#include "t_rtos_mpu6050_main_tasks.h"
#include "t_rtos_mpu6050_console_widget.h"
#include "t_rtos_mpu6050_control.h"
#include "t_rtos_mpu6050_main_classes.h"
#include "t_rtos_mpu6050_display_setup.h"
#include "t_rtos_mpu6050_main_widgets.h"

Probe p0 = Probe(0);
Probe p1 = Probe(1);
// Probe p2 = Probe(2); I2C SDA
// Probe p3 = Probe(3); I2C SCL
Probe p4 = Probe(4);
Probe p5 = Probe(5);
// Probe p6 = Probe(6); MPU_INT
Probe p7 = Probe(7);

// extern rtos_HW_I2C_Master i2c_mpu_master;
extern struct_ConfigMPU6050 cfg_mpu_device;
extern struct_rtosConfigSwitchButton cfg_central_switch;
extern struct_ConfigMasterI2C cfg_mpu6050_i2c;

extern struct_ConfigMasterSPI cfg_spi;
extern struct_ConfigST7735 cfg_st7735;

extern struct_ConfigMasterI2C cfg_display_i2c;
extern struct_ConfigSSD1306 cfg_left_screen;
extern struct_ConfigSSD1306 cfg_right_screen;

extern struct_ConfigTextWidget cfg_monitoring_text;

rtos_HW_I2C_Master i2c_mpu_master = rtos_HW_I2C_Master(cfg_mpu6050_i2c);
MPU6050 mpu = MPU6050(&i2c_mpu_master, cfg_mpu_device, GPIO_MPU_INT, test_rtos_mpu6050_shared_IRQ_callback);
my_mpu6050_controller mpu_controller = my_mpu6050_controller(&mpu);

// ##### ST7735 setup #####
rtos_HW_SPI_Master spi_master = rtos_HW_SPI_Master(cfg_spi,
                                                   DMA_IRQ_0, end_of_TX_DMA_xfer_handler);
rtos_ST7735 color_display = rtos_ST7735(&spi_master, cfg_st7735);
rtos_GraphicDisplayGateKeeper SPI_display_gate_keeper = rtos_GraphicDisplayGateKeeper();

// ##### SSD1306 setup #####
#if defined(SHOW_MONITORING_WIDGET)
rtos_HW_I2C_Master i2c_display_master = rtos_HW_I2C_Master(cfg_display_i2c);
rtos_SSD1306 left_display = rtos_SSD1306(&i2c_display_master, cfg_left_screen);
rtos_SSD1306 right_display = rtos_SSD1306(&i2c_display_master, cfg_right_screen);
rtos_GraphicDisplayGateKeeper I2C_display_gate_keeper = rtos_GraphicDisplayGateKeeper();
#endif // SHOW_MONITORING_WIDGET

//--------------- setup launch_calibration switch---------------------
rtos_SwitchButton central_switch = rtos_SwitchButton(GPIO_MPU_RESET, &test_rtos_mpu6050_shared_IRQ_callback,
                                                     mpu_controller.control_event_input_queue,
                                                     cfg_central_switch);

//--------------- setup widgets---------------------
#if defined(ENABLE_PRINT_MEASURES)
my_mpu_console_widget console_widget = my_mpu_console_widget(&mpu);
#endif // ENABLE_PRINT_MEASURES
#if defined(SHOW_MONITORING_WIDGET)
MonitoringWidgets my_monitoring_widget = MonitoringWidgets(&mpu, cfg_monitoring_text, SSD1306_CANVAS_FORMAT, &left_display);
#endif // SHOW_MONITORING_WIDGET

//-----------------------------main--------------------------
int main()
{
#if defined(ENABLE_PRINT_MEASURES)
    stdio_init_all();
    xTaskCreate(my_mpu_printing_task, "mpu_printing", 256, &p4, 5, &console_widget.task_handle);
#endif // ENABLE_PRINT_MEASURES

#if defined(SHOW_MONITORING_WIDGET)
    xTaskCreate(I2C_display_gate_keeper_task, "I2C_gate_keeper_task", 256, NULL, 5, NULL);
    xTaskCreate(my_mpu_monitoring_task, "mpu_monit", 256, NULL, 10, &my_monitoring_widget.task_handle);
#endif // SHOW_MONITORING_WIDGET

    xTaskCreate(mpu_process_measures_task, "mpu_process_measures", 256, &p7, 5, NULL);

    xTaskCreate(SPI_display_gate_keeper_task, "SPI_gate_keeper_task", 256, NULL, 5, NULL);

    xTaskCreate(central_switch_process_irq_event_task, "mpu_reset", 256, NULL, 4, NULL);
    xTaskCreate(mpu_controller_task, "mpu_cntrl", 256, &p5, 6, NULL);

    xTaskCreate(idle_task, "idle_task", 256, &p0, 0, NULL);
    vTaskStartScheduler();

    while (true)
        tight_loop_contents();
}
