#include"main.h"

void app_main()
{
    //WiFi初始化
    while(wifi_init())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //图像初始化
    while(frame_init(240,320))
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //启动http服务器
    while(http_init())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //lvgl init
    lv_init();

    //lvgl port display init
    lvgl_port_display_init();

    //lvgl ui init
    ui_init();

    while(1)
    {
        lv_tick_inc(10);
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
