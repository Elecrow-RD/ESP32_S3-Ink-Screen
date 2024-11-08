#ifndef _SPI_INIT_H_
#define _SPI_INIT_H_

#include "Arduino.h"

//项目板子
#define SCK 12
#define MOSI 11
#define RES 10
#define DC 13
#define CS 14
#define BUSY 9

#define EPD_SCK_Clr() digitalWrite(SCK, LOW)
#define EPD_SCK_Set() digitalWrite(SCK, HIGH)

#define EPD_MOSI_Clr() digitalWrite(MOSI, LOW)
#define EPD_MOSI_Set() digitalWrite(MOSI, HIGH)

#define EPD_RES_Clr() digitalWrite(RES, LOW)
#define EPD_RES_Set() digitalWrite(RES, HIGH)

#define EPD_DC_Clr() digitalWrite(DC, LOW)
#define EPD_DC_Set() digitalWrite(DC, HIGH)

#define EPD_CS_Clr() digitalWrite(CS, LOW)
#define EPD_CS_Set() digitalWrite(CS, HIGH)

#define EPD_ReadBusy digitalRead(BUSY)


void EPD_GPIOInit(void);
void EPD_WR_Bus(uint8_t dat);
void EPD_WR_REG(uint8_t reg);	
void EPD_WR_DATA8(uint8_t dat);

#endif
