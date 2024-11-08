#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

void setup() {
 DEBUG("2.13inch e-Paper demo\r\n");
 DEV_Module_Init();
  EPD_2IN13D_Init();
  EPD_2IN13D_Clear();
  DEV_Delay_ms(500);
#if 0
      /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN13D_WIDTH, EPD_2IN13D_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("2in13d.bmp", 0, 0);


    //4.Refresh the picture in RAM to e-Paper
    EPD_2IN13D_Display();
    DEV_Delay_ms(2000);
#elif 1
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN13D_WIDTH, EPD_2IN13D_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    
    DEBUG("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(IMAGE_DATA);

    DEBUG("EPD_2IN13D_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN13D_Display();
    DEV_Delay_ms(2000);
//    
//      SPIRAM_Usertest();
#endif
Paint_NewImage(IMAGE_BW, EPD_2IN13D_WIDTH, EPD_2IN13D_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
Paint_Clear(WHITE);
#if 0
    //1.Create a new image cache named IMAGE_BW and fill it with white
    DEBUG("Draw black image\r\n");
  
    Paint_DrawPoint(5, 70, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 80, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 50, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 70, 20, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawRectangle(60, 70, 90, 100, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(125, 85, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 15, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(5, 30, 123456789, &Font16, BLACK, WHITE);
    
    Paint_DrawPoint(5, 90, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 100, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(125, 70, 125, 100, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(110, 85, 140, 85, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 70, 50, 100, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(165, 85, 15, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 0, "waveshare Electronics", &Font12, BLACK, WHITE);
    Paint_DrawNum(5, 50, 987654321, &Font16, WHITE, RED);

    //2.Drawing on the image


    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN13D_Display();
    DEV_Delay_ms(2000);

    //4.Partial refresh, example shows time
#elif 0
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
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

        Paint_ClearWindows(110, 30, 110 + Font20.Width * 7, 30 + Font20.Height, WHITE);
        Paint_DrawTime(110, 30, &sPaint_time, &Font20, WHITE, BLACK);

        EPD_2IN13D_DisplayPart();
        DEV_Delay_ms(500);//Analog clock 1s
    }
#endif
  DEV_Delay_ms(5000);
  EPD_2IN13D_Init();
  EPD_2IN13D_Clear();

  EPD_2IN13D_Sleep();
  DEV_Module_Exit();
}

void loop() {

}
