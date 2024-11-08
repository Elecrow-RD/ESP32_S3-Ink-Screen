#include "EPD.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "EPD_SDCard.h"

void setup() {
 DEV_Module_Init();
 DEBUG("1.54inch e-Paper B demo\r\n");
  EPD_1IN54B_V2_Init();
  EPD_1IN54B_V2_Clear();
  DEV_Delay_ms(500);
  
#if 0
    /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black image
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_1IN54B_V2_WIDTH, EPD_1IN54B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //3.Read BMP images into RAM
    SDCard_ReadBMP("1in54b-b.bmp", 0, 0);

    //Draw red image
    DEBUG("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_1IN54B_V2_WIDTH, EPD_1IN54B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("1in54b-r.bmp", 0, 0);
    //4.Refresh the image in RAM to e-Paper
    EPD_1IN54B_V2_Display();
    DEV_Delay_ms(2000);  
#elif 0
    /*show image for array*/
    DEBUG("show image for array\r\n");
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_1IN54B_V2_WIDTH, EPD_1IN54B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    Paint_DrawBitMap(IMAGE_BLACK);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_1IN54B_V2_WIDTH, EPD_1IN54B_V2_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);   
    Paint_DrawBitMap(IMAGE_RED );
    
    DEBUG("EPD_1IN54B_V2_Display\r\n");
    //3.Refresh the image in RAM to e-Paper
    EPD_1IN54B_V2_Display();
    DEV_Delay_ms(2000);
#endif    

#if 1
    /*Horizontal screen*/
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_1IN54B_V2_WIDTH, EPD_1IN54B_V2_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 10, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);   
    Paint_DrawLine(45, 70, 45, 110, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_2X2);
    Paint_DrawLine(25, 90, 65, 90, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_2X2);
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
    Paint_DrawCircle(115, 90, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_2X2);
    Paint_DrawNum(30, 145, 123456789, &Font20, WHITE, BLACK);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_1IN54B_V2_WIDTH, EPD_1IN54B_V2_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_2X2);        
    Paint_DrawRectangle(90, 10, 140, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_2X2);        
    Paint_DrawCircle(45, 90, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);    
    Paint_DrawString_EN(30, 115, "waveshare", &Font20, BLACK, WHITE);    
    
    //3.Refresh the image in RAM to e-Paper
    EPD_1IN54B_V2_Display();  
    
#endif
    DEV_Delay_ms(3000);
    DEBUG("clear \r\n");
    EPD_1IN54B_V2_Clear();
    DEBUG("go to sleep \r\n");
    EPD_1IN54B_V2_Sleep();
    DEV_Module_Exit();
}

void loop() {

}
