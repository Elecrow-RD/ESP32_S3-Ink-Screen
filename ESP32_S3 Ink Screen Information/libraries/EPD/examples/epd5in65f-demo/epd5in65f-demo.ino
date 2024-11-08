#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
	DEBUG("EPD_5in65F_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

	DEBUG("e-Paper Init and Clear...\r\n");
	EPD_5IN65F_Init();
	EPD_5IN65F_Clear(EPD_5IN65F_WHITE);
	DEV_Delay_ms(100);
					
#if 1
      /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_5IN65F_WIDTH, EPD_5IN65F_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_SetScale(7);
    Paint_Clear(EPD_5IN65F_WHITE);
    
    //3.Read BMP pictures into RAM
    SDCard_Read_RGB_7Color("5in65f1.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_5IN65F_Display();
    DEV_Delay_ms(5000);
#endif
	
#if 0
	DEBUG("Draw black picture\r\n");
	Paint_NewImage(IMAGE_BW, EPD_5IN65F_WIDTH, EPD_5IN65F_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
	Paint_SetScale(7);
	Paint_Clear(EPD_5IN65F_WHITE);
  
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
	Paint_DrawString_EN(10, 130, "waveshare", &Font16, BLACK, WHITE);
	Paint_DrawString_EN(10, 150, "hello world", &Font12, WHITE, BLACK);
 
	Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
	Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
  
	EPD_5IN65F_Display();
	DEV_Delay_ms(5000); 
#endif
	DEBUG("e-Paper Clear...\r\n");
	EPD_5IN65F_Clear(EPD_5IN65F_WHITE);
	DEV_Delay_ms(100); 
	EPD_5IN65F_Sleep();

	// close 5V
	DEBUG("close 5V, Module enters 0 power consumption ...\r\n");
	DEV_Module_Exit();
	
	return 0;
}

void loop() {

}
