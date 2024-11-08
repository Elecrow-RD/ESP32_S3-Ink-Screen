#ifndef _EPD_INIT_H_
#define _EPD_INIT_H_

#include "spi.h"
//Due to the 5.97Inch E-Paper screen being controlled by two SSD1683 ICs
//And the resolution of SSD1683 is 400x300, while the resolution of E-Paper is 792x272
//So the master-slave chips are cascaded together with a resolution of 396x272 for display
//Resulting in 8 columns of pixel space at the junction of two ICs, so address offset is required for display
//Therefore, the program defines EPD_W EPD_H as 800x272, and the actual display area is still 792x272
//If the EPD_Display function is directly used to call the full screen display of images, a modulus resolution of 800x272 is required
//If the EPD_ShowPicture function is used to display images in full screen, the modulus resolution is 792x272
#define EPD_W	800
#define EPD_H	272

#define WHITE 0xFF
#define BLACK 0x00

#define ALLSCREEN_GRAGHBYTES  27200/2

#define Source_BYTES 400/8
#define Gate_BITS  	 272
#define ALLSCREEN_BYTES Source_BYTES*Gate_BITS

void EPD_READBUSY(void);
void EPD_HW_RESET(void);
void EPD_Update(void);
void EPD_PartUpdate(void);
void EPD_FastUpdate(void);
void EPD_DeepSleep(void);
void EPD_Init(void);
void EPD_FastMode1Init(void);
void EPD_SetRAMMP(void);
void EPD_SetRAMMA(void);
void EPD_SetRAMSP(void);
void EPD_SetRAMSA(void);
void EPD_Clear_R26A6H(void);
void EPD_Display_Clear(void);
void EPD_Display(const uint8_t *ImageBW);
void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas);
#endif
