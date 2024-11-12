#include <Arduino.h>
#include "EPD.h"
#include "EPD_GUI.h"
#include "pic_scenario.h"

#define Max_CharNum_PerLine 34//---416/12  Maximum number of characters per line

uint8_t ImageBW[12480];
char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.Support multiple development environments (Arduino IDE, ESP IDF, MicroPython), suitable for different people's needs, simplifying the secondary development process.Due to its excellent characteristics such as low power consumption, high contrast, and high reflectivity, this electronic paper screen is widely applicable to shelf tags, price tags, badges, smart tags, smart home devices, e-readers, smart wearable devices, and other portable devices, making it an ideal choice for various smart devices and applications.";

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  EPD_GPIOInit();
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE); //Clear Canvas

  EPD_FastInit();
  EPD_Display_Clear();
  EPD_Update(); 

   //Power on interface

  //  EPD_PartInit();
  EPD_FastInit();

  Long_Text_Display(0, 0, My_content_1, 24, BLACK);

  EPD_Display(ImageBW);
  EPD_Update();
  EPD_DeepSleep();
}

void loop() {
  // put your main code here, to run repeatedly:

}


/*
--------Text display--------
*x: Starting horizontal axis
*y: Starting ordinate
*Content: Displayed Text
*FontSize: font size
*Color: font color
*/
void Long_Text_Display(int x, int y, const char* content, int fontSize, int color) {
    int length = strlen(content);
    int i = 0;
    char line[Max_CharNum_PerLine + 1]; //+1 is to place the string terminator '\ 0'

    while (i < length) {
        int lineLength = 0;
        memset(line, 0, sizeof(line));//Clear the line buffer

       //Fill the line until it reaches the screen width or the end of the string
        while (lineLength < Max_CharNum_PerLine && i < length) {
            line[lineLength++] = content[i++];
        }

        EPD_ShowString(x, y, line, fontSize, color);//Display this line
        y += fontSize; //Update the y-coordinate for displaying the next line

      //If there are still remaining strings and the next line exceeds the screen height, stop displaying
      //You need to decide when to stop displaying based on your screen height here
      //For example, if your screen height is 240 pixels and the height of each character is 24 pixels, then you can display 10行
        if (y >= 240) {
            break;
        }
    }
}