/*****************************************************************************
* | File        :   EPD_SDCard.h
* | Author      :   Waveshare Team
* | Function    :   Show SDcard BMP picto e-paper
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* | This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __EPD_SDCARD_H__
#define __EPD_SDCARD_H__

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include <SD.h>


typedef struct {
    UDOUBLE Size;
    UDOUBLE Index ;
    UDOUBLE Header_Size ;
    UDOUBLE Bit_Pixel ;
    UDOUBLE BMP_Width;
    UDOUBLE BMP_Height;
} BMP_HEADER;
extern BMP_HEADER BMP_Header;


UWORD SDCard_Read16(File f);
UDOUBLE SDCard_Read32(File f);
boolean SDCard_ReadBmpHeader(File f);

void SDCard_Init(void);
void SDCard_ReadBMP(const char *BmpName, UWORD Xstart, UWORD Ystart);
void SDCard_Read_4GrayBMP(const char *BmpName, UWORD Xstart, UWORD Ystart);
void SDCard_Read_RGB_7Color(const char *path, UWORD Xstart, UWORD Ystart);
#endif


