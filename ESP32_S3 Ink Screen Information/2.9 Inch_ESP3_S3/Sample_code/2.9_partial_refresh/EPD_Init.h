#ifndef _EPD_INIT_H_
#define _EPD_INIT_H_

#include "spi.h"

/* 定义墨水屏显示方向 */
#define USE_HORIZONTIAL 2 /* 0 1 2 3 */

#if USE_HORIZONTIAL == 0 | USE_HORIZONTIAL == 2
#define EPD_W 296
#define EPD_H 128
#define ALLSCREEN_BYTES ((EPD_H % 8) ? (EPD_H / 8 + 1) : (EPD_H / 8)) * EPD_W
#else
#define EPD_W 128
#define EPD_H 296
#define ALLSCREEN_BYTES ((EPD_W % 8) ? (EPD_W / 8 + 1) : (EPD_W / 8)) * EPD_H
#endif
/* 定义颜色参数 */
/* R24H:黑色像素写0 白色像素写1 */
#define WHITE 0xFF
#define BLACK 0x00

/* 函数说明 */
void EPD_READBUSY(void);
void EPD_HW_RESET(void);
void EPD_Sleep(void);
void EPD_Update(void);
void EPD_PartUpdate(void);
void EPD_FastUpdate(void);
void EPD_Clear_R26H(void);
void EPD_ALL_Fill(uint8_t color);
void EPD_DisplayImage(const uint8_t *ImageBW);
void EPD_Init(void);
#endif
