#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

void setup() {
  DEBUG("2.13inch e-Paper B V4 demo\r\n");
  DEV_Module_Init();
  EPD_2IN13B_V4_Init();
  EPD_2IN13B_V4_Clear();
  DEV_Delay_ms(100);
  
#if 0
    /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black image
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);
    //3.Read BMP images into RAM
    SDCard_ReadBMP("2in13b4b.bmp", 0, 0);
  
    //Draw red image
    DEBUG("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("2in13b4r.bmp", 0, 0);

    //4.Refresh the image in RAM to e-Paper
    EPD_2IN13B_V4_Display();
    DEV_Delay_ms(4000);  
#elif 1
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    Paint_DrawBitMap(gImage_2in13b_V4b);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    Paint_DrawBitMap(gImage_2in13b_V4r);
    
    DEBUG("EPD_2IN13B_V4_Display\r\n");
    //3.Refresh the image in RAM to e-Paper
    EPD_2IN13B_V4_Display();
    DEV_Delay_ms(4000);
#endif

#if 1
    /*Horizontal screen*/
    //1.Draw black image
    DEBUG("Draw black image\r\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 70, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 80, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 50, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 70, 20, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawRectangle(60, 70, 90, 100, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(125, 85, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 15, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(5, 30, 123456789, &Font16, BLACK, WHITE);

    //2.Draw red image
    DEBUG("Draw red image\r\n");
    Paint_NewImage(IMAGE_BWR, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 90, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 100, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(125, 70, 125, 100, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(110, 85, 140, 85, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 70, 50, 100, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(165, 85, 15, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 0, "waveshare Electronics", &Font12, BLACK, WHITE);
    Paint_DrawNum(5, 50, 987654321, &Font16, WHITE, RED);

    //3.Refresh the image in RAM to e-Paper
    DEBUG("EPD_2IN13B_V4_Display\r\n");
    EPD_2IN13B_V4_Display();
    
#endif    
  DEV_Delay_ms(3000);
  EPD_2IN13B_V4_Clear();

  EPD_2IN13B_V4_Sleep();
  DEV_Module_Exit();
}

void loop() {

}
