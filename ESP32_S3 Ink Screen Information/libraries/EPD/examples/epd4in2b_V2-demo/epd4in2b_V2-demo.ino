#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
  DEBUG("4.2inch e-Paper B V2 demo\r\n");
  DEV_Module_Init();
  
  EPD_4IN2B_V2_Init();
  EPD_4IN2B_V2_Clear();


#if 1
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_4IN2B_V2_WIDTH, EPD_4IN2B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("4in2b-b.bmp", 0, 0);
    
    //Draw yellow picture
    DEBUG("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_4IN2B_V2_WIDTH, EPD_4IN2B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("4in2b-r.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_4IN2B_V2_Display();
    DEV_Delay_ms(2000);
#endif

#if 1
    //1.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    Paint_NewImage(IMAGE_BW, EPD_4IN2B_V2_WIDTH, EPD_4IN2B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 20, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 20, 50, 50, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 20, 20, 50, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawRectangle(60, 20, 90, 50, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(35, 90, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 120, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(5, 140, 123456789, &Font12, BLACK, WHITE);
    // EPD_4IN2B_V2_SetBlack();

    //Draw yellow picture
    Paint_NewImage(IMAGE_BWR, EPD_4IN2B_V2_WIDTH, EPD_4IN2B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    
    Paint_DrawPoint(5, 30, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(35, 75, 35, 105, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(20, 90, 50, 90, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 20, 50, 50, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(75, 90, 15, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 160, "waveshare", &Font16, RED, WHITE);
    Paint_DrawNum(5, 180, 987654321, &Font16, WHITE, RED);
    // EPD_4IN2B_V2_SetRed();

    //show
    DEBUG("EPD_4IN2B_V2_Display...\n");
    EPD_4IN2B_V2_Display();
    DEV_Delay_ms(4000);
#endif
  DEV_Delay_ms(4000);
  EPD_4IN2B_V2_Clear();
  
  EPD_4IN2B_V2_Sleep();
  DEV_Module_Exit();
}

void loop() {

}
