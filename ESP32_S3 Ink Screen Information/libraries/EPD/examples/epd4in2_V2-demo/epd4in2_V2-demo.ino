#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

void setup() {
  DEBUG("4.2inch e-Paper V2 demo\r\n");
  DEV_Module_Init();
  EPD_4IN2_V2_Init();
  EPD_4IN2_V2_Clear();
  DEV_Delay_ms(500);

#if 0
      /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("4in2.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_4IN2_V2_Display();
    DEV_Delay_ms(2000);
#elif 1
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    
    DEBUG("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(IMAGE_DATA);

    DEBUG("EPD_4IN2_V2_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_4IN2_V2_Display();
    DEV_Delay_ms(2000);

#elif 0
	//1.Create a new image cache named IMAGE_BW and fill it with white
	Paint_NewImage(IMAGE_BW, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
  	Paint_Clear(WHITE);
    

	EPD_4IN2_V2_Init_Fast(Seconds_1_5S);
    //2.Drawing on the image
    Paint_DrawPoint(10, 20, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 30, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 50, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 20, 70, 70, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 20, 20, 70, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(30, 120, 60, 120, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(45, 135, 45, 105, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

    Paint_DrawRectangle(20, 20, 70, 70, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(75, 20, 120, 70, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(45, 120, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(100, 120, 15, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 150, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(10, 170, "waveshare", &Font16, BLACK, WHITE);

    Paint_DrawNum(10, 200, 123456789, &Font12, BLACK, WHITE);
    Paint_DrawNum(10, 220, 987654321, &Font16, WHITE, BLACK);

    //3.Refresh the picture in RAM to e-Paper
    EPD_4IN2_V2_Display_Fast();
	DEV_Delay_ms(3000);

	DEBUG("Partial refresh\r\n");
	Paint_NewImage(IMAGE_BW, 120, 50, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
	Paint_SetScale(2);
    Paint_Clear(WHITE);

	DEBUG("Partial refresh\r\n");
	DEBUG("Partial refresh effect is not recommended, please do not use\r\n");
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 20;
	for (;;) {
		sPaint_time.Sec = sPaint_time.Sec + 1;
		if (sPaint_time.Sec == 60) {
			sPaint_time.Min = sPaint_time.Min + 1;
			sPaint_time.Sec = 0;
			if (sPaint_time.Min == 60) {
				sPaint_time.Hour =  sPaint_time.Hour + 1;
				sPaint_time.Min = 0;
				if (sPaint_time.Hour == 24) {
					sPaint_time.Hour = 0;
					sPaint_time.Min = 0;
					sPaint_time.Sec = 0;
				}
			}
		}
		Paint_Clear(WHITE);
		Paint_DrawRectangle(1, 1, 120, 50, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawTime(10, 15, &sPaint_time, &Font20, WHITE, BLACK);
		EPD_4IN2_V2_PartialDisplay(200, 80, 320, 130);
		DEV_Delay_ms(500);//Analog clock 1s
		num = num - 1;
		if(num == 0) {
			break;
		}
    }

#elif 0

	EPD_4IN2_V2_Init_4Gray();
	Paint_NewImage(IMAGE_BW, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
	Paint_SetScale(4);
	Paint_Clear(WHITE);

	// Paint_DrawPoint(10, 20, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	// Paint_DrawPoint(10, 30, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	// Paint_DrawPoint(10, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	// Paint_DrawPoint(10, 50, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

	// Paint_DrawLine(20, 20, 70, 70, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
	// Paint_DrawLine(70, 20, 20, 70, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
	// Paint_DrawLine(30, 120, 60, 120, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
	// Paint_DrawLine(45, 135, 45, 105, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

	// Paint_DrawRectangle(20, 20, 70, 70, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
	// Paint_DrawRectangle(75, 20, 120, 70, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

	// Paint_DrawCircle(45, 120, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
	// Paint_DrawCircle(100, 120, 15, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

//	Paint_DrawString_EN(10, 150, "hello world", &Font12, WHITE, BLACK);
//	Paint_DrawString_EN(10, 170, "waveshare", &Font16, BLACK, WHITE);
//
//	Paint_DrawNum(10, 200, 123456789, &Font12, BLACK, WHITE);
	
	Paint_DrawNum(200, 10, 987654321, &Font16, GRAY1, GRAY4);
	Paint_DrawNum(200, 30, 987654321, &Font16, GRAY2, GRAY3);
	Paint_DrawNum(200, 50, 987654321, &Font16, GRAY3, GRAY2);
	Paint_DrawNum(200, 70, 987654321, &Font16, GRAY4, GRAY1);
	
	EPD_4IN2_V2_Display_4Gray();


	SDCard_Init();
	SDCard_Read_4GrayBMP("4IN2Sc.bmp", 0, 0);
	EPD_4IN2_V2_Display_4Gray();
	DEV_Delay_ms(4000);
#endif

	DEV_Delay_ms(3000);
	EPD_4IN2_V2_Init();
	EPD_4IN2_V2_Clear();

	EPD_4IN2_V2_Sleep();
	DEV_Module_Exit();
}

void loop() {

}
