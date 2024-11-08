#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
  DEBUG("EPD_3in52_test Demo\r\n");
  DEV_Module_Init();


  DEBUG("e-Paper Init and Clear...\r\n");
  EPD_3IN52_Init();
  EPD_3IN52_display_NUM(EPD_3IN52_WHITE);
  EPD_3IN52_lut_GC();
  EPD_3IN52_refresh();
  DEV_Delay_ms(100);
          
#if 1/*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_3IN52_WIDTH, EPD_3IN52_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_INVERTED);
    Paint_SetScale(2);
    Paint_Clear(WHITE);
    
    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("3in52.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_3IN52_display();
    EPD_3IN52_lut_GC();
    EPD_3IN52_refresh();
    DEV_Delay_ms(5000);
#endif
  
#if 0
  DEBUG("Draw picture\r\n");
  Paint_NewImage(IMAGE_BW, EPD_3IN52_WIDTH, EPD_3IN52_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_INVERTED);
	Paint_Clear(WHITE);	

  printf("Drawing:BlackImage\r\n");
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
  Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
  Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
  Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
  Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
  printf("EPD_Display\r\n");
  EPD_3IN52_display();
  EPD_3IN52_lut_GC();
  EPD_3IN52_refresh();
  DEV_Delay_ms(2000); 
#endif
  DEBUG("e-Paper Clear...\r\n");
  EPD_3IN52_Clear();
  DEV_Delay_ms(100); 
  EPD_3IN7_Sleep();

  // close 5V
  DEBUG("close 5V, Module enters 0 power consumption ...\r\n");
  DEV_Module_Exit();
  

}

void loop() {

}
