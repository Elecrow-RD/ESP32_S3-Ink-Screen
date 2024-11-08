/*****************************************************************************
* | File        :   SPI_RAM.h
* | Author      :   Waveshare Team
* | Function    :   23LC1024 DRIVER
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2018-05-12
* | Info        :   Drive 23LC1024
*
******************************************************************************/
#ifndef __SPI_RAM_H_
#define __SPI_RAM_H_

#include "DEV_Config.h"
/**
 * SRAM opcodes
**/
#define CMD_WREN  0x06
#define CMD_WRDI  0x04
#define CMD_RDSR  0x05
#define CMD_WRSR  0x01
#define CMD_READ  0x03
#define CMD_WRITE 0x02

/**
 * SRAM modes
**/
#define BYTE_MODE   0x00
#define PAGE_MODE   0x80
#define STREAM_MODE 0x40


void SPIRAM_Set_Mode(UBYTE mode);

UBYTE SPIRAM_RD_Byte(UDOUBLE Addr);
void SPIRAM_WR_Byte(UDOUBLE Addr, UBYTE Data);

void SPIRAM_RD_Page(UDOUBLE Addr, UBYTE *pBuf);
void SPIRAM_WR_Page(UDOUBLE Addr, UBYTE *pBuf);

void SPIRAM_RD_Stream(UDOUBLE Addr, UBYTE *pBuf, UDOUBLE Len);
void SPIRAM_WR_Stream(UDOUBLE Addr, UBYTE *pBuf, UDOUBLE Len);

void SPIRAM_Usertest(void);
#endif
