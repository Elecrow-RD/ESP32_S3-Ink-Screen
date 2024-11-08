#include "EPD.h"
#include "EPDfont.h"
#include "string.h"

PAINT Paint;


/*******************************************************************
    Function Description: Create an image cache array
    Interface Description: * Image:The image array to be passed in
                            Width:Image width
                            Height:Image length
                            Rotate:Screen display orientation
                            Color:Display color
    Return value: None
*******************************************************************/
void Paint_NewImage(uint8_t *image,uint16_t Width,uint16_t Height,uint16_t Rotate,uint16_t Color)
{
	Paint.Image = 0x00;
	Paint.Image = image;
	Paint.color = Color;  
	Paint.widthMemory = Width;
	Paint.heightMemory = Height;  
	Paint.widthByte = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);
	Paint.heightByte = Height;     
	Paint.rotate = Rotate;
	if(Rotate==0||Rotate==180) 
	{
		Paint.width=Height;
		Paint.height=Width;
	} 
	else 
	{
		Paint.width = Width;
		Paint.height = Height;
	}
}				 

/*******************************************************************
    Function Description: Clear Buffer
    Interface Description: Color:Pixel Color Parameters
    Return value: None
*******************************************************************/
void Paint_Clear(uint8_t Color)
{
	uint16_t X,Y;
	uint32_t Addr;
  for(Y=0;Y<Paint.heightByte;Y++) 
	{
    for(X=0;X<Paint.widthByte;X++) 
		{   
      Addr=X+Y*Paint.widthByte;//8 pixel =  1 byte
      Paint.Image[Addr]=Color;
    }
  }
}


/*******************************************************************
    Function description: Light up a pixel point
    Interface description: Xpoint pixel x-coordinate parameters
              Ypoint: pixel point Y coordinate parameter
              Color :Pixel color parameters
    返回值：  无
*******************************************************************/
void Paint_SetPixel(uint16_t Xpoint,uint16_t Ypoint,uint16_t Color)
{
	uint16_t X, Y;
	uint32_t Addr;
	uint8_t Rdata;		
    switch(Paint.rotate) 
		{
				case 0:
					if(Xpoint>=396)
					{
						Xpoint+=8;
					}
					X=Xpoint;
					Y=Ypoint;
					break;
			case 90:
					if(Ypoint>=396)
					{
						Ypoint+=8;
					}
					X=Paint.widthMemory-Ypoint-1;
					Y=Xpoint;
					break;
			case 180:
				  if(Xpoint>=396)
					{
						Xpoint+=8;
					}
					X=Paint.widthMemory-Xpoint-1;
					Y=Paint.heightMemory-Ypoint-1;
					break;

			case 270:
					if(Ypoint>=396)
					{
						Ypoint+=8;
					}
					X=Ypoint;
					Y=Paint.heightMemory-Xpoint-1;
					break;
				default:
						return;
    }
		Addr=X/8+Y*Paint.widthByte;
    Rdata=Paint.Image[Addr];
    if(Color==BLACK)
    {    
			Paint.Image[Addr]=Rdata&~(0x80>>(X % 8)); //Corresponding data position 0
		}
    else
		{
      Paint.Image[Addr]=Rdata|(0x80>>(X % 8));   //Corresponding data location 1
		}
}


/*******************************************************************
    Function description: underlined function
    Interface description: Xstart pixel x starting coordinate parameter
              Ystart :Pixel Y starting coordinate parameter
              Xend   :Pixel x End Coordinate Parameter
              Yend   :Pixel Y End Coordinate Parameter
              Color  :Pixel color parameters
    Return value: None
*******************************************************************/
void EPD_DrawLine(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color)
{   
	uint16_t Xpoint, Ypoint;
	int dx, dy;
	int XAddway,YAddway;
	int Esp;
	char Dotted_Len;
  Xpoint = Xstart;
  Ypoint = Ystart;
  dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
  dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;
  XAddway = Xstart < Xend ? 1 : -1;
  YAddway = Ystart < Yend ? 1 : -1;
  Esp = dx + dy;
  Dotted_Len = 0;
  for (;;) {
        Dotted_Len++;
            Paint_SetPixel(Xpoint, Ypoint, Color);
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
/*******************************************************************
    Function Description: Draw a Rectangular Function
    Interface description: Xstart rectangle x starting coordinate parameter
              Ystart :Starting coordinate parameters of rectangle Y
              Xend   :End coordinate parameters of rectangle x
              Yend   :End coordinate parameters of rectangle Y
              Color  :Pixel color parameters
              mode   :Is the rectangle filled
    Return value: None
*******************************************************************/
void EPD_DrawRectangle(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color,uint8_t mode)
{
	uint16_t i;
    if (mode)
			{
        for(i = Ystart; i < Yend; i++) 
				{
          EPD_DrawLine(Xstart,i,Xend,i,Color);
        }
      }
		else 
		 {
        EPD_DrawLine(Xstart, Ystart, Xend, Ystart, Color);
        EPD_DrawLine(Xstart, Ystart, Xstart, Yend, Color);
        EPD_DrawLine(Xend, Yend, Xend, Ystart, Color);
        EPD_DrawLine(Xend, Yend, Xstart, Yend, Color);
		 }
}
/*******************************************************************
    Function description: Draw a circular function
    Interface Description: X_Center Center Center x Starting Coordinate Parameter
              Y_Center :Center Y coordinate parameter
              Radius   :Circular radius parameter
              Color    :Pixel color parameters
              mode     :Is the circle filled and displayed
    Return value: None
*******************************************************************/
void EPD_DrawCircle(uint16_t X_Center,uint16_t Y_Center,uint16_t Radius,uint16_t Color,uint8_t mode)
{
	int Esp, sCountY;
	uint16_t XCurrent, YCurrent;
  XCurrent = 0;
  YCurrent = Radius;
  Esp = 3 - (Radius << 1 );
    if (mode) {
        while (XCurrent <= YCurrent ) { //Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                Paint_SetPixel(X_Center + XCurrent, Y_Center + sCountY, Color);//1
                Paint_SetPixel(X_Center - XCurrent, Y_Center + sCountY, Color);//2
                Paint_SetPixel(X_Center - sCountY, Y_Center + XCurrent, Color);//3
                Paint_SetPixel(X_Center - sCountY, Y_Center - XCurrent, Color);//4
                Paint_SetPixel(X_Center - XCurrent, Y_Center - sCountY, Color);//5
                Paint_SetPixel(X_Center + XCurrent, Y_Center - sCountY, Color);//6
                Paint_SetPixel(X_Center + sCountY, Y_Center - XCurrent, Color);//7
                Paint_SetPixel(X_Center + sCountY, Y_Center + XCurrent, Color);
            }
            if ((int)Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while (XCurrent <= YCurrent ) {
            Paint_SetPixel(X_Center + XCurrent, Y_Center + YCurrent, Color);//1
            Paint_SetPixel(X_Center - XCurrent, Y_Center + YCurrent, Color);//2
            Paint_SetPixel(X_Center - YCurrent, Y_Center + XCurrent, Color);//3
            Paint_SetPixel(X_Center - YCurrent, Y_Center - XCurrent, Color);//4
            Paint_SetPixel(X_Center - XCurrent, Y_Center - YCurrent, Color);//5
            Paint_SetPixel(X_Center + XCurrent, Y_Center - YCurrent, Color);//6
            Paint_SetPixel(X_Center + YCurrent, Y_Center - XCurrent, Color);//7
            Paint_SetPixel(X_Center + YCurrent, Y_Center + XCurrent, Color);//0
            if ((int)Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

/*******************************************************************
    Function Description: Display a single character
    Interface description: 
              x :characters x coordinate parameters
              y :Character Y coordinate parameter
            chr :Characters to be displayed
          size1 :Display character font size
          Color :Pixel color parameters
    Return value: None
*******************************************************************/
void EPD_ShowChar(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1,uint16_t color)
{
	uint16_t i,m,temp,size2,chr1;
	uint16_t x0,y0;
	x0=x,y0=y;
	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //Obtain the number of bytes occupied by the dot matrix set corresponding to one character in the font
	chr1=chr-' ';  //Calculate the offset value
	for(i=0;i<size2;i++)
	{
		if(size1==12)
        {temp=ascii_1206[chr1][i];} //Call 1206 font
		else if(size1==16)
        {temp=ascii_1608[chr1][i];} //Call 1608 font
		else if(size1==24)
        {temp=ascii_2412[chr1][i];} //Call 2412 font
		else if(size1==48)
        {temp=ascii_4824[chr1][i];} //Call 2412 font
		else 
        return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)Paint_SetPixel(x,y,color);
			else Paint_SetPixel(x,y,!color);
			temp>>=1;
			y++;
		}
		x++;
		if((size1!=8)&&((x-x0)==size1/2))
		{x=x0;y0=y0+8;}
		y=y0;
  }
}

/*******************************************************************
    Function description: Display string
    Interface Description：
              x  :String x coordinate parameter
              y  :String Y coordinate parameter
            *chr :The string to be displayed
            size1:Display string font size
            Color:Pixel color parameters
    Return value: None
*******************************************************************/
void EPD_ShowString(uint16_t x,uint16_t y,const char *chr,uint16_t size1,uint16_t color)
{
	while(*chr!='\0')//Determine if it is an illegal character!
	{
		EPD_ShowChar(x,y,*chr,size1,color);
		chr++;
		x+=size1/2;
  }
}
/*******************************************************************
   Function description: Exponential operation
    Interface Description: 
              m :base 
              N :index
    Return value: m to the power of n
*******************************************************************/
uint32_t EPD_Pow(uint16_t m,uint16_t n)
{
	uint32_t result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}
/*******************************************************************
    Function Description: Display integer numbers
    Interface description: 
              x      ：numbers x coordinate parameters
              y      ：Digital Y-coordinate parameter
              num    ：The number to be displayed
              len    ：Number of digits
              size1  ：Display string font size
              Color  ：Pixel color parameters
    Return value: None
*******************************************************************/
void EPD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint16_t len,uint16_t size1,uint16_t color)
{
	uint8_t t,temp,m=0;
	if(size1==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/EPD_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				EPD_ShowChar(x+(size1/2+m)*t,y,'0',size1,color);
      }
			else 
			{
			  EPD_ShowChar(x+(size1/2+m)*t,y,temp+'0',size1,color);
			}
  }
}
/*******************************************************************
    Function Description: Display Floating Point Numbers
    Interface description: 
              x     ：numbers x coordinate parameters
              y     ：Digital Y-coordinate parameter
              num   ：Floating point numbers to be displayed
              len    :Number of digits
              pre    :Precision of Floating Point Numbers
              size1  :Display string font size
              Color  :Pixel color parameters
    Return value: None
*******************************************************************/
void EPD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint8_t pre,uint8_t sizey,uint8_t color)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*EPD_Pow(10,pre);
	for(t=0;t<len;t++)
	{
		temp=(num1/EPD_Pow(10,len-t-1))%10;
		if(t==(len-pre))
		{
			EPD_ShowChar(x+(len-pre)*sizex,y,'.',sizey,color);
			t++;
			len+=1;
		}
	 	EPD_ShowChar(x+t*sizex,y,temp+48,sizey,color);
	}
}

/*******************************************************************
    Function Description: display picture
    Interface description: 
              x     ：Numbers x coordinate parameters
              y     ：Digital Y-coordinate parameter
            sizex   ：Width of image resolution
            sizey    :Height of image resolution
              BMP    :Generated C array
              Color  :Pixel color parameters
    Return value: None
*******************************************************************/
void EPD_ShowPicture(uint16_t x,uint16_t y,uint16_t sizex,uint16_t sizey,const uint8_t BMP[],uint16_t Color)
{
	uint16_t j=0,t;
	uint16_t i,temp,x0,TypefaceNum=sizey*(sizex/8+((sizex%8)?1:0));
	x0=x;
  for(i=0;i<TypefaceNum;i++)
	{
		temp=BMP[j];
		for(t=0;t<8;t++)
		{
		 if(temp&0x80)
		 {
			 Paint_SetPixel(x,y,!Color);
		 }
		 else
		 {
			 Paint_SetPixel(x,y,Color);
		 }
		 x++;
		 temp<<=1;
		}
		if((x-x0)==sizex)
		{
			x=x0;
			y++;
		}
		j++;
//    delayMicroseconds(10); // Delay in microseconds
	}
}
