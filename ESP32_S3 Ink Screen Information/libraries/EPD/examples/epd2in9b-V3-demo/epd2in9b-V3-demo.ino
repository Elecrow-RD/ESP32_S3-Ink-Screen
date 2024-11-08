#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
  delay(10);
  DEBUG("2.9inch b V3 e-Paper demo\r\n");
  DEV_Module_Init();
  EPD_2IN9B_V3_Init();
  EPD_2IN9B_V3_Clear();
  DEV_Delay_ms(500);
#if 1
      /*show sd card pic*/
    //1.Initialize the SD card
    DEBUG("Initialize the SD card\r\n");
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9B_V3_WIDTH, EPD_2IN9B_V3_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("2in9cb.bmp", 0, 0);
    
    Paint_NewImage(IMAGE_BWR, EPD_2IN9B_V3_WIDTH, EPD_2IN9B_V3_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("2in9cy.bmp", 0, 0);
    
    //4.Refresh the picture in RAM to e-Paper
    EPD_2IN9B_V3_Display();
    DEV_Delay_ms(2000);
#elif 0
    DEBUG("Paint_NewImage\r\n");
    
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9B_V3_WIDTH, EPD_2IN9B_V3_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //2.Drawing on the image
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);

    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    
    Paint_NewImage(IMAGE_BWR, EPD_2IN9B_V3_WIDTH, EPD_2IN9B_V3_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawCircle(160, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(210, 95, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 0, "hello world", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 30, "Waveshare", &Font24, BLACK, WHITE);

    //3.Refresh the picture in RAM to e-Paper
    DEBUG("EPD_Display\r\n");
    EPD_2IN9B_V3_Display();
    DEV_Delay_ms(2000);
#endif
  DEV_Delay_ms(3000);
  EPD_2IN9B_V3_Clear();

  EPD_2IN9B_V3_Sleep();
  DEV_Module_Exit();
}

void loop() {

}
