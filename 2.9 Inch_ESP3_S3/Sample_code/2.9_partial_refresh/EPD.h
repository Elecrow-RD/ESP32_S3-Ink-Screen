#ifndef _EPD_H_
#define _EPD_H_

#include "EPD_Init.h"

/* 函数说明 */
void EPD_DrawPoint(uint16_t x, uint16_t y, uint8_t color);
void EPD_Clear(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color);                                 // 填充缓存函数
void EPD_DrawLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color);                              // 划线函数
void EPD_DrawRectangle(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color);                         // 绘制空心矩形
void Draw_Circle(int xc, int yc, int x, int y, uint8_t color);                                                     // 8分法画圆内部调用
void EPD_DrawCircle(uint16_t xc, uint16_t yc, uint16_t r, uint8_t color, uint16_t mode);                           // 绘制圆形
void EPD_DrawTriangel(uint16_t x, uint16_t y, uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color);  // 绘制空心三角形
void EPD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t color, uint8_t sizey);                              // 显示字符函数
void EPD_ShowString(uint16_t x, uint16_t y, const char *s, uint8_t color, uint16_t sizey);                         // 显示字符串
uint32_t mypow(uint8_t m, uint8_t n);                                                                              // 幂运算内部调用
void EPD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t color, uint8_t sizey);                 // 显示数字
void EPD_ShowFloatNum(uint16_t x, uint16_t y, float num, uint8_t pre, uint8_t len, uint8_t color, uint8_t sizey);  // 显示浮点数
//void EPD_ShowChinese12x12(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                    // 显示12x12字符串
//void EPD_ShowChinese16x16(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                    // 显示16x16字符串
//void EPD_ShowChinese24x24(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                    // 显示24x24字符串
//void EPD_ShowChinese32x32(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                    // 显示32x32字符串
//void EPD_ShowChinese(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                         // 显示中文字符串
//void EPD_ShowStr(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                             // 中英混显
//void EPD_StrCenter(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey);                           // 居中显示
void EPD_ShowPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t pic[], uint8_t color); // 图片显示
void EPD_ShowWatch(uint16_t x, uint16_t y, float num, uint8_t pre, uint8_t len, uint8_t color, uint8_t sizey);     // 显示秒表
#endif
