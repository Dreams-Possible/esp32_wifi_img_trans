#include"lvgl_port_display.h"
//enable lvgl port
#ifdef LVGL_PORT_DISPLAY_H

//config
#define HOR 240
#define VER 320

//device flash
static void flash(lv_display_t*display,const lv_area_t*area,uint8_t*color);
//lvgl port display init
void lvgl_port_display_init();

//device flash
static void flash(lv_display_t*display,const lv_area_t*area,uint8_t*color)
{
    frame_draw(area->x1,area->y1,area->x2,area->y2,(uint16_t*)color);
    lv_display_flush_ready(display);
    return;
}

//lvgl port display init
void lvgl_port_display_init()
{
    lv_display_t*display=lv_display_create(HOR,VER);
    lv_display_set_flush_cb(display,flash);
    uint8_t*buffer_1=malloc(HOR*VER/4*sizeof(uint16_t));
    uint8_t*buffer_2=malloc(HOR*VER/4*sizeof(uint16_t));
    lv_display_set_buffers(display,buffer_1,buffer_2,HOR*VER/4*sizeof(uint16_t),LV_DISPLAY_RENDER_MODE_PARTIAL);
    return;
}

#endif//#ifdef LVGL_PORT_DISPLAY_H
