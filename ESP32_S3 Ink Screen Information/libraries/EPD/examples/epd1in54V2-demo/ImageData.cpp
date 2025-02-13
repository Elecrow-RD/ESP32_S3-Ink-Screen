/**
 *  @filename   :   imagedata.cpp
 *  @brief      :   data file for epd demo
 *
 *  Copyright (C) Waveshare     September 5 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "imagedata.h"
#include <avr/pgmspace.h>

const unsigned char IMAGE_DATA[] PROGMEM = { /* 0X00,0X01,0XC8,0X00,0XC8,0X00, */
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFE,0X01,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XF8,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XFF,
0X3F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XF0,0X00,
0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XF0,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XE3,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,
0XE0,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,0X9F,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XE1,0XE3,0X00,0X00,0X00,0X00,0X01,
0XFF,0XFF,0XE7,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF1,0XC3,0XF3,0X0F,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XE3,0XFF,0X8F,0XFF,0XFF,
0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XC3,0X3B,0X0F,0XFF,0XFF,
0XFF,0XFE,0XFF,0XFF,0XE3,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF1,0XC3,0X0F,0X0F,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XE1,0XFE,0X1F,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XC3,0X0F,0X0F,
0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XF0,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XE3,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XC3,0X87,0X0F,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XF0,
0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XE0,0X7F,0XFF,0XFF,0XFF,0XFF,0XF1,0XC1,
0X03,0X0F,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XF8,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0X8F,
0XFF,0XE0,0X0F,0XFF,0XFF,0XFF,0XFF,0XF1,0XE0,0X00,0X1F,0XFF,0XFF,0XFF,0XFE,0XFF,
0XFF,0XFE,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFC,0X03,0XFF,0XFF,0XFF,0XFF,
0XF1,0XE0,0X00,0X1F,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X8F,0XFF,0XFF,0X80,0X7F,0XFF,0XFF,0XFF,0XF1,0XF0,0X00,0X3F,0XFF,0XFF,0XFF,
0X7E,0XFF,0XFF,0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XF0,0X1F,0XFF,
0XFF,0XFF,0XF1,0XF8,0X00,0X7F,0XFF,0XFF,0XFC,0X3E,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0X00,0X1F,0XFF,0XFF,0XFF,0XF1,0XFE,0X00,0XFF,0XFF,
0XFF,0XF0,0X3E,0XFF,0XFF,0XC6,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XF8,0X07,
0X8F,0XFF,0XFF,0XFF,0XF1,0XFE,0X87,0XFF,0XFF,0XFF,0XE0,0XCE,0XFF,0XFF,0XCE,0X7F,
0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XE0,0X1F,0X8F,0XC0,0X07,0XFF,0XF1,0XFE,0XFF,
0XFF,0XFF,0XFF,0X81,0X86,0XFF,0XFF,0XCE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XE0,0XFF,0XCF,0X80,0X07,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0X02,0X06,0XFF,0XFF,
0XC6,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XE3,0XFF,0XEF,0X00,0X07,0XFF,0XF1,
0XFE,0XFF,0XFF,0XFF,0XFE,0X0C,0X02,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFE,0X18,0X02,
0XFF,0XFF,0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,
0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFE,0X20,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X8F,0XFF,0XFE,0X01,0XFF,0X1F,0XFF,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFE,
0XC0,0X02,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XF0,0X01,0XFF,
0X9F,0XFF,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0X00,0X02,0XFF,0XFF,0XF8,0X00,0X7F,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XE0,0X01,0XE0,0X80,0X0F,0XFF,0XF1,0XFE,0XFF,0XFF,
0XFF,0XFF,0X00,0X02,0XFF,0XFF,0XF0,0X00,0X3F,0XFF,0XE7,0XFF,0XFF,0X8F,0XFF,0XE0,
0X03,0XE0,0X00,0X07,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0X80,0X06,0XFF,0XFF,0XE0,
0XCC,0X1F,0XFF,0XE0,0XFF,0XFF,0X8F,0XFF,0XE2,0X71,0XE0,0X00,0X07,0XFF,0XF1,0XFE,
0XFF,0XFF,0XFF,0XFF,0XC0,0X0E,0XFF,0XFF,0XE3,0XC7,0X1F,0XFF,0XE0,0X3F,0XFF,0X8F,
0XFF,0XE7,0X39,0XE0,0X00,0X0F,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0XC0,0X0E,0XFF,
0XFF,0XE7,0XE7,0X8F,0XFF,0XF0,0X07,0XFF,0X8F,0XFF,0XE7,0X38,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0X00,0X1E,0XFF,0XFF,0XE7,0XE7,0X8F,0XFF,0XFE,0X01,
0XFF,0X8F,0XFF,0XE3,0X10,0XFF,0XFF,0XFF,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFC,0X00,
0X3E,0XFF,0XFF,0XE3,0XC7,0X8F,0XFF,0XFF,0XC0,0X7F,0X8F,0XFF,0XE3,0X01,0XFF,0X1F,
0XC7,0XFF,0XF1,0XFE,0XFF,0X83,0XFF,0XF0,0X00,0X7E,0XFF,0XFF,0XE0,0X07,0X1F,0XFF,
0XFF,0XF8,0X3F,0X8F,0XFF,0XF3,0X81,0XFF,0X1F,0XC7,0XFF,0XF1,0XFE,0XFC,0X01,0XFF,
0XE0,0X00,0XFE,0XFF,0XFF,0XF0,0X0F,0X1F,0XFF,0XFF,0XC0,0X1F,0X8F,0XFF,0XFF,0XC7,
0XFF,0X1F,0XC7,0XFF,0XF1,0XFE,0XF0,0X07,0XFF,0X80,0X01,0XFE,0XFF,0XFF,0XF8,0X1F,
0XBF,0XFF,0XFE,0X00,0X0F,0X8F,0XFF,0XFF,0XFF,0XF8,0X00,0X07,0XFF,0XF1,0XFE,0XC0,
0X18,0XFE,0X00,0X03,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X07,0X87,0X8F,0XFF,
0XFF,0XFF,0XF8,0X00,0X0F,0XFF,0XF1,0XFE,0XC0,0XE0,0XF8,0X00,0X0F,0XFE,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE0,0X1F,0XC7,0X8F,0XFF,0XFF,0XFF,0XF8,0X00,0X0F,0XFF,0XF1,
0XFE,0XC7,0X00,0XE0,0X00,0X1F,0XFE,0XFF,0XFF,0XFF,0XFF,0X9F,0XFF,0XE0,0XFF,0XC7,
0X8F,0XFE,0X00,0X01,0XFF,0X1E,0XFF,0XFF,0XF1,0XFE,0XDC,0X00,0XC0,0X00,0X3F,0XFE,
0XFF,0XFF,0XF8,0X3F,0X1F,0XFF,0XE3,0XFF,0XC7,0X8F,0XFE,0X00,0X01,0XFF,0X1F,0XFF,
0XFF,0XF1,0XFE,0XE0,0X00,0X00,0X00,0XFF,0XFE,0XFF,0XFF,0XF0,0X0F,0X1F,0XFF,0XFF,
0XFF,0XC7,0X8F,0XFE,0X00,0X01,0XFF,0XFF,0XFF,0XFF,0XF1,0XFE,0XC0,0X00,0X00,0X03,
0XFF,0XFE,0XFF,0XFF,0XE0,0X03,0X1F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFE,0X03,0XFF,0XF8,
0X7F,0XFF,0XFF,0XF1,0XFE,0XE0,0X00,0X00,0X07,0XFF,0XFE,0XFF,0XFF,0XE3,0XC1,0X9F,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XC0,0X7F,0XF8,0X1F,0XFF,0XFF,0XF1,0XFE,0XE0,0X00,
0X00,0X1F,0XFF,0XFE,0XFF,0XFF,0XE7,0XE0,0X9F,0XFF,0XF8,0X00,0XFF,0X8F,0XFF,0XF8,
0X1F,0XF8,0X07,0XFF,0XFF,0XF1,0XFE,0XF0,0X00,0X00,0XFF,0XFF,0XFE,0XFF,0XFF,0XE7,
0XF8,0X1F,0XFF,0XF0,0X00,0XFF,0X8F,0XFF,0XFE,0X03,0XF8,0X01,0XFF,0XFF,0XF1,0XFE,
0XF8,0X00,0X03,0XFF,0XFF,0XFE,0XFF,0XFF,0XE7,0XFC,0X1F,0XFF,0XE0,0X00,0XFF,0X8F,
0XFF,0XFF,0X83,0XF8,0XC0,0X7F,0XFF,0XF1,0XFE,0XFC,0X00,0X3F,0XFF,0XFF,0XFE,0XFF,
0XFF,0XE3,0XFE,0X1F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFC,0X07,0XF8,0XF0,0X1F,0XFF,
0XF1,0XFE,0XFF,0XB7,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XF1,0XFF,0X1F,0XFF,0XE3,0X31,
0XFF,0X8F,0XFF,0XE0,0X3F,0XF8,0XFC,0X07,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0XFF,0XFF,0XF3,0XFF,0X9F,0XFF,0XE3,0X38,0XFF,0X8F,0XFF,0X00,0XFF,0XF8,0XFF,
0X03,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XE3,0X38,0XFF,0X8F,0XFE,0X07,0XFF,0XF8,0XFF,0XC3,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0X18,0XFF,0X8F,0XFE,0X00,0X01,
0XF8,0XFF,0XF3,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XDF,
0XFF,0XFF,0XE3,0X00,0XFF,0X8F,0XFE,0X00,0X01,0XF8,0XFF,0XFF,0XFF,0XF1,0XFE,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XE3,0X80,0XFF,0X8F,0XFE,
0X00,0X01,0XF8,0XFF,0XFF,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,
0XFF,0X87,0XFF,0XFF,0XF1,0X81,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,
0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XC3,0XFF,0XFF,0XFF,0XC3,0XFF,
0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,
0XFF,0XFF,0XFF,0XE3,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF1,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XF3,0XFF,0XFF,0XFF,
0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0X00,0X00,0X00,0X00,
0X00,0X01,0XFF,0XFF,0XFF,0XE3,0XFF,0XFC,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE3,0XFF,
0XFC,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC3,0XFF,0XFC,0X00,0X00,0XFF,0X8F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X87,0XFF,0XFC,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XE3,0XF1,0XFF,0X8F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X1F,0XFF,0XFF,0XE3,0XF9,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XE3,0XF8,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XE3,0XF8,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X01,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,
0XE1,0XF0,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XF0,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,
0XFF,0XFF,0XF0,0X01,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,0XF8,0X01,0XFF,0X8F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X87,0XFF,0XFF,0XFE,0X07,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,
0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XF0,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X70,0X3F,
0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,
0XFF,0XFA,0XFF,0XFF,0XFF,0XFF,0XF0,0X20,0X1F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XC0,0X1F,0XFF,0XFF,0XFF,0XE0,
0X02,0X1F,0XFF,0XE3,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,0XF1,0XFF,
0XFF,0XFF,0XFF,0X00,0X0F,0XFF,0XFF,0XFF,0XE3,0X87,0X1F,0XFF,0XE3,0XFF,0XFF,0X8F,
0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFE,0X00,0X07,0XFF,0XFF,
0XFF,0XE7,0X8F,0X8F,0XFF,0XE3,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,
0XF1,0XFF,0XFF,0XFF,0XFE,0X00,0X02,0X7F,0XFF,0XFF,0XE7,0XCF,0X8F,0XFF,0XF0,0XFF,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFC,0X00,0X00,
0X7F,0XFF,0XFF,0XE7,0XCF,0X9F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0X00,
0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0XFF,0XFF,0XFF,0XE3,0XFF,0X1F,0XFF,
0XE0,0X00,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XF8,
0X30,0X00,0XFF,0XFF,0XFF,0XF3,0XFE,0X1F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFE,0X00,
0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XF8,0X30,0X00,0XFF,0XFF,0XFF,0XF7,0XFF,
0X3F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XFF,
0XFF,0XF0,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0X01,0XFF,0X0F,0XFF,0XFF,0XF1,
0XFF,0XFF,0XFF,0X90,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XC0,0X7F,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0X10,0X00,0X00,0XFF,
0XFF,0XFF,0XF8,0X1F,0X1F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFF,0XE0,0X3F,0X0F,0XFF,
0XFF,0XF1,0XFF,0XFF,0XFC,0X10,0X00,0X00,0XFF,0XFF,0XFF,0XF0,0X0F,0X1F,0XFF,0XE0,
0X00,0XFF,0X8F,0XFF,0XFF,0XF8,0X1F,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XF8,0X18,0X30,
0X00,0XFF,0XFF,0XFF,0XE0,0X03,0X1F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFF,0XFC,0X07,
0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XF8,0X08,0X38,0X00,0XFF,0XFF,0XFF,0XE3,0XC1,0X9F,
0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0X03,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XF0,
0X08,0X30,0X01,0XFF,0XFF,0XFF,0XE7,0XF0,0X9F,0XFF,0XFF,0XE1,0XFF,0X8F,0XFF,0XFF,
0XFF,0X81,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XE0,0X08,0X00,0X01,0XFF,0XFF,0XFF,0XE7,
0XF8,0X1F,0XFF,0XFF,0XF9,0XFF,0X8F,0XFF,0XFF,0XFF,0XE0,0X0F,0XFF,0XFF,0XF1,0XFF,
0XFF,0XE0,0XE4,0X00,0X01,0XFF,0XFF,0XFF,0XE7,0XFC,0X1F,0XFF,0XFF,0XF8,0XFF,0X8F,
0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XE0,0XE2,0X00,0X03,0XFF,0XFF,
0XFF,0XE3,0XFE,0X1F,0XFF,0XFF,0XF8,0XFF,0X8F,0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,
0XF1,0XFF,0XFF,0XC0,0XE2,0X00,0X07,0XFF,0XFF,0XFF,0XF1,0XFF,0X1F,0XFF,0XE0,0X00,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFC,0X0F,0XFF,0XFF,0XF1,0XFF,0XFF,0XC0,0X41,0X00,0X0F,
0XFF,0XFF,0XFF,0XF3,0XFF,0X9F,0XFF,0XE0,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFE,0X0F,
0XFF,0XFF,0XF1,0XFF,0XFF,0XC0,0X00,0XC0,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XE0,0X01,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XC0,0X00,
0X30,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XC0,0X00,0X07,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,
0XC0,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XFF,0XFF,0XFF,0X07,0XFF,0XFF,0XF1,0XFF,0XFF,0XC0,0X00,0X00,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XE0,0XFC,0X01,0XFF,0XFF,0XF1,
0XFF,0XFF,0XC0,0X40,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XC0,0X78,0X00,0XFF,0XFF,0XF1,0XFF,0XFF,0XC0,0XE0,0X00,0X7F,0XFF,
0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0X87,0XFF,0X8F,0XFF,0XFF,0X80,0X38,0X00,0XFF,
0XFF,0XF1,0XFF,0XFF,0XE0,0XE0,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0X1E,
0X03,0XFF,0X8F,0XFF,0XFF,0X00,0X10,0X00,0X7F,0XFF,0XF1,0XFF,0XFF,0XE0,0XE0,0X00,
0X7F,0XFF,0XFF,0XFE,0XFF,0XBF,0XCF,0XFE,0X3E,0X01,0XFF,0X8F,0XFF,0XFF,0X00,0X10,
0X00,0X7F,0XFF,0XF1,0XFF,0XFF,0XE0,0X00,0X00,0X3F,0XFF,0XFF,0XFE,0X3F,0XFF,0X8F,
0XFE,0X3C,0X01,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0XF0,0X7F,0XFF,0XF1,0XFF,0XFF,0XF0,
0X00,0X00,0X3F,0XFF,0XFF,0XFF,0X3C,0X0F,0X9F,0XFE,0X3C,0X30,0XFF,0X8F,0XFF,0XFE,
0X0F,0X01,0XF8,0X3F,0XFF,0XF1,0XFF,0XFF,0XF8,0X00,0X01,0X1F,0XFF,0XFF,0XFF,0XF0,
0X03,0XFF,0XFE,0X3C,0X78,0XFF,0X8F,0XFF,0XFE,0X0F,0X81,0XFC,0X3F,0XFF,0XF1,0XFF,
0XFF,0XF8,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0XFF,0XFE,0X38,0X78,0XFF,0X8F,
0XFF,0XFE,0X1F,0XC3,0XFC,0X3F,0XFF,0XF1,0XFF,0XFF,0XFC,0X00,0X07,0XFF,0XFF,0XFF,
0XFF,0XC0,0X00,0XFF,0XFE,0X18,0X78,0XFF,0X8F,0XFF,0XFE,0X1F,0XC3,0XFC,0X3F,0XFF,
0XF1,0XFF,0XFF,0XFF,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X7F,0XFE,0X00,0XF8,
0XFF,0X8F,0XFF,0XFE,0X1F,0XC3,0XFC,0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,
0XFF,0XFF,0XFF,0X80,0X00,0X3F,0XFF,0X00,0XF8,0XFF,0X8F,0XFF,0XFE,0X1F,0XC3,0XFC,
0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X3F,0XFF,
0X01,0XF0,0XFF,0X8F,0XFF,0XFE,0X1F,0XC3,0XFC,0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X3F,0XFF,0XC3,0XF1,0XFF,0X8F,0XFF,0XFF,0X0F,
0XC3,0XFC,0X3F,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0X00,0X00,
0X31,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0X0F,0XFF,0XF8,0X3F,0XFF,0XF1,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0X00,0X00,0X31,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XFF,0X07,0XFF,0XF8,0X7F,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X80,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XF0,0X7F,0XFF,0XF1,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X80,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X80,0X00,0X7F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X7F,0XFF,0XFF,
0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X01,0XFF,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X78,0X03,0XDF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,
0X1F,0X8F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X7F,0XFF,0XCF,0XFF,0XFF,0XFF,0XFF,0X8F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFE,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0X00,0X00,
0X00,0X01,0X7F,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFD,0X80,0X00,0X00,0X03,0X1F,0XFF,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0X0F,0XF8,0X7F,0XFF,0XF1,0XFF,0XF8,
0X80,0X00,0X00,0X02,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XFF,0XFE,0X07,0XF8,0X3F,0XFF,0XF1,0XFF,0XF0,0X40,0X00,0X00,0X04,0X0F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFE,0X07,0XF0,0X3F,0XFF,0XF1,
0XFF,0XF0,0X60,0X00,0X00,0X0C,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X8F,0XFF,0XFF,0XFE,0X07,0XF0,0X3F,0XFF,0XF1,0XFF,0XF0,0X20,0X00,0X00,0X08,0X07,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFE,0X07,0XF0,0X3F,
0XFF,0XF1,0XFF,0XF0,0X30,0X00,0X00,0X10,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0X07,0XF8,0X7F,0XFF,0XF1,0XFF,0XF0,0X10,0X00,0X00,
0X30,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0X0F,
0XF8,0X7F,0XFF,0XF1,0XFF,0XF0,0X18,0X00,0X00,0X20,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X08,
0X00,0X00,0X60,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X04,0X00,0X00,0X40,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,
0XF0,0X06,0X00,0X00,0X80,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X02,0X00,0X01,0X80,0X07,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFF,0XF0,0X03,0X00,0X01,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X00,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X01,0X00,0X02,0X00,
0X07,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF1,0XFF,0XF0,0X01,0X80,0X06,0X00,0X07,0XFF,0XFF,0XFF,0XFC,0X00,0X00,
0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X80,
0X04,0X00,0X07,0XFF,0XFF,0XFF,0XF0,0X00,0X38,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X40,0X08,0X00,0X07,0XFF,0XFF,0XFF,0XE0,
0X00,0XFE,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,
0X00,0X40,0X08,0X00,0X07,0XFF,0XFF,0XFF,0XC0,0X03,0XFF,0X80,0X00,0XFF,0X8F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X20,0X10,0X00,0X07,0XFF,0XFF,
0XFF,0X80,0X0F,0XFF,0XF8,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,
0XFF,0XF0,0X00,0X30,0X30,0X00,0X07,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFC,0X00,0XFF,
0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X10,0X20,0X00,0X07,
0XFF,0XFF,0XFE,0X00,0XFF,0XE7,0XFE,0X00,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF1,0XFF,0XF0,0X00,0X18,0X40,0X00,0X07,0XFF,0XFF,0XFC,0X01,0XFF,0X81,0XFF,
0X00,0XFF,0X8F,0XFF,0XFF,0XF0,0X3F,0XFC,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X08,0XC0,
0X00,0X07,0XFF,0XFF,0XFC,0X01,0XFF,0X00,0X7F,0X00,0XFF,0X8F,0XFF,0XFF,0XC0,0X0F,
0XFC,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X04,0X80,0X00,0X07,0XFF,0XFF,0XF8,0X01,0XFF,
0XC0,0X7F,0X80,0XFF,0X8F,0XFF,0XFF,0X80,0X07,0XFC,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,
0X05,0X00,0X00,0X07,0XFF,0XFF,0XF8,0X00,0XFF,0XF8,0X00,0X00,0XFF,0X8F,0XFF,0XFF,
0X00,0X03,0XFC,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X03,0X00,0X00,0X07,0XFF,0XFF,0XF0,
0X00,0X1F,0XFE,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0X00,0X01,0XFC,0X3F,0XFF,0XF1,0XFF,
0XF0,0X00,0X03,0X00,0X00,0X07,0XFF,0XFF,0XF0,0X00,0X07,0XFF,0X80,0X00,0XFF,0X8F,
0XFF,0XFE,0X00,0X00,0XFC,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X01,0X00,0X00,0X07,0XFF,
0XFF,0XF1,0XFF,0X81,0XFF,0X80,0X00,0XFF,0X8F,0XFF,0XFE,0X07,0X80,0XFC,0X3F,0XFF,
0XF1,0XFF,0XF0,0X00,0X01,0X80,0X00,0X07,0XFF,0XFF,0XE0,0XFF,0X00,0X7F,0X80,0X00,
0XFF,0X8F,0XFF,0XFE,0X0F,0XE0,0X7C,0X3F,0XFF,0XF1,0XFF,0XF0,0X47,0X80,0X80,0X00,
0X07,0XFF,0XFF,0XE0,0X7F,0XC1,0X3F,0X80,0X00,0XFF,0X8F,0XFF,0XFE,0X1F,0XF0,0X3C,
0X3F,0XFF,0XF1,0XFF,0XF0,0X4F,0XC0,0X40,0X00,0X07,0XFF,0XFF,0XE0,0X3F,0XF9,0X4F,
0X00,0X00,0XFF,0X8F,0XFF,0XFE,0X1F,0XF8,0X1C,0X3F,0XFF,0XF1,0XFF,0XF0,0X4C,0X40,
0X40,0X00,0X07,0XFF,0XFF,0XE0,0X1F,0XFE,0X78,0X00,0X00,0XFF,0X8F,0XFF,0XFE,0X1F,
0XF8,0X0C,0X3F,0XFF,0XF1,0XFF,0XF0,0X64,0XC0,0X40,0X00,0X07,0XFF,0XFF,0XE0,0X0F,
0XFF,0X80,0X00,0X00,0XFF,0X8F,0XFF,0XFE,0X1F,0XFC,0X04,0X3F,0XFF,0XF1,0XFF,0XF0,
0X7F,0XC0,0X40,0X00,0X07,0XFF,0XFF,0XE0,0X05,0XFF,0XF0,0X00,0X00,0XFF,0X8F,0XFF,
0XFE,0X1F,0XFE,0X00,0X3F,0XFF,0XF1,0XFF,0XF0,0X1F,0X00,0XC0,0X00,0X07,0XFF,0XFF,
0XE0,0X00,0X3F,0XFC,0X00,0X00,0XFF,0X8F,0XFF,0XFF,0X0F,0XFF,0X00,0X3F,0XFF,0XF1,
0XFF,0XF0,0X00,0X00,0X80,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X0F,0XFF,0X00,0X00,0XFF,
0X8F,0XFF,0XFF,0X0F,0XFF,0X00,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X01,0X00,0X00,0X07,
0XFF,0XFF,0XE0,0X00,0X03,0XFF,0X80,0X00,0XFF,0X8F,0XFF,0XFF,0X07,0XFF,0XC0,0X3F,
0XFF,0XF1,0XFF,0XF0,0X00,0X01,0X00,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X07,0XFF,0X80,
0X01,0XFF,0X8F,0XFF,0XFF,0X87,0XFF,0XE0,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X02,0X00,
0X00,0X07,0XFF,0XFF,0XE0,0X00,0X3F,0XFF,0X00,0X01,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XF8,0X3F,0XFF,0XF1,0XFF,0XF0,0X00,0X06,0X00,0X00,0X07,0XFF,0XFF,0XE0,0X00,0XFF,
0XFC,0X00,0X01,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,
0X05,0X00,0X00,0X07,0XFF,0XFF,0XE0,0X01,0XFF,0XE0,0X00,0X01,0XFF,0X8F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X0D,0X80,0X00,0X07,0XFF,0XFF,0XE0,
0X01,0XFF,0X00,0X00,0X03,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,
0XF0,0X00,0X08,0X80,0X00,0X07,0XFF,0XFF,0XE0,0X01,0XFF,0X80,0X00,0X03,0XFF,0X8F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X10,0X40,0X00,0X07,0XFF,
0XFF,0XE0,0X00,0XFF,0XF0,0X00,0X03,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFF,0XF0,0X00,0X10,0X40,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X1F,0XFE,0X00,0X07,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X20,0X20,0X00,
0X07,0XFF,0XFF,0XE0,0X00,0X03,0XFF,0X80,0X07,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X60,0X30,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X07,0XFF,
0X80,0X0F,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0X40,
0X10,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X3F,0XFF,0X80,0X1F,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X00,0XC0,0X08,0X00,0X07,0XFF,0XFF,0XE0,0X01,
0XFF,0XFF,0X00,0X1F,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XF0,
0X00,0X80,0X0C,0X00,0X07,0XFF,0XFF,0XE0,0X01,0XFF,0XF8,0X00,0X3F,0XFF,0X8F,0XFF,
0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XF0,0X01,0X80,0X04,0X00,0X07,0XFF,0XFF,
0XE0,0X01,0XFF,0XE0,0X00,0X7F,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,
0XFF,0XF0,0X01,0X00,0X02,0X00,0X07,0XFF,0XFF,0XE0,0X01,0XFE,0X00,0X00,0XFF,0XFF,
0X8F,0XFF,0XFE,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XF0,0X02,0X00,0X03,0X00,0X07,
0XFF,0XFF,0XE0,0X01,0XF0,0X00,0X03,0XFF,0XFF,0X8F,0XFF,0XFE,0X00,0X00,0X00,0X3F,
0XFF,0XF1,0XFF,0XF0,0X06,0X00,0X01,0X00,0X07,0XFF,0XFF,0XE0,0X01,0X80,0X00,0X07,
0XFF,0XFF,0X8F,0XFF,0XFF,0X00,0X00,0X00,0X3F,0XFF,0XF1,0XFF,0XF0,0X04,0X00,0X01,
0X80,0X07,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X1F,0XFF,0XFF,0X8F,0XFF,0XFF,0X83,0XFF,
0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X0C,0X00,0X00,0X80,0X07,0XFF,0XFF,0XE0,0X00,0X00,
0X00,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0X81,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X08,
0X00,0X00,0X40,0X07,0XFF,0XFF,0XE0,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,
0XC1,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X18,0X00,0X00,0X60,0X07,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,
0XF0,0X10,0X00,0X00,0X20,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,
0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X20,0X00,0X00,0X10,0X07,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XFF,
0XF1,0XFF,0XF0,0X60,0X00,0X00,0X18,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF0,0X40,0X00,0X00,0X08,
0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF1,0XFF,0XF8,0XC0,0X00,0X00,0X04,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XF8,0X80,0X00,
0X00,0X04,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0X00,0X00,0X00,0X02,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF1,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,};
