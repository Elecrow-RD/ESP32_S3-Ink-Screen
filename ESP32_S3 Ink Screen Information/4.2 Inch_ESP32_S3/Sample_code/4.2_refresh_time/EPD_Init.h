#ifndef _EPD_INIT_H_
#define _EPD_INIT_H_

#include "spi.h"
//由于5.97Inch E-Paper屏幕是有两颗SSD1683 IC控制
//且SSD1683的分辨率为400x300 E-Paper的分辨率为 792x272 
//所以主从芯片使用分辨率为396x272将其级联在一起用于显示
//导致两颗IC拼接处存在8列像素点的空间 所以显示时需要做地址偏移
//因此程序将 EPD_W EPD_H定义为了 800x272 实际显示区域仍为792x272
//同时如果直接用EPD_Display函数直接调用全屏显示图片的话需要取模分辨率为 800x272
//如果用EPD_ShowPicture函数全屏显示图片的话取模分辨率为 792x272
#define EPD_W	400
#define EPD_H	300

#define WHITE 0xFF
#define BLACK 0x00

// #define ALLSCREEN_GRAGHBYTES  15000/2

// #define Source_BYTES 400/8
// #define Gate_BITS  	 272
// #define ALLSCREEN_BYTES Source_BYTES*Gate_BITS

#define Fast_Seconds_1_5s 0
#define Fast_Seconds_1_s  1

void EPD_ReadBusy(void);
void EPD_RESET(void);
void EPD_Sleep(void);

void EPD_Update(void);
void EPD_Update_Fast(void);
void EPD_Update_Part(void);
void EPD_Update_4Gray(void);

void EPD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
void EPD_SetCursor(uint16_t xs, uint16_t ys);

void EPD_Display(const uint8_t *Image);
void EPD_Display_Fast(const uint8_t *Image);
void EPD_Display_Part(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, const uint8_t *Image);

void EPD_Init(void);
void EPD_Init_Fast(uint8_t mode);
void EPD_Init_Part(void);
void EPD_Clear_R26A6H(void);
void EPD_Clear_R26H(const uint8_t *Image);

void EPD_Clear(void);
#endif
