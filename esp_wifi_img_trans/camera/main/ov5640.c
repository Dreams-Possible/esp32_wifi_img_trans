#include"ov5640.h"

//配置摄像头
#define PWDN_IO 11//电源开关，低电平正常工作，高电平停止工作
#define RST_IO 12//复位，高电平触发复位
#define XCLK_IO -1
#define SIOD_SDA_IO 9
#define SIOC_SCL_IO 10
#define D0_IO 4
#define D1_IO 5
#define D2_IO 6
#define D3_IO 7
#define D4_IO 15
#define D5_IO 16
#define D6_IO 17
#define D7_IO 18
#define VSYNC_IO 8
#define HREF_IO 19
#define PCLK_IO 20

//摄像头初始化
uint8_t ov5640_init_user();
//获取一帧
uint8_t ov5640_take(uint8_t**jpg_buf,uint32_t*jpg_len);
//释放帧资源
void ov5640_free();

//摄像头数据
camera_fb_t*camera_fb=NULL;

//摄像头初始化
uint8_t ov5640_init_user()
{
    //配置摄像头
    camera_config_t camera_config={0};
    camera_config.pin_pwdn=PWDN_IO;
    camera_config.pin_reset=RST_IO;
    camera_config.pin_xclk=XCLK_IO;
    camera_config.pin_sccb_sda=SIOD_SDA_IO;
    camera_config.pin_sccb_scl=SIOC_SCL_IO;
    camera_config.pin_d7=D7_IO;
    camera_config.pin_d6=D6_IO;
    camera_config.pin_d5=D5_IO;
    camera_config.pin_d4=D4_IO;
    camera_config.pin_d3=D3_IO;
    camera_config.pin_d2=D2_IO;
    camera_config.pin_d1=D1_IO;
    camera_config.pin_d0=D0_IO;
    camera_config.pin_vsync=VSYNC_IO;
    camera_config.pin_href=HREF_IO;
    camera_config.pin_pclk=PCLK_IO;
    camera_config.xclk_freq_hz=20000000;
    camera_config.ledc_timer=LEDC_TIMER_0;
    camera_config.ledc_channel=LEDC_CHANNEL_0;
    camera_config.pixel_format=PIXFORMAT_JPEG;
    // camera_config.frame_size=FRAMESIZE_VGA;
    camera_config.frame_size=FRAMESIZE_HD;
    // camera_config.frame_size=FRAMESIZE_FHD;
    camera_config.jpeg_quality=16;
    camera_config.fb_count=2;
    camera_config.grab_mode=CAMERA_GRAB_LATEST;
    //初始化摄像头
    esp_err_t ret=esp_camera_init(&camera_config);
    if(ret!=ESP_OK)
    {
        //初始化摄像头失败
        printf("ov5640: ov5640_init_user: init fail\n");
        return 1;
    }
    //初始化摄像头成功
    printf("ov5640: ov5640_init_user: init ok\n");
    return 0;
}

//获取一帧
uint8_t ov5640_take(uint8_t**jpg_buf,uint32_t*jpg_len)
{
    //获取一帧
    camera_fb=esp_camera_fb_get();
    if(!camera_fb)
    {
        *jpg_buf=NULL;
        *jpg_len=0;
        printf("ov5640: ov5640_take: take fail\n");
        return 1;
    }else
    {
        *jpg_buf=camera_fb->buf;
        *jpg_len=camera_fb->len;
        printf("ov5640: ov5640_take: take\n");
        return 0;
    }
}

//释放帧资源
void ov5640_free()
{
    //释放摄像头资源
    if(camera_fb)
    {
        esp_camera_fb_return(camera_fb);
        camera_fb=NULL;
    }
}
