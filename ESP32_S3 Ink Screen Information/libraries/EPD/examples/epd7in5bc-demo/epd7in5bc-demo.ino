#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
 DEBUG("7.5inch e-Paper B and C demo\r\n");
 DEV_Module_Init();
  
  EPD_7IN5BC_Init();
  EPD_7IN5BC_Clear();
  DEV_Delay_ms(300);

#if 0
      /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);
    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("7in5b-b.bmp", 0, 0);

    //Draw red picture
    DEBUG("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("7in5b-r.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_7IN5BC_Display();
    DEV_Delay_ms(2000);
#endif

#if 1
    //1.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    Paint_NewImage(IMAGE_BW, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //2.Drawing on the image
    Paint_DrawPoint(25, 50, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 70, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 90, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 110, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(50, 50, 150, 150, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(150, 50, 50, 150, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(100, 200, 100, 300, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 250, 150, 250, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

    //Draw red picture
    Paint_NewImage(IMAGE_BWR, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    Paint_DrawRectangle(50, 50, 150, 150, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(200, 50, 300, 150, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(100, 250, 50, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(250, 250, 50, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 310, "hello world", &Font24, WHITE, RED);
    Paint_DrawString_EN(10, 335, "Waveshare Electronics", &Font24, RED, WHITE);

    Paint_DrawNum(10, 360, 123456789, &Font24, RED, WHITE);

    //3.Refresh the picture in RAM to e-Paper
    EPD_7IN5BC_Display();
#endif



  DEV_Delay_ms(4000);
  EPD_7IN5BC_Clear();
  
  EPD_7IN5BC_Sleep();
  DEV_Module_Exit();
}

void loop() {

}
