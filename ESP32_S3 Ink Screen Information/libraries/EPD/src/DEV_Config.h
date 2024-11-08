/*****************************************************************************
* | File      	: DEV_Config.h
* | Author      : Waveshare team
* | Function    :	debug with prntf
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "Debug.h"
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * SPI RAM
**/
#define SPIRAM_CS 5
#define SPIRAM_CS_0     digitalWrite(SPIRAM_CS, LOW)
#define SPIRAM_CS_1     digitalWrite(SPIRAM_CS, HIGH)

/**
 * SD Card
**/
#define SD_CS 6
#define SD_CS_0     digitalWrite(SD_CS, LOW)
#define SD_CS_1     digitalWrite(SD_CS, HIGH)
/**
 * e-Paper GPIO
**/
#define EPD_CS 10
#define EPD_CS_0     digitalWrite(EPD_CS, LOW)
#define EPD_CS_1     digitalWrite(EPD_CS, HIGH)

#define EPD_DC 9
#define EPD_DC_0     digitalWrite(EPD_DC, LOW)
#define EPD_DC_1     digitalWrite(EPD_DC, HIGH)

#define EPD_RST 8
#define EPD_RST_0     digitalWrite(EPD_RST, LOW)
#define EPD_RST_1     digitalWrite(EPD_RST, HIGH)

#define EPD_BUSY 7
#define EPD_BUSY_RD   digitalRead(EPD_BUSY)


#define EPD_RST_PIN     EPD_RST
#define EPD_DC_PIN      EPD_DC
#define EPD_CS_PIN      EPD_CS
#define EPD_BUSY_PIN    EPD_BUSY

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_Digital_Read(_pin) digitalRead(_pin)

/**
 * SPI
**/
#define DEV_SPI_WriteByte(_dat)   SPI.transfer(_dat)
#define DEV_SPI_ReadByte(_dat) SPI.transfer(_dat)

void DEV_Delay_ms(UWORD xms);
void DEV_Delay_us(UWORD xus);
UBYTE DEV_Module_Init(void);
void DEV_Module_Exit(void);



#endif

