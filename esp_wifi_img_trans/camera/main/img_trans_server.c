#include"img_trans_server.h"

//定义用于HTTP多部分流的边界字符串
#define PART_BOUNDARY "123456789000000000000987654321"
//设置MIME类型为"multipart/x-mixed-replace"，适用于MJPEG流媒体
static char*STREAM_CONTENT="multipart/x-mixed-replace;boundary="PART_BOUNDARY;
//设置流的边界格式，用于分隔每一帧图像
static char*STREAM_BOUNDARY="\r\n--"PART_BOUNDARY"\r\n";
//设置每一部分的 HTTP 头信息（包括图像类型和长度）
static char*STREAM_PART="Content-Type: image/jpg\r\nContent-Length: %u\r\n\r\n";

//处理视频流的HTTP请求
static esp_err_t jpg_stream(httpd_req_t*req);
//启动http服务器
uint8_t http_init();

//处理视频流的HTTP请求
static esp_err_t jpg_stream(httpd_req_t*req)
{
    //JPEG图像数据的长度
    uint32_t jpg_len=0;
    //JPEG图像数据指针
    uint8_t*jpg_buf=NULL;
    //响应头缓冲区指针
    char part_buf[64]={0};
    //设置HTTP响应头类型为视频流类型
    httpd_resp_set_type(req,STREAM_CONTENT);
    //持续发送视频流帧
    while(1)
    {
        esp_err_t ret=ESP_OK;
        //获取JPEG数据
        if(ov5640_take(&jpg_buf,&jpg_len))
        {
            //获取JPEG数据失败
            printf("img_trans_server: jpg_stream: get jepg fail\n");
            return ESP_FAIL;
        }
        //发送流的边界部分，表示一帧的开始
        ret=httpd_resp_send_chunk(req,STREAM_BOUNDARY,strlen(STREAM_BOUNDARY));
        //发送每一帧的HTTP头信息
        uint16_t h_len=snprintf(part_buf,64,STREAM_PART,jpg_len);
        ret=httpd_resp_send_chunk(req,part_buf,h_len);
        //发送每一帧的JPEG图像数据
        ret=httpd_resp_send_chunk(req,(char*)jpg_buf,jpg_len);
        //释放JPEG数据
        ov5640_free();
        if(ret!=ESP_OK)
        {
            //HTTP通讯失败
            printf("img_trans_server: jpg_stream: connect fail\n");
            return ESP_FAIL;
        }
    }
}

//启动http服务器
uint8_t http_init()
{
    //默认配置参数
    httpd_config_t config=HTTPD_DEFAULT_CONFIG();
    //http服务
    httpd_handle_t server=NULL;
    //url处理结构
    httpd_uri_t uri_get={0};
    uri_get.uri="/";
    uri_get.method=HTTP_GET;
    uri_get.handler=jpg_stream;
    uri_get.user_ctx=NULL;
    esp_err_t ret=ESP_OK;
    //启动http服务器
    ret=httpd_start(&server,&config);
    //注册URI处理程序
    ret=httpd_register_uri_handler(server,&uri_get);
    if(ret!=ESP_OK)
    {
        //http服务器启动失败
        printf("jpg_stream: http_init: init fail\n");
        return 1;
    }else
    {
        //http服务器启动成功
        printf("jpg_stream: http_init: init ok\n");
        return 0;
    }
}
