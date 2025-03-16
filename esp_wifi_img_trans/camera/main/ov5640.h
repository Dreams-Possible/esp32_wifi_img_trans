#pragma once

//头文件
#include<stdio.h>
#include<string.h>
#include"esp_err.h"
#include"esp_camera.h"

//摄像头初始化
uint8_t ov5640_init_user();
//获取一帧
uint8_t ov5640_take(uint8_t**jpg_buf,uint32_t*jpg_len);
//释放帧资源
void ov5640_free();
