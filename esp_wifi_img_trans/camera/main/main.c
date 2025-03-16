#include"main.h"

void app_main()
{
    //WiFi初始化
    while(wifi_init())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //摄像头初始化
    while(ov5640_init_user())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //启动http服务器
    while(http_init())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
