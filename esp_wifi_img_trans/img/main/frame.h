#pragma once

//头文件
#include<stdio.h>
#include<string.h>
#include"esp_err.h"
#include"esp_camera.h"

//图像初始化
uint8_t frame_init(uint16_t hor,uint16_t ver);
//绘制图像
void frame_draw(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t*color);
//创建JPEG图像
uint8_t frame_jpg_mk(uint8_t**jpg_buf,uint32_t*jpg_len);
//释放JPEG图像
void frame_jpg_fr(uint8_t**jpg_buf);
