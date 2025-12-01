/*
 * @Author:  E-mail 1247221946@qq.com
 * @Date: 2025-01-13 14:12:05
 * @LastEditors:  E-mail 1247221946@qq.com
 * @LastEditTime: 2025-01-13 15:47:40
 * @FilePath: \LVGL\main\main.c
 * @Description:
 *
 * Copyright (c) 2025 by 1247221946@qq.com, All Rights Reserved.
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "lvgl.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "lv_port_disp.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_chip_info.h" 
#include "esp_psram.h"
#include "esp_flash.h"
#include "esp_timer.h"
#include "lvgl/demos/lv_demos.h"
#include "demos/lv_demos.h"
#include "sdkconfig.h"



static void lvgl_act(void *pvParameter);

void app_main(void)
{
    xTaskCreatePinnedToCore(lvgl_act, "gui_app", 4096 * 2, NULL, 0, NULL, 1);

}
static void lvgl_act(void *pvParameter)
{


    esp_err_t ret;
    ret = nvs_flash_init();              /* 初始化NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES
    || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }


    lv_init();
    lv_port_disp_init();
    lv_demo_benchmark();



    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler();
    }

}
