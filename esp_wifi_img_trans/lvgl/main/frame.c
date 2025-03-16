#include"frame.h"

//图像数据
typedef struct frame_t
{
    //图像源地址
    uint16_t*img;
    //图像水平长度
    uint16_t hor;
    //图像垂直长度
    uint16_t ver;
}frame_t;
static frame_t frame={0};

//图像初始化
uint8_t frame_init(uint16_t hor,uint16_t ver);
//矫正图像
static  void frame_rgbcg(uint16_t*rgb);
//绘制图像
void frame_draw(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t*color);
//创建JPEG图像
uint8_t frame_jpg_mk(uint8_t**jpg_buf,uint32_t*jpg_len);
//释放JPEG图像
void frame_jpg_fr(uint8_t**jpg_buf);

//图像初始化
uint8_t frame_init(uint16_t hor,uint16_t ver)
{
    frame.hor=hor;
    frame.ver=ver;
    frame.img=malloc(hor*ver*sizeof(uint16_t));
    if(!frame.img)
    {
        //图像初始化失败
        printf("frame: frame_init: init fail\n");
        return 1;
    }
    uint16_t*frame_=frame.img;
    for(uint32_t f=0;f<frame.hor*frame.ver;++f)
    {
        frame_[f]=0xffff;
        frame_rgbcg(&frame_[f]);
    }
    printf("frame: frame_init: init ok\n");
    return 0;
}

//矫正图像
static void frame_rgbcg(uint16_t*rgb)
{
    *rgb=((*rgb)<<8|(*rgb>>8));
}

//绘制图像
void frame_draw(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t*color)
{
    if(!color)
    {
        printf("frame: frame_draw: error\n");
        return;
    }
    if(x2>frame.hor||y2>frame.ver)
    {
        printf("frame: frame_draw: error\n");
        return;
    }
    if(x2<x1||y2<y1)
    {
        printf("frame: frame_draw: error\n");
        return;
    }
    uint32_t num=(x2-x1+1)*(y2-y1+1);
    uint16_t*frame_=malloc(num*sizeof(uint16_t));
    uint16_t*frame_bp=frame_;
    if(!frame_)
    {
        printf("frame: frame_draw: error\n");
        return;
    }
    memcpy(frame_,color,num*sizeof(uint16_t));
    for(uint32_t f=0;f<num;++f)
    {
        frame_rgbcg(&frame_[f]);
    }
    uint16_t*frame_h=frame.img+frame.hor*y1+x1;
    for(uint32_t f=y1;f<=y2;++f)
    {
        memcpy(frame_h,frame_,(x2-x1+1)*sizeof(uint16_t));
        frame_h+=frame.hor;
        frame_+=x2-x1+1;
    }
    free(frame_bp);
    return;
}

//创建JPEG图像
uint8_t frame_jpg_mk(uint8_t**jpg_buf,uint32_t*jpg_len)
{
    //进行JPEG压缩
    uint8_t ret=fmt2jpg((uint8_t*)frame.img,0,frame.hor,frame.ver,PIXFORMAT_RGB565,100,jpg_buf,(size_t*)jpg_len);
    if(ret!=1)
    {
        //JPEG压缩失败
        printf("frame: frame_jpg_mk: jpeg creat fail\n");
        return 1;
    }
    return 0;
}

//释放JPEG图像
void frame_jpg_fr(uint8_t**jpg_buf)
{
    if(*jpg_buf)
    {
        free(*jpg_buf);
    }
}
