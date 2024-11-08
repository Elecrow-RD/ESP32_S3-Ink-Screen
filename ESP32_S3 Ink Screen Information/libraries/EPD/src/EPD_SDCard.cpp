/*****************************************************************************
* | File        :   EPD_SDCard.cpp
* | Author      :   Waveshare team
* | Function    :   Read the BMP file in the SD card and parse it
* | Info        :
*----------------
* | This version:   V1.1
* | Date        :   2020-07-13
* | Info        :   V1.1
* -----------------------------------------------------------------------------
* V1.1(2020-07-13):
* 1.Add: SDCard_Read_RGB_7Color(const char *path, UWORD Xstart, UWORD Ystart)
*		read bmp data to SPIRAM for 5.65f e-Paper
*
******************************************************************************/
#include "EPD_SDCard.h"
#include "Debug.h"
#include "GUI_Paint.h"
BMP_HEADER BMP_Header;

/******************************************************************************
function:	Read 2 bytes of data and convert to big endian
parameter:
Info:
    These read data from the SD card file and convert them to big endian 
    (the data is stored in little endian format!)
******************************************************************************/
UWORD SDCard_Read16(File f)
{
    UWORD d;
    UBYTE b;
    b = f.read();
    d = f.read();
    d <<= 8;
    d |= b;
    return d;
}

/******************************************************************************
function:	Read 4 bytes of data and convert to big endian
parameter:
Info:
    These read data from the SD card file and convert them to big endian 
    (the data is stored in little endian format!)
******************************************************************************/
UDOUBLE SDCard_Read32(File f)
{
    UDOUBLE d;
    UWORD b;

    b = SDCard_Read16(f);
    d = SDCard_Read16(f);
    d <<= 16;
    d |= b;
    return d;
}

/******************************************************************************
function:	Reading BMP Picture Files header and Information header 
parameter:
Info:
    These read data from the SD card file and convert them to big endian 
    (the data is stored in little endian format!)
******************************************************************************/
boolean SDCard_ReadBmpHeader(File f)
{
    UWORD File_Type;
    File_Type = SDCard_Read16(f) ;//0000h 2byte: file type

    if (File_Type != 0x4D42) {
        // magic bytes missing
        return false;
    }

    // read file size
    BMP_Header.Size = SDCard_Read32(f);//0002h 4byte: file size

    // read and ignore creator bytes
    SDCard_Read32(f);//0006h 4byte:

    BMP_Header.Index = SDCard_Read32(f);//000ah 4byte: Offset between file head and image (offbits)

    // read DIB header
    BMP_Header.Header_Size = SDCard_Read32(f);//000Eh 4byte: Bitmap header = 40

    BMP_Header.BMP_Width = SDCard_Read32(f);//12-15:Image wide
    DEBUG("BMP_Width = ");
    DEBUG(BMP_Header.BMP_Width);
    DEBUG("\n");
    BMP_Header.BMP_Height = SDCard_Read32(f);//16-19:Image high
    DEBUG("BMP_Header = ");
    DEBUG(BMP_Header.BMP_Height);
    DEBUG("\n");
    if (SDCard_Read16(f) != 1)//1A-1B :0 for the use of the palette, 1 for the number of color indices
        return false;

    BMP_Header.Bit_Pixel = SDCard_Read16(f);//1C-1D：Whether the image is compressed

    if (SDCard_Read32(f) != 0) {//1E-21：
        // compression not supported!
        return false;
    }

    return true;
}

/******************************************************************************
function:	Initialize the SD card
parameter:
Info:
    If the initialization fails, stop the game until the 
    initialization is successful
******************************************************************************/
void SDCard_Init(void)
{
    SD_CS_1;

    Sd2Card card;
    card.init(SPI_FULL_SPEED, SD_CS);
    if (!SD.begin(SD_CS))  {
        DEBUG("SD init failed!\n");
        while (1);                              // init fail, die here
    }
    DEBUG("SD init OK!\n");
}

/******************************************************************************
function:	Read BMP image data to SPIRAM
parameter:
    BmpName : BMP picture name,
    Xstart : x starting position
    Ystart: Y starting position
Info:
    If the initialization fails, stop the game until the initialization is successful
******************************************************************************/
void SDCard_ReadBMP(const char *BmpName, UWORD Xstart, UWORD Ystart)
{
    File bmpFile;
    bmpFile = SD.open(BmpName);
    if (!bmpFile) {
        DEBUG("not find : ");
        DEBUG(BmpName);
        DEBUG("\n");
        return;
    } else {
        DEBUG("open bmp file : ");
        DEBUG(BmpName);
        DEBUG("\n");
    }

    if (!SDCard_ReadBmpHeader(bmpFile)) {
        DEBUG("read bmp file error\n");
        return;
    }

    bmpFile.seek(BMP_Header.Index);

    UWORD X, Y;
    UWORD Image_Width_Byte = (BMP_Header.BMP_Width % 8 == 0)? (BMP_Header.BMP_Width / 8): (BMP_Header.BMP_Width / 8 + 1);
    UWORD Bmp_Width_Byte = (Image_Width_Byte % 4 == 0) ? Image_Width_Byte: ((Image_Width_Byte / 4 + 1) * 4);

    UBYTE ReadBuff[1] = {0};
    for(Y = Ystart; Y < BMP_Header.BMP_Height; Y++) {//Total display column
        for(X = Xstart / 8; X < Bmp_Width_Byte; X++) {//Show a line in the line
            bmpFile.read(ReadBuff, 1);
            if(X < Image_Width_Byte) { //bmp
                if(Paint_Image.Image_Color == IMAGE_COLOR_POSITIVE) {
                    SPIRAM_WR_Byte(X + (BMP_Header.BMP_Height - Y - 1) * Image_Width_Byte + Paint_Image.Image_Offset, ReadBuff[0]);
                } else {
                    SPIRAM_WR_Byte(X + (BMP_Header.BMP_Height - Y - 1) * Image_Width_Byte + Paint_Image.Image_Offset, ~ReadBuff[0]);
                }
            }
        }
    }

    bmpFile.close();
}

void SDCard_Read_4GrayBMP(const char *BmpName, UWORD Xstart, UWORD Ystart)
{
    File bmpFile;
    bmpFile = SD.open(BmpName);
    if (!bmpFile) {
        DEBUG("not find : ");
        DEBUG(BmpName);
        DEBUG("\n");
        return;
    } else {
        DEBUG("open bmp file : ");
        DEBUG(BmpName);
        DEBUG("\n");
    }

    if (!SDCard_ReadBmpHeader(bmpFile)) {
        DEBUG("read bmp file error\n");
        return;
    }

    bmpFile.seek(BMP_Header.Index);

    UWORD X, Y;
    UWORD Bmp_Width_Byte = BMP_Header.BMP_Width/2;
	
	DEBUG("Bmp_Width_Byte : ");
	DEBUG(Bmp_Width_Byte);
	DEBUG("\n");
	
	DEBUG("BMP_Header.BMP_Height : ");
	DEBUG(BMP_Header.BMP_Height);
	DEBUG("\n");
	
    UBYTE ReadBuff[1] = {0};
    for(Y = Ystart; Y < BMP_Header.BMP_Height; Y++) {//Total display column
        for(X = Xstart / 4; X < Bmp_Width_Byte; X++) {//Show a line in the line
            bmpFile.read(ReadBuff, 1);
            if(X < Bmp_Width_Byte) { //bmp
				//DEBUG((ReadBuff[0]>>6)&0x03);
				//DEBUG(" ");
				if(Paint_Image.Image_Color == IMAGE_COLOR_POSITIVE) {
					Paint_DrawPixel(X*2,   Ystart+BMP_Header.BMP_Height-Y, (ReadBuff[0]>>6)&0x03);
					Paint_DrawPixel(X*2+1, Ystart+BMP_Header.BMP_Height-Y, (ReadBuff[0]>>2)&0x03);
				} else {
					Paint_DrawPixel(X*2,   Ystart+BMP_Header.BMP_Height-Y, ~(ReadBuff[0]>>6)&0x03);
					Paint_DrawPixel(X*2+1, Ystart+BMP_Header.BMP_Height-Y, ~(ReadBuff[0]>>2)&0x03);
				
				}
            }
        }
    }

    bmpFile.close();
}

/******************************************************************************
function:	Read BMP image(just suit 5.65f e-Paper) data to SPIRAM
parameter:
    path : BMP picture name,
    Xstart : x starting position
    Ystart: Y starting position
Info:
    If the initialization fails, stop the game until the initialization is successful
******************************************************************************/
void SDCard_Read_RGB_7Color(const char *path, UWORD Xstart, UWORD Ystart)
{
    File bmpFile;
    /* 1.Open file read file header */
    bmpFile = SD.open(path);
    if (!bmpFile) {
        DEBUG("not find : ");
        DEBUG(path);
        DEBUG("\n");
        return;
    } else {
        DEBUG("open bmp file : ");
        DEBUG(path);
        DEBUG("\n");
    }
	
    if (!SDCard_ReadBmpHeader(bmpFile)) {
        DEBUG("read bmp file error\n");
        return;
    }

    /* 2.Get BMP file data pointer */
    bmpFile.seek(BMP_Header.Index);

    UWORD X, Y;
    UWORD Bmp_Width_Byte = BMP_Header.BMP_Width;
	UWORD Bmp_Height_Byte = BMP_Header.BMP_Height;
	
	DEBUG("Bmp_Width_Byte : ");
	DEBUG(Bmp_Width_Byte);
	DEBUG("\n");
	
	DEBUG("Bmp_Height_Byte : ");
	DEBUG(Bmp_Height_Byte);
	DEBUG("\n");
    UBYTE ReadBuff[3] = {0};
		
    /* 3.Write data into RAM */
    for(Y = Bmp_Height_Byte + Ystart; Y > Ystart; Y--) {//Total display column
        for(X =  Xstart; X < Bmp_Width_Byte + Xstart; X++) {//Show a line in the line									

						bmpFile.read((char *)ReadBuff, 1);
						bmpFile.read((char *)ReadBuff + 1, 1);
						bmpFile.read((char *)ReadBuff + 2, 1);
						
						if(ReadBuff[0] == 0 && ReadBuff[1] == 0 && ReadBuff[2] == 0){
							Paint_DrawPixel(X, Y, 0x00);//Black
						}else if(ReadBuff[0] == 255 && ReadBuff[1] == 255 && ReadBuff[2] == 255){
							Paint_DrawPixel(X, Y, 0x01);//White
						}else if(ReadBuff[0] == 0 && ReadBuff[1] == 255 && ReadBuff[2] == 0){
							Paint_DrawPixel(X, Y, 0x02);//Green
						}else if(ReadBuff[0] == 255 && ReadBuff[1] == 0 && ReadBuff[2] == 0){
							Paint_DrawPixel(X, Y, 0x03);//Blue
						}else if(ReadBuff[0] == 0 && ReadBuff[1] == 0 && ReadBuff[2] == 255){
							Paint_DrawPixel(X, Y, 0x04);//Red
						}else if(ReadBuff[0] == 0 && ReadBuff[1] == 255 && ReadBuff[2] == 255){
							Paint_DrawPixel(X, Y, 0x05);//Yellow
						}else if(ReadBuff[0] == 0 && ReadBuff[1] == 128 && ReadBuff[2] == 255){
							Paint_DrawPixel(X, Y, 0x06);//Orange
						}						
        }
    }
    bmpFile.close();
}

