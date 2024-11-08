/*****************************************************************************
* | File      	:   EPD_2IN66.c
* | Author      :   Waveshare team
* | Function    :   2.66inch e-paper
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-07-30
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_2in66.h"
#include "DEBUG.h"
#include "GUI_Paint.h"

static const UBYTE WF_PARTIAL[159] =
{
0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0A,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,0x22,0x22,
0x00,0x00,0x00,0x22,0x17,0x41,0xB0,0x32,0x36,
};  

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_2IN66_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(300);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(3);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(300);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_2IN66_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_2IN66_SendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

static void EPD_2IN66_ReadBusy_HIGH(void)
{
    DEBUG("e-Paper busy\r\n");
    UBYTE busy;
    do {
        busy = DEV_Digital_Read(EPD_BUSY_PIN);
    } while(busy);
    DEV_Delay_ms(200);
    DEBUG("e-Paper busy release\r\n");
}

/******************************************************************************
function :	set the look-up tables
parameter:
******************************************************************************/
void EPD_2IN66_Load_LUT(void)
{
	UWORD i;
	EPD_2IN66_SendCommand(0x32);
	for (i = 0; i < 153; i++) {
		EPD_2IN66_SendData(WF_PARTIAL[i]);
	}
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_2IN66_Init(void)
{
    EPD_2IN66_Reset();
    
	EPD_2IN66_ReadBusy_HIGH();
	EPD_2IN66_SendCommand(0x12);//soft  reset
	EPD_2IN66_ReadBusy_HIGH();
	/*	Y increment, X increment	*/
	EPD_2IN66_SendCommand(0x11);
	EPD_2IN66_SendData(0x03);
	/*	Set RamX-address Start/End position	*/
	EPD_2IN66_SendCommand(0x44);
	EPD_2IN66_SendData(0x01);	
	EPD_2IN66_SendData((EPD_2IN66_WIDTH % 8 == 0)? (EPD_2IN66_WIDTH / 8 ): (EPD_2IN66_WIDTH / 8 + 1) );
	/*	Set RamY-address Start/End position	*/
	EPD_2IN66_SendCommand(0x45);
	EPD_2IN66_SendData(0);
	EPD_2IN66_SendData(0);
	EPD_2IN66_SendData((EPD_2IN66_HEIGHT&0xff));
	EPD_2IN66_SendData((EPD_2IN66_HEIGHT&0x100)>>8);

	EPD_2IN66_ReadBusy_HIGH();
}

/******************************************************************************
function :  Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_2IN66_Init_Partial(void)
{
    EPD_2IN66_Reset();
    
    EPD_2IN66_ReadBusy_HIGH();
    EPD_2IN66_SendCommand(0x12);//soft  reset
    EPD_2IN66_ReadBusy_HIGH();
   
    EPD_2IN66_Load_LUT();
    EPD_2IN66_SendCommand(0x37); 
    EPD_2IN66_SendData(0x00);  
    EPD_2IN66_SendData(0x00);  
    EPD_2IN66_SendData(0x00);  
    EPD_2IN66_SendData(0x00); 
    EPD_2IN66_SendData(0x00);  	
    EPD_2IN66_SendData(0x40);  
    EPD_2IN66_SendData(0x00);  
    EPD_2IN66_SendData(0x00);   
    EPD_2IN66_SendData(0x00);  
    EPD_2IN66_SendData(0x00);

	/* Y increment, X increment */
    EPD_2IN66_SendCommand(0x11);
    EPD_2IN66_SendData(0x03);
    /*	Set RamX-address Start/End position	*/
    EPD_2IN66_SendCommand(0x44);
    EPD_2IN66_SendData(0x01); 
    EPD_2IN66_SendData((EPD_2IN66_WIDTH % 8 == 0)? (EPD_2IN66_WIDTH / 8 ): (EPD_2IN66_WIDTH / 8 + 1) );
    /*	Set RamY-address Start/End position	*/
    EPD_2IN66_SendCommand(0x45);
    EPD_2IN66_SendData(0);
    EPD_2IN66_SendData(0);
    EPD_2IN66_SendData((EPD_2IN66_HEIGHT&0xff));
    EPD_2IN66_SendData((EPD_2IN66_HEIGHT&0x100)>>8);

    EPD_2IN66_SendCommand(0x3C); 
    EPD_2IN66_SendData(0x80);   

    EPD_2IN66_SendCommand(0x22); 
    EPD_2IN66_SendData(0xcf); 
    EPD_2IN66_SendCommand(0x20); 
    EPD_2IN66_ReadBusy_HIGH();
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void TurnOnDisplay(void)
{
    EPD_2IN66_SendCommand(0x20);
    EPD_2IN66_ReadBusy_HIGH();
}

/******************************************************************************
function :  Clear screen
parameter:
******************************************************************************/
void EPD_2IN66_Clear(void)
{
	UWORD i;
	UWORD IMAGE_COUNTER = (EPD_2IN66_WIDTH / 8) * EPD_2IN66_HEIGHT;

	EPD_2IN66_SendCommand(0x24);
	for (i = 0; i < IMAGE_COUNTER; i++) {
		EPD_2IN66_SendData(0xff);
	}

	TurnOnDisplay(); 
}

/******************************************************************************
function :  Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_2IN66_Display(void)
{
  UWORD i;
  UWORD IMAGE_COUNTER = (EPD_2IN66_WIDTH / 8) * EPD_2IN66_HEIGHT;
  
  EPD_2IN66_SendCommand(0x24);
  for (i = 0; i < IMAGE_COUNTER; i++) {
	  EPD_2IN66_SendData(SPIRAM_RD_Byte(i));
  }

	TurnOnDisplay();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_2IN66_Sleep(void)
{
    EPD_2IN66_SendCommand(0X10);
    EPD_2IN66_SendData(0x01);
}
