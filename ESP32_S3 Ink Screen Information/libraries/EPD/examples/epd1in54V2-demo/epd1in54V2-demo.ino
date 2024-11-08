#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

#define mode 2

void setup() {
  DEBUG("1.54inch e-Paper V2 demo\r\n");
  DEV_Module_Init();
  EPD_1IN54_V2_Init();
  EPD_1IN54_V2_Clear();
  DEV_Delay_ms(500);
#if (mode==1)
      /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("1in54.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_1IN54_V2_Display();
    DEV_Delay_ms(2000);
#elif (mode==2)
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    
    DEBUG("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(IMAGE_DATA);

    DEBUG("EPD_1IN54_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_1IN54_V2_Display();
    DEV_Delay_ms(2000);
//    
//      SPIRAM_Usertest();
#elif (mode==3)
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //2.Drawing on the image
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(170, 15, 170, 55, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(150, 35, 190, 35, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(170, 35, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(170, 85, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawString_EN(5, 70, "hello world", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(5, 90, "waveshare", &Font20, BLACK, WHITE);

    Paint_DrawNum(5, 120, 123456789, &Font20, BLACK, WHITE);

    //3.Refresh the picture in RAM to e-Paper
    EPD_1IN54_V2_Display();
    DEV_Delay_ms(2000);

#else
    //1.Create a new image cache named IMAGE_BW and fill it with black
    Paint_NewImage(IMAGE_BW, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(BLACK);
    
    //2.Partial refresh, example shows time
    EPD_1IN54_V2_Init_Partial();
    DEBUG("Partial refresh\r\n");
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 20;
    for (int i=0; i<10; i++) {
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
        Paint_ClearWindows(15, 140, 15 + Font20.Width * 7, 145 + Font20.Height, WHITE);
        Paint_DrawTime(15, 145, &sPaint_time, &Font20, WHITE, BLACK);
        num = num - 1;
        if(num == 0) {
            break;
        }
        EPD_1IN54_V2_DisplayPart();
        DEV_Delay_ms(500);//Analog clock 1s
    }
    
#endif
    //DEV_Delay_ms(3000);
    EPD_1IN54_V2_Init();
    EPD_1IN54_V2_Clear();
    
    EPD_1IN54_V2_Sleep();
    DEV_Module_Exit();
}

void loop() {

}
