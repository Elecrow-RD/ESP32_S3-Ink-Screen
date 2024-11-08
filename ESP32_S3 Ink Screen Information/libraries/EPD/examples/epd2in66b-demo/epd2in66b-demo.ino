#include "EPD.h"
#include "GUI_Paint.h"
#include "EPD_SDCard.h"

void setup() {
	DEBUG("EPD_2in66b_test Demo\r\n");
	if(DEV_Module_Init()!=0){
		return -1;
	}

	DEBUG("e-Paper Init and Clear...\r\n");
	EPD_2IN66B_Init();
	EPD_2IN66B_Clear();
	DEV_Delay_ms(100);

#if 0
	/*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN66B_WIDTH, EPD_2IN66B_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("2in66bb.bmp", 0, 0);
	
    DEBUG("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BWR, EPD_2IN66B_WIDTH, EPD_2IN66B_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("2in66br.bmp", 0, 0);
	
    //4.Refresh the picture in RAM to e-Paper
    EPD_2IN66B_Display();
    DEV_Delay_ms(5000);
#endif
  
#if 1
    //1.Draw black image
    DEBUG("Draw black image\r\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN66B_WIDTH, EPD_2IN66B_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
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
    Paint_NewImage(IMAGE_BWR, EPD_2IN66B_WIDTH, EPD_2IN66B_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 90, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 100, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(125, 70, 125, 100, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(110, 85, 140, 85, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 70, 50, 100, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(165, 85, 15, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 0, "waveshare Electronics", &Font12, BLACK, WHITE);
    Paint_DrawNum(5, 50, 987654321, &Font16, WHITE, RED);

	EPD_2IN66B_Display();
	DEV_Delay_ms(5000); 
#endif
	DEBUG("e-Paper Clear...\r\n");
	EPD_2IN66B_Clear();
	
	EPD_2IN66B_Sleep();
	DEV_Delay_ms(3000); //at least 3s
	
	// close 5V
	DEBUG("close 5V, Module enters 0 power consumption ...\r\n");
	DEV_Module_Exit();

	return 0;
}

void loop() {

}
