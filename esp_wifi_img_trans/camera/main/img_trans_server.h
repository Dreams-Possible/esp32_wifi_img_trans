#pragma once

//头文件
#include<stdio.h>
#include"esp_err.h"
#include"esp_http_server.h"
#include"ov5640.h"

//启动http服务器
uint8_t http_init();
