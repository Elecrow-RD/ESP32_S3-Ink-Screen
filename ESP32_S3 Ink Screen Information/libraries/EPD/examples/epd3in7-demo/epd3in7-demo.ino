#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
  DEBUG("EPD_3in7_test Demo\r\n");
  DEV_Module_Init();


  DEBUG("e-Paper Init and Clear...\r\n");
  EPD_3IN7_4Gray_Init();
  EPD_3IN7_4Gray_Clear();
  DEV_Delay_ms(100);
          
#if 1/*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_3IN7_WIDTH, EPD_3IN7_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_SetScale(4);
    Paint_Clear(WHITE);
    
    //3.Read BMP pictures into RAM
    SDCard_Read_4GrayBMP("3in7Gray.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_3IN7_4Gray_Display();
    DEV_Delay_ms(5000);
#endif
  
#if 0
  DEBUG("Draw picture\r\n");
  Paint_NewImage(IMAGE_BW, EPD_3IN7_WIDTH, EPD_3IN7_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
  Paint_SetScale(4);
  Paint_Clear(WHITE);
  
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
  Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
  Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
  
  EPD_3IN7_4Gray_Display();
  DEV_Delay_ms(5000); 
#endif
  
#if 0
  DEBUG("Draw 4-Gray picture\r\n");
  Paint_NewImage(IMAGE_BW, EPD_3IN7_WIDTH, EPD_3IN7_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
  Paint_SetScale(4);
  Paint_Clear(WHITE);
  
  Paint_DrawString_EN(10, 150, "GRAY1 with black background", &Font24, BLACK, GRAY1);
  Paint_DrawString_EN(10, 175, "GRAY3 with white background", &Font24, WHITE, GRAY3);
  Paint_DrawString_EN(10, 200, "GRAY2 with white background", &Font24, WHITE, GRAY2);
  Paint_DrawString_EN(10, 225, "GRAY4 with white background", &Font24, WHITE, GRAY4);
  
  EPD_3IN7_4Gray_Display();
  DEV_Delay_ms(5000); 
#endif

#if 0
    EPD_3IN7_1Gray_Init();       //init 1 Gray mode
    EPD_3IN7_1Gray_Clear();
    Paint_NewImage(IMAGE_BW, EPD_3IN7_WIDTH, EPD_3IN7_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_SetScale(2);
    Paint_Clear(WHITE);
    DEBUG("show time, partial update, just 1 Gary mode\r\n");
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 10;
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
        Paint_ClearWindows(300, 0, 479, 80, WHITE);
        Paint_DrawTime(320, 20, &sPaint_time, &Font20, WHITE, BLACK);
        
        if(num-- == 0) 
            break;
            
        DEBUG("Part refresh...\r\n");
        EPD_3IN7_1Gray_Display();
    }
#endif
  EPD_3IN7_4Gray_Init();
  DEBUG("e-Paper Clear...\r\n");
  EPD_3IN7_4Gray_Clear();
  DEV_Delay_ms(100); 
  EPD_3IN7_Sleep();

  // close 5V
  DEBUG("close 5V, Module enters 0 power consumption ...\r\n");
  DEV_Module_Exit();
  

}

void loop() {

}
