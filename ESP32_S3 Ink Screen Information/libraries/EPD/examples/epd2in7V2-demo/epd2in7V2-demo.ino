#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

void setup() {
    DEV_Module_Init();

    DEBUG("e-Paper Init and Clear...\r\n");
	EPD_2IN7_V2_Init();
    EPD_2IN7_V2_Clear();
    DEV_Delay_ms(500);
    //1.Initialize the SD card
    SDCard_Init();
#if 0
    /*show sd card pic*/
    
    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN7_V2_WIDTH, EPD_2IN7_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("2in7.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_2IN7_V2_Display();
    DEV_Delay_ms(2000);
#else
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN7_V2_WIDTH, EPD_2IN7_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    DEBUG("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(IMAGE_DATA);

    DEBUG("EPD_2IN7_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN7_V2_Display();
    DEV_Delay_ms(2000);
#endif

#if 0  // Fast Drawing on the image
    DEBUG("e-Paper Init Fast\r\n");
    EPD_2IN7_V2_Init_Fast();
	//1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN7_V2_WIDTH, EPD_2IN7_V2_HEIGHT, IMAGE_ROTATE_270, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //1.Select Image

    // 2.Drawing on the image
    Paint_Clear(WHITE);
    DEBUG("Drawing:BlackImage\r\n");
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

    Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);

    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(45, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(105, 95, 20, WHITE, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawLine(85, 95, 125, 95, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(105, 75, 105, 115, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 2, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);

    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

    EPD_2IN7_V2_Display_Fast();
    DEV_Delay_ms(3000);

#endif

#if 0  // Drawing on the image

    Paint_NewImage(IMAGE_BW, EPD_2IN7_V2_WIDTH, EPD_2IN7_V2_HEIGHT, IMAGE_ROTATE_270, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //1.Select Image
	EPD_2IN7_V2_Init();
    Paint_Clear(WHITE);
	
    // 2.Drawing on the image
    DEBUG("Drawing:BlackImage\r\n");
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

    Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);

    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(45, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(105, 95, 20, WHITE, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawLine(85, 95, 125, 95, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(105, 75, 105, 115, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 2, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);

    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

    EPD_2IN7_V2_Display_Base();
    DEV_Delay_ms(3000);
#endif



#if 0   //Partial refresh, example shows time    	
    // If you didn't use the EPD_2IN7_V2_Display_Base() function to refresh the image before,
    // use the EPD_2IN7_V2_Display_Base_color() function to refresh the background color, 
    // otherwise the background color will be garbled 
    EPD_2IN7_V2_Init();
    EPD_2IN7_V2_Display_Base_color(WHITE);
    DEBUG("Partial refresh\r\n");
	Paint_NewImage(IMAGE_BW, 50, 120, IMAGE_ROTATE_270, IMAGE_COLOR_POSITIVE);
	Paint_SetScale(2);
    Paint_Clear(WHITE);
    
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 15;
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

        num = num - 1;
        if(num == 0) {
            break;
        }
        DEBUG("Part refresh...\r\n");
        EPD_2IN7_V2_Display_Partial(60, 134, 110, 254); // Xstart must be a multiple of 8
        DEV_Delay_ms(500);
    }
#endif

#if 0 // show image for array
    DEBUG("4 grayscale display\r\n");
	Paint_NewImage(IMAGE_BW, EPD_2IN7_V2_WIDTH, EPD_2IN7_V2_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_SetScale(4);
    Paint_Clear(WHITE);
    EPD_2IN7_V2_Init_4GRAY();
    
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
    EPD_2IN7_V2_4GrayDisplay();
    DEV_Delay_ms(3000);

#endif

    DEBUG("Clear...\r\n");
    EPD_2IN7_V2_Init();
    EPD_2IN7_V2_Clear();
	
    DEBUG("Goto Sleep...\r\n");
    EPD_2IN7_V2_Sleep();
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    DEBUG("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
}

void loop() {

}
