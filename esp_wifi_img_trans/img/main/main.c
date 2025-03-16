#include"main.h"

void app_main()
{
    //WiFi初始化
    while(wifi_init())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //图像初始化
    while(frame_init(1024,1024))
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //启动http服务器
    while(http_init())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
