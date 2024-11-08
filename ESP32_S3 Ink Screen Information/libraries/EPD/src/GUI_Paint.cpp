/*****************************************************************************
* | File      	:	GUI_Paint.cpp
* | Author      :   Waveshare team
* | Function    :	Achieve drawing: draw points, lines, boxes, circles and
*                   their size, solid dotted line, solid rectangle hollow
*					rectangle, solid circle hollow circle.
* | Info        :
*   Achieve display characters: Display a single character, string, number
*   Achieve time display: adaptive size display time minutes and seconds
*----------------
* |	This version:   V1.1
* | Date        :   2020-07-13
* | Info        :
* -----------------------------------------------------------------------------
* V1.1(2020-07-13):
* 1.Change: Paint_SetScale(UBYTE scale)
*		 Add scale 7 for 5.65f e-Parper
* 2.Change: Paint_DrawPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color)
*		 Add the branch for scale 7
* 3.Change: Paint_Clear(UWORD Color)
*		 Add the branch for scale 7
*
******************************************************************************/
#include "GUI_Paint.h"
#include "DEV_Config.h"
#include "Debug.h"
#include <stdint.h>

//SPI Ram
PAINT_IMAGE Paint_Image;

/******************************************************************************
function :	Exchange two numbers of data
parameter:
    Point1: The Xpoint coordinate of the point
    Point2: The Ypoint coordinate of the point
******************************************************************************/
static void Paint_Swop(UWORD Point1, UWORD Point2)
{
    UWORD Temp;
    Temp = Point1;
    Point1 = Point2;
    Point2 = Temp;
}

/******************************************************************************
function:	Create Image
parameter:
    Width   :   The width of the picture
    Height  :   The height of the picture
    Rotate  :   Image flip degree
    Color   :   Whether the picture is inverted
******************************************************************************/
void Paint_NewImage(UWORD Image_Name, UWORD Width, UWORD Height, UWORD Rotate, UWORD Color)
{
    SPIRAM_Set_Mode(BYTE_MODE);

    if(Rotate == IMAGE_ROTATE_0 || Rotate == IMAGE_ROTATE_180) {
        Paint_Image.Image_Width = Width;
        Paint_Image.Image_Height = Height;
    } else {
        Paint_Image.Image_Width = Height;
        Paint_Image.Image_Height = Width;
    }
    Paint_Image.Image_Name = Image_Name;//At least one picture
    Paint_Image.Image_Rotate = Rotate;
    Paint_Image.Memory_Width = Width;
    Paint_Image.Memory_Height = Height;
    Paint_Image.Image_Color = Color;
	Paint_Image.Scale = 2;
	Paint_Image.Mirror = MIRROR_NONE;
		
    UWORD BYTE_Height = Paint_Image.Memory_Height;
    UWORD BYTE_Width = (Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1);
    Paint_Image.Image_Offset =  Paint_Image.Image_Name * (BYTE_Height * BYTE_Width);
}

/******************************************************************************
function:	Draw Pixels
parameter:
    Xpoint  :   At point X
    Ypoint  :   At point Y
    Color   :   Painted colors
******************************************************************************/
static void Paint_DrawPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
    // UWORD Height = Paint_Image.Memory_Height;
    UWORD Width = (Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1);
    UDOUBLE Offset = Paint_Image.Image_Offset;
	
		switch(Paint_Image.Mirror) {
    case MIRROR_NONE:
        break;
    case MIRROR_HORIZONTAL:
        Xpoint = Paint_Image.Memory_Width - Xpoint - 1;
        break;
    case MIRROR_VERTICAL:
        Ypoint = Paint_Image.Memory_Height - Ypoint - 1;
        break;
    case MIRROR_ORIGIN:
        Xpoint = Paint_Image.Memory_Width - Xpoint - 1;
        Ypoint = Paint_Image.Memory_Height - Ypoint - 1;
        break;
    default:
        return;
    }
	
    UDOUBLE Addr = Xpoint / 8 + Ypoint * Width + Offset;
    UBYTE Rdata = SPIRAM_RD_Byte(Addr);

	if(Paint_Image.Scale == 2){
		UWORD Width = (Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1);
		UDOUBLE Addr = Xpoint / 8 + Ypoint * Width + Offset;
		UBYTE Rdata = SPIRAM_RD_Byte(Addr);
		if(Paint_Image.Image_Color == IMAGE_COLOR_POSITIVE) {
			if(Color == BLACK)
				SPIRAM_WR_Byte(Addr, Rdata & ~(0x80 >> (Xpoint % 8)));
			else
				SPIRAM_WR_Byte(Addr, Rdata | (0x80 >> (Xpoint % 8)));
		} else {
			if(Color == WHITE)
				SPIRAM_WR_Byte(Addr, Rdata & ~(0x80 >> (Xpoint % 8)));
			else
				SPIRAM_WR_Byte(Addr, Rdata | (0x80 >> (Xpoint % 8)));
		}
	}else if(Paint_Image.Scale == 4){
		UWORD Width = (Paint_Image.Memory_Width % 4 == 0)? (Paint_Image.Memory_Width / 4 ): (Paint_Image.Memory_Width / 4 + 1);
		UDOUBLE Addr = Xpoint / 4 + Ypoint * Width + Offset;
		Color = Color % 4;//Guaranteed color scale is 4  --- 0~3
		UBYTE Rdata = SPIRAM_RD_Byte(Addr);
		
		Rdata = Rdata & (~(0xC0 >> ((Xpoint % 4)*2)));
		SPIRAM_WR_Byte(Addr, Rdata | ((Color << 6) >> ((Xpoint % 4)*2)));
    }else if(Paint_Image.Scale == 7){
		UDOUBLE Width = Paint_Image.Memory_Width*3%8 == 0 ? Paint_Image.Memory_Width*3/8 : Paint_Image.Memory_Width*3/8+1;
		//UWORD Width = 225;
		UDOUBLE Addr = (Xpoint * 3) / 8 + Ypoint * Width;
		UBYTE shift, Rdata, Rdata2;
		shift = (Xpoint+Ypoint*Paint_Image.Memory_Height) % 8;
		switch(shift) {
			case 0 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0x1f;
				Rdata = Rdata | ((Color << 5) & 0xe0);
				SPIRAM_WR_Byte(Addr, Rdata);
				break;
			case 1 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0xe3;
				Rdata = Rdata | ((Color << 2) & 0x1c);
				SPIRAM_WR_Byte(Addr, Rdata);
				break;
			case 2 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0xfc;
				Rdata2 = SPIRAM_RD_Byte(Addr + 1) & 0x7f;
				Rdata = Rdata | ((Color >> 1) & 0x03);
				Rdata2 = Rdata2 | ((Color << 7) & 0x80);
				SPIRAM_WR_Byte(Addr, Rdata);
				SPIRAM_WR_Byte(Addr + 1, Rdata2);
				break;
			case 3 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0x8f;
				Rdata = Rdata | ((Color << 4) & 0x70);
				SPIRAM_WR_Byte(Addr, Rdata);
				break;
			case 4 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0xf1;
				Rdata = Rdata | ((Color << 1) & 0x0e);
				SPIRAM_WR_Byte(Addr, Rdata);
				break;
			case 5 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0xfe;
				Rdata2 = SPIRAM_RD_Byte(Addr + 1) & 0x3f;
				Rdata = Rdata | ((Color >> 2) & 0x01);
				Rdata2 = Rdata2 | ((Color << 6) & 0xc0);
				SPIRAM_WR_Byte(Addr, Rdata);
				SPIRAM_WR_Byte(Addr + 1, Rdata2);
				break;
			case 6 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0xc7;
				Rdata = Rdata | ((Color << 3) & 0x38);
				SPIRAM_WR_Byte(Addr, Rdata);
				break;
			case 7 :
				Rdata = SPIRAM_RD_Byte(Addr) & 0xf8;
				Rdata = Rdata | (Color & 0x07);
				SPIRAM_WR_Byte(Addr, Rdata);
				break;						
		}	
	}
}

/******************************************************************************
function:	Select Image mirror
parameter:
    mirror   :Not mirror,Horizontal mirror,Vertical mirror,Origin mirror
******************************************************************************/
void Paint_SetMirroring(UBYTE mirror)
{
    if(mirror == MIRROR_NONE || mirror == MIRROR_HORIZONTAL || 
        mirror == MIRROR_VERTICAL || mirror == MIRROR_ORIGIN) {
        DEBUG("mirror image");
        Paint_Image.Mirror = mirror;
    } else {
        DEBUG("mirror should be MIRROR_NONE, MIRROR_HORIZONTAL MIRROR_VERTICAL or MIRROR_ORIGIN\r\n");
    }
}

void Paint_SetScale(UBYTE scale)
{
	if(scale == 2) {
		Paint_Image.Scale = 2;
		UWORD BYTE_Height = Paint_Image.Memory_Height;
		UWORD BYTE_Width = (Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1);
		Paint_Image.Image_Offset =  Paint_Image.Image_Name * (BYTE_Height * BYTE_Width);
	} else if(scale == 4) {
		Paint_Image.Scale = 4;
		UWORD BYTE_Height = Paint_Image.Memory_Height;
		UWORD BYTE_Width = (Paint_Image.Memory_Width % 4 == 0)? (Paint_Image.Memory_Width / 4 ): (Paint_Image.Memory_Width / 4 + 1);
		Paint_Image.Image_Offset =  Paint_Image.Image_Name * (BYTE_Height * BYTE_Width);
    }else if(scale == 7){//Only applicable with 5in65 e-Paper
		Paint_Image.Scale = 7;
		UWORD BYTE_Height = Paint_Image.Memory_Height;
		UWORD BYTE_Width = (Paint_Image.Memory_Width % 2 == 0)? (Paint_Image.Memory_Width / 2 ): (Paint_Image.Memory_Width / 2 + 1);
		Paint_Image.Image_Offset =  Paint_Image.Image_Name * (BYTE_Height * BYTE_Width);
	}else {
		DEBUG("Set Scale Input parameter error\r\n");
		DEBUG("Scale Only support: 2 4 7\r\n");
	}
}
/******************************************************************************
function:	Clear the color of the picture
parameter:
    Color   :   Painted colors
******************************************************************************/
void Paint_Clear(UWORD Color)
{
	UWORD Height = Paint_Image.Memory_Height;
	UDOUBLE Width = Paint_Image.Memory_Width; 
	if(Paint_Image.Image_Color == IMAGE_COLOR_INVERTED) {
		Color = ~Color;
	}
	if(Paint_Image.Scale == 2) {
		Width = ((Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1));
		UDOUBLE Offset = Paint_Image.Image_Offset;
		for (UWORD Y = 0; Y < Height; Y++) {
			for (UWORD X = 0; X < Width; X++ ) {//8 pixel =  1 byte
				SPIRAM_WR_Byte((X + Y * Width) + Offset, Color);
			}
		}
	} else if(Paint_Image.Scale == 4) {
		Width = (Paint_Image.Memory_Width % 4 == 0)? (Paint_Image.Memory_Width / 4 ): (Paint_Image.Memory_Width / 4 + 1);
		UDOUBLE Offset = Paint_Image.Image_Offset;
		if(Color%4 == 0x00) {
			Color = 0x00;
		}else if(Color%4 == 0x01) {
			Color = 0x55;
		}else if(Color%4 == 0x02) {
			Color = 0xAA;
		}else if(Color%4 == 0x03) {
			Color = 0xff;
		}
		
		for (UWORD Y = 0; Y < Height; Y++) {
			for (UWORD X = 0; X < Width; X++ ) {//8 pixel =  1 byte
				SPIRAM_WR_Byte((X + Y * Width) + Offset, Color);
			}
		}
	} else if(Paint_Image.Scale == 7) {
		Color = (UBYTE)Color;
		Width = (Paint_Image.Memory_Width * 3 % 8 == 0)? (Paint_Image.Memory_Width * 3 / 8 ): (Paint_Image.Memory_Width * 3 / 8 + 1);
		for (UDOUBLE Y = 0; Y < Height; Y++) {
			for (UDOUBLE X = 0; X < Width; X++ ) {
				if((X + Y * Width)%3 == 0) 
					SPIRAM_WR_Byte((X + Y * Width), (Color<<5) | (Color<<2) | (Color>>1));							
				else if((X + Y * Width)%3 == 1) 
					SPIRAM_WR_Byte((X + Y * Width), (Color<<7) | (Color<<4) | (Color<<1) | (Color>>2));				
				else if((X + Y * Width)%3 == 2)
					SPIRAM_WR_Byte((X + Y * Width), (Color<<6) |  (Color<<3) |  Color);				
			}
		}
	}
}

/******************************************************************************
function:	Set the pixel, according to the flip of the picture,
            to convert the coordinates
parameter:
    Xpoint  :   At point X
    Ypoint  :   At point Y
    Color   :   Painted colors
******************************************************************************/
static void Paint_SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
    UWORD X, Y;
    switch(Paint_Image.Image_Rotate) {
    case IMAGE_ROTATE_0:
        X = Xpoint;
        Y = Ypoint;
        Paint_DrawPixel(X, Y, Color);
        break;
    case IMAGE_ROTATE_90:
        X = Ypoint;
        Y = Paint_Image.Image_Width - Xpoint;
        Paint_DrawPixel(X, Y, Color);
        break;
    case IMAGE_ROTATE_180:
        X = Paint_Image.Image_Width - Xpoint;
        Y = Paint_Image.Image_Height - Ypoint;
        Paint_DrawPixel(X, Y, Color);
        break;
    case IMAGE_ROTATE_270:
        X = Paint_Image.Image_Height - Ypoint;
        Y = Xpoint;
        Paint_DrawPixel(X, Y, Color);
        break;
    }
}
/******************************************************************************
function:	Clear the color of a window
parameter:
    Xstart :   x starting point
    Ystart :   Y starting point
    Xend   :   x end point
    Yend   :   y end point
******************************************************************************/
void Paint_ClearWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color)
{
    UWORD X, Y;
    for (Y = Ystart; Y < Yend; Y++) {
        for (X = Xstart; X < Xend; X++) {//8 pixel =  1 byte
            Paint_SetPixel(X, Y, Color);
        }
    }
}

/******************************************************************************
function:	Draw Point(Xpoint, Ypoint) Fill the color
parameter:
    Xpoint		:   The Xpoint coordinate of the point
    Ypoint		:   The Ypoint coordinate of the point
    Color		:   Set color
    Dot_Pixel	:	point size
******************************************************************************/
void Paint_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color,
                     DOT_PIXEL Dot_Pixel, DOT_STYLE DOT_STYLE)
{
    if (Xpoint > Paint_Image.Image_Width || Ypoint > Paint_Image.Image_Height) {
        DEBUG("Paint_DrawPoint Input exceeds the normal display range\r\n");
        return;
    }

    int16_t XDir_Num , YDir_Num;
    if (DOT_STYLE == DOT_STYLE_DFT) {
        for (XDir_Num = 0; XDir_Num < 2 * Dot_Pixel - 1; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1; YDir_Num++) {
                Paint_SetPixel(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
            }
        }
    } else {
        for (XDir_Num = 0; XDir_Num <  Dot_Pixel; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num <  Dot_Pixel; YDir_Num++) {
                Paint_SetPixel(Xpoint + XDir_Num - 1, Ypoint + YDir_Num - 1, Color);
            }
        }
    }
}

/******************************************************************************
function:	Draw a line of arbitrary slope
parameter:
    Xstart ：Starting Xpoint point coordinates
    Ystart ：Starting Xpoint point coordinates
    Xend   ：End point Xpoint coordinate
    Yend   ：End point Ypoint coordinate
    Color  ：The color of the line segment
******************************************************************************/
void Paint_DrawLine(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,
                    UWORD Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel)
{
    if (Xstart > Paint_Image.Image_Width || Ystart > Paint_Image.Image_Height ||
        Xend > Paint_Image.Image_Width || Yend > Paint_Image.Image_Height) {
        DEBUG("Paint_DrawLine Input exceeds the normal display range\r\n");
        return;
    }

    if (Xstart > Xend)
        Paint_Swop(Xstart, Xend);
    if (Ystart > Yend)
        Paint_Swop(Ystart, Yend);

    UWORD Xpoint = Xstart;
    UWORD Ypoint = Ystart;
    int dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
    int dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

    // Increment direction, 1 is positive, -1 is counter;
    int XAddway = Xstart < Xend ? 1 : -1;
    int YAddway = Ystart < Yend ? 1 : -1;

    //Cumulative error
    int Esp = dx + dy;
    char Dotted_Len = 0;

    for (;;) {
        Dotted_Len++;
        //Painted dotted line, 2 point is really virtual
        if (Line_Style == LINE_STYLE_DOTTED && Dotted_Len % 3 == 0) {
            //DEBUG("LINE_DOTTED\r\n");
            Paint_DrawPoint(Xpoint, Ypoint, IMAGE_BACKGROUND, Dot_Pixel, DOT_STYLE_DFT);
            Dotted_Len = 0;
        } else {
            Paint_DrawPoint(Xpoint, Ypoint, Color, Dot_Pixel, DOT_STYLE_DFT);
        }
        if (2 * Esp >= dy) {
            if (Xpoint == Xend)
                break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if (2 * Esp <= dx) {
            if (Ypoint == Yend)
                break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}

/******************************************************************************
function:	Draw a rectangle
parameter:
    Xstart ：Rectangular  Starting Xpoint point coordinates
    Ystart ：Rectangular  Starting Xpoint point coordinates
    Xend   ：Rectangular  End point Xpoint coordinate
    Yend   ：Rectangular  End point Ypoint coordinate
    Color  ：The color of the Rectangular segment
    Filled : Whether it is filled--- 1 solid 0：empty
******************************************************************************/
void Paint_DrawRectangle(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,
                         UWORD Color, DRAW_FILL Filled, DOT_PIXEL Dot_Pixel)
{
    if (Xstart > Paint_Image.Image_Width || Ystart > Paint_Image.Image_Height ||
        Xend > Paint_Image.Image_Width || Yend > Paint_Image.Image_Height) {
        DEBUG("Input exceeds the normal display range\r\n");
        return;
    }

    if (Xstart > Xend)
        Paint_Swop(Xstart, Xend);
    if (Ystart > Yend)
        Paint_Swop(Ystart, Yend);

    if (Filled ) {
        UWORD Ypoint;
        for(Ypoint = Ystart; Ypoint < Yend; Ypoint++) {
            Paint_DrawLine(Xstart, Ypoint, Xend, Ypoint, Color , LINE_STYLE_SOLID, Dot_Pixel);
        }
    } else {
        Paint_DrawLine(Xstart, Ystart, Xend, Ystart, Color , LINE_STYLE_SOLID, Dot_Pixel);
        Paint_DrawLine(Xstart, Ystart, Xstart, Yend, Color , LINE_STYLE_SOLID, Dot_Pixel);
        Paint_DrawLine(Xend, Yend, Xend, Ystart, Color , LINE_STYLE_SOLID, Dot_Pixel);
        Paint_DrawLine(Xend, Yend, Xstart, Yend, Color , LINE_STYLE_SOLID, Dot_Pixel);
    }
}

/******************************************************************************
function:	Use the 8-point method to draw a circle of the
            specified size at the specified position->
parameter:
    X_Center  ：Center X coordinate
    Y_Center  ：Center Y coordinate
    Radius    ：circle Radius
    Color     ：The color of the ：circle segment
    Filled    : Whether it is filled: 1 filling 0：Do not
******************************************************************************/
void Paint_DrawCircle(UWORD X_Center, UWORD Y_Center, UWORD Radius,
                      UWORD Color, DRAW_FILL  Draw_Fill , DOT_PIXEL Dot_Pixel)
{
    if (X_Center > Paint_Image.Image_Width || Y_Center >= Paint_Image.Image_Height) {
        DEBUG("Paint_DrawCircle Input exceeds the normal display range\r\n");
        return;
    }

    //Draw a circle from(0, R) as a starting point
    int16_t XCurrent, YCurrent;
    XCurrent = 0;
    YCurrent = Radius;

    //Cumulative error,judge the next point of the logo
    int16_t Esp = 3 - (Radius << 1 );

    int16_t sCountY;
    if (Draw_Fill == DRAW_FILL_FULL) {
        while (XCurrent <= YCurrent ) { //Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                Paint_DrawPoint(X_Center + XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//1
                Paint_DrawPoint(X_Center - XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//2
                Paint_DrawPoint(X_Center - sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//3
                Paint_DrawPoint(X_Center - sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//4
                Paint_DrawPoint(X_Center - XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//5
                Paint_DrawPoint(X_Center + XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//6
                Paint_DrawPoint(X_Center + sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );//7
                Paint_DrawPoint(X_Center + sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );
            }
            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while (XCurrent <= YCurrent ) {
            Paint_DrawPoint(X_Center + XCurrent, Y_Center + YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//1
            Paint_DrawPoint(X_Center - XCurrent, Y_Center + YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//2
            Paint_DrawPoint(X_Center - YCurrent, Y_Center + XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//3
            Paint_DrawPoint(X_Center - YCurrent, Y_Center - XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//4
            Paint_DrawPoint(X_Center - XCurrent, Y_Center - YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//5
            Paint_DrawPoint(X_Center + XCurrent, Y_Center - YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//6
            Paint_DrawPoint(X_Center + YCurrent, Y_Center - XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//7
            Paint_DrawPoint(X_Center + YCurrent, Y_Center + XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );//0

            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

/******************************************************************************
function:	Show English characters
parameter:
    Xpoint           ：X coordinate
    Ypoint           ：Y coordinate
    Acsii_Char       ：To display the English characters
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
void Paint_DrawChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char,
                    sFONT* Font, UWORD Color_Background, UWORD Color_Foreground)
{
    UWORD Page, Column;

    if (Xpoint > Paint_Image.Image_Width || Ypoint > Paint_Image.Image_Height) {
        DEBUG("Paint_DrawChar Input exceeds the normal display range\r\n");
        return;
    }

    uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for (Page = 0; Page < Font->Height; Page ++ ) {
        for (Column = 0; Column < Font->Width; Column ++ ) {

            //To determine whether the font background color and screen background color is consistent
            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if (pgm_read_byte(ptr) & (0x80 >> (Column % 8)))
                    Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            } else {
                if (pgm_read_byte(ptr) & (0x80 >> (Column % 8))) {
                    Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            }
            //One pixel is 8 bits
            if (Column % 8 == 7)
                ptr++;
        }// Write a line
        if (Font->Width % 8 != 0)
            ptr++;
    }// Write all
}

/******************************************************************************
function:	Display the string
parameter:
    Xstart           ：X coordinate
    Ystart           ：Y coordinate
    pString          ：The first address of the English string to be displayed
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
void Paint_DrawString_EN(UWORD Xstart, UWORD Ystart, const char * pString,
                         sFONT* Font, UWORD Color_Background, UWORD Color_Foreground )
{
    UWORD Xpoint = Xstart;
    UWORD Ypoint = Ystart;

    if (Xstart > Paint_Image.Image_Width || Ystart > Paint_Image.Image_Height) {
        DEBUG("Paint_DrawString_EN Input exceeds the normal display range\r\n");
        return;
    }

    while (* pString != '\0') {
        //if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
        if ((Xpoint + Font->Width ) > Paint_Image.Image_Width ) {
            Xpoint = Xstart;
            Ypoint += Font->Height;
        }

        // If the Y direction is full, reposition to(Xstart, Ystart)
        if ((Ypoint  + Font->Height ) > Paint_Image.Image_Height ) {
            Xpoint = Xstart;
            Ypoint = Ystart;
        }
        Paint_DrawChar(Xpoint, Ypoint, * pString, Font, Color_Background, Color_Foreground);

        //The next character of the address
        pString ++;

        //The next word of the abscissa increases the font of the broadband
        Xpoint += Font->Width;
    }
}

/******************************************************************************
function:	Display nummber
parameter:
    Xstart           ：X coordinate
    Ystart           : Y coordinate
    Nummber          : The number displayed
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
#define  ARRAY_LEN 255
void Paint_DrawNum(UWORD Xpoint, UWORD Ypoint, int32_t Nummber,
                   sFONT* Font, UWORD Color_Background, UWORD Color_Foreground )
{

    int16_t Num_Bit = 0, Str_Bit = 0;
    uint8_t Str_Array[ARRAY_LEN] = {0}, Num_Array[ARRAY_LEN] = {0};
    uint8_t *pStr = Str_Array;

    if (Xpoint > Paint_Image.Image_Width || Ypoint > Paint_Image.Image_Height) {
        DEBUG("Paint_DisNum Input exceeds the normal display range\r\n");
        return;
    }

    //Converts a number to a string
    while (Nummber) {
        Num_Array[Num_Bit] = Nummber % 10 + '0';
        Num_Bit++;
        Nummber /= 10;
    }

    //The string is inverted
    while (Num_Bit > 0) {
        Str_Array[Str_Bit] = Num_Array[Num_Bit - 1];
        Str_Bit ++;
        Num_Bit --;
    }

    //show
    Paint_DrawString_EN(Xpoint, Ypoint, (const char*)pStr, Font, Color_Background, Color_Foreground );
}

/******************************************************************************
function:	Display time
parameter:
    Xstart           ：X coordinate
    Ystart           : Y coordinate
    pTime            : Time-related structures
    Font             ：A structure pointer that displays a character size
    Color            : Select the background color of the English character
******************************************************************************/
void Paint_DrawTime(UWORD Xstart, UWORD Ystart, PAINT_TIME *pTime, sFONT* Font,
                    UWORD Color_Background, UWORD Color_Foreground)
{
    uint8_t value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    UWORD Dx = Font->Width;

    //Write data into the cache
    Paint_DrawChar(Xstart                           , Ystart, value[pTime->Hour / 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx                      , Ystart, value[pTime->Hour % 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx  + Dx / 4 + Dx / 2   , Ystart, ':'                    , Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx * 2 + Dx / 2         , Ystart, value[pTime->Min / 10] , Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx * 3 + Dx / 2         , Ystart, value[pTime->Min % 10] , Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx * 4 + Dx / 2 - Dx / 4, Ystart, ':'                    , Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx * 5                  , Ystart, value[pTime->Sec / 10] , Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + Dx * 6                  , Ystart, value[pTime->Sec % 10] , Font, Color_Background, Color_Foreground);
}

/******************************************************************************
function:	Display monochrome bitmap
parameter:
    image_buffer ：A picture data converted to a bitmap
info:
    Use a computer to convert the image into a corresponding array,
    and then embed the array directly into Imagedata.cpp as a .c file.
******************************************************************************/
void Paint_DrawBitMap(const unsigned char* image_buffer)
{
    UWORD Xpoint, Ypoint, Height, Width;
    Height = Paint_Image.Memory_Height;
    Width = (Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1);
    UDOUBLE Offset = Paint_Image.Image_Offset;
    UDOUBLE Addr = 0;

    for (Ypoint = 0; Ypoint < Height; Ypoint++) {
        for (Xpoint = 0; Xpoint < Width; Xpoint++) {//8 pixel =  1 byte
            Addr = Xpoint + Ypoint * Width + Offset;					
            SPIRAM_WR_Byte(Addr, pgm_read_byte(image_buffer+Xpoint + Ypoint * Width));
        }
    }
}

/******************************************************************************
function: Display the string
parameter:
    Xstart  ：X coordinate
    Ystart  ：Y coordinate
    pString ：The first address of the Chinese string and English
              string to be displayed
    Font    ：A structure pointer that displays a character size
    Color_Foreground : Select the foreground color
    Color_Background : Select the background color
******************************************************************************/
void Paint_DrawString_CN(UWORD Xstart, UWORD Ystart, const char * pString, cFONT* font,
                        UWORD Color_Foreground, UWORD Color_Background)
{
    const char* p_text = pString;
    int x = Xstart, y = Ystart;
    int i, j,Num;

    /* Send the string character by character on EPD */
    while (*p_text != 0) {
        if(*p_text <= 0x7F) {  //ASCII < 126
            for(Num = 0; Num < font->size; Num++) {
                if(*p_text== font->table[Num].index[0]) {
                    const char* ptr = &font->table[Num].matrix[0];

                    for (j = 0; j < font->Height; j++) {
                        for (i = 0; i < font->Width; i++) {
                            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                                if (*ptr & (0x80 >> (i % 8))) {
                                    Paint_SetPixel(x + i, y + j, Color_Foreground);
                                    // Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                                }
                            } else {
                                if (*ptr & (0x80 >> (i % 8))) {
                                    Paint_SetPixel(x + i, y + j, Color_Foreground);
                                    // Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                                } else {
                                    Paint_SetPixel(x + i, y + j, Color_Background);
                                    // Paint_DrawPoint(x + i, y + j, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                                }
                            }
                            if (i % 8 == 7) {
                                ptr++;
                            }
                        }
                        if (font->Width % 8 != 0) {
                            ptr++;
                        }
                    }
                    break;
                }
            }
            /* Point on the next character */
            p_text += 1;
            /* Decrement the column position by 16 */
            x += font->ASCII_Width;
        } else {        //Chinese
            for(Num = 0; Num < font->size; Num++) {
                if((*p_text== font->table[Num].index[0]) && (*(p_text+1) == font->table[Num].index[1])) {
                    const char* ptr = &font->table[Num].matrix[0];

                    for (j = 0; j < font->Height; j++) {
                        for (i = 0; i < font->Width; i++) {
                            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                                if (*ptr & (0x80 >> (i % 8))) {
                                    Paint_SetPixel(x + i, y + j, Color_Foreground);
                                    // Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                                }
                            } else {
                                if (*ptr & (0x80 >> (i % 8))) {
                                    Paint_SetPixel(x + i, y + j, Color_Foreground);
                                    // Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                                } else {
                                    Paint_SetPixel(x + i, y + j, Color_Background);
                                    // Paint_DrawPoint(x + i, y + j, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                                }
                            }
                            if (i % 8 == 7) {
                                ptr++;
                            }
                        }
                        if (font->Width % 8 != 0) {
                            ptr++;
                        }
                    }
                    break;
                }
            }
            /* Point on the next character */
            p_text += 2;
            /* Decrement the column position by 16 */
            x += font->Width;
        }
    }
}
