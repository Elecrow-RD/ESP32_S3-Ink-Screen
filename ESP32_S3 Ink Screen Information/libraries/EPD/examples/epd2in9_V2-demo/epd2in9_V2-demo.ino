#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

void setup() {
	DEBUG("2.9inch e-Paper V2 demo\r\n");
	DEV_Module_Init();
	EPD_2IN9_V2_Init();
	EPD_2IN9_V2_Clear();
	DEV_Delay_ms(500);
#if 0
     /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("2in9.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_2IN9_V2_Display();
    DEV_Delay_ms(2000);
#elif 0
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);    
    
    DEBUG("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(IMAGE_DATA);

    DEBUG("EPD_2IN9_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN9_V2_Display();
    DEV_Delay_ms(2000);
#endif

UBYTE Rotate = IMAGE_ROTATE_90;
#if 0
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, Rotate, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    
    //2.Drawing on the image
    if (Rotate == IMAGE_ROTATE_0 || Rotate == IMAGE_ROTATE_180) {
        DEBUG("Vertical screen\r\n");
        
        Paint_DrawPoint(10, 20, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 30, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

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
    } else {
        DEBUG("Horizontal screen\r\n");
            
        Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

        Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
        Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
        Paint_DrawLine(140, 95, 180, 95, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
        Paint_DrawLine(160, 75, 160, 115, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

        Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

        Paint_DrawCircle(160, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawCircle(210, 95, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

        Paint_DrawString_EN(10, 0, "waveshare Electronics", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);

        Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
        Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);        
    }

    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN9_V2_Display_Base();
    DEV_Delay_ms(2000);
#endif

#if 0
    //4.Partial refresh, example shows time
    // Paint_NewImage(IMAGE_BW, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, Rotate, IMAGE_COLOR_POSITIVE);
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    for (int i=0; i<10; i++){
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
        if (Rotate == IMAGE_ROTATE_0 || Rotate == IMAGE_ROTATE_180) {
            Paint_ClearWindows(15, 75, 15 + Font20.Width * 7, 75 + Font20.Height, WHITE);
            Paint_DrawTime(15, 75, &sPaint_time, &Font20, WHITE, BLACK);
        } else {
            Paint_ClearWindows(120, 30, 120 + Font20.Width * 7, 30 + Font20.Height, WHITE);
            Paint_DrawTime(120, 30, &sPaint_time, &Font20, WHITE, BLACK);
        }
        EPD_2IN9_V2_Display_Partial();
        DEV_Delay_ms(500);//Analog clock 1s
    }
#endif

#if 0 // show image for array
    DEBUG("show Gray------------------------\r\n");
    EPD_2IN9_V2_Gray4_Init();
    DEBUG("4 grayscale display\r\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);  	
    Paint_SetScale(4);
    Paint_Clear(0xff);
    
   /* Arduino UNO does not have enough memory, uncommenting may cause the program to run incorrectly.*/
    // Paint_DrawPoint(10, 80, GRAY4, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    // Paint_DrawPoint(10, 90, GRAY4, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    // Paint_DrawPoint(10, 100, GRAY4, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    // Paint_DrawLine(20, 70, 70, 120, GRAY4, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    // Paint_DrawLine(70, 70, 20, 120, GRAY4, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    // Paint_DrawRectangle(20, 70, 70, 120, GRAY4, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    // Paint_DrawRectangle(80, 70, 130, 120, GRAY4, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    // Paint_DrawCircle(45, 95, 20, GRAY4, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    // Paint_DrawCircle(105, 95, 20, GRAY2, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    // Paint_DrawLine(85, 95, 125, 95, GRAY4, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    // Paint_DrawLine(105, 75, 105, 115, GRAY4, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, GRAY4, GRAY1);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, GRAY3, GRAY1);
    Paint_DrawNum(10, 33, 123456789, &Font12, GRAY4, GRAY2);
    Paint_DrawNum(10, 50, 987654321, &Font16, GRAY1, GRAY4);
    EPD_2IN9_V2_4GrayDisplay();
    DEV_Delay_ms(3000);

#endif
    EPD_2IN9_V2_Init();
	EPD_2IN9_V2_Clear();

	EPD_2IN9_V2_Sleep();
	DEV_Delay_ms(1000);
	DEV_Module_Exit();
}

void loop() {

}
