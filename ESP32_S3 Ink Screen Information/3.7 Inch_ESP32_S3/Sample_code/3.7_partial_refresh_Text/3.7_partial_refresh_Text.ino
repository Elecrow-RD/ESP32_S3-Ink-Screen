#include <Arduino.h>
#include "EPD.h"
#include "EPD_GUI.h"
#include "pic_scenario.h"
uint8_t ImageBW[12480];

int startX = 0; //Starting horizontal axis
int startY = 0;  //Starting ordinate
int fontSize = 24; // font size
int endX = 200;    // End horizontal axis
int endY = 240;    // End vertical axis

const char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.";

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  EPD_GPIOInit();
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 180, WHITE);
  Paint_Clear(WHITE); //Clear Cannavs

  EPD_FastInit();
  EPD_Display_Clear();
  EPD_Update();

  EPD_FastInit();

  Part_Text_Display(My_content_1, startX, startY, fontSize, BLACK, endX, endY);

  EPD_Display(ImageBW);
  EPD_Update();
  EPD_DeepSleep();
  delay(5000);
  clear_all();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void clear_all()
{
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE); //Clear Cannavs
  EPD_FastInit();
  EPD_Display_Clear();
  EPD_Update();  //Before flashing, clear the screen of E-Paper first
}

/*
*---------Function description: Display text content locally------------
*----Parameter introduction:
      content：Text content
      startX：Starting horizontal axis
      startY：Starting ordinate
      fontSize：font size
      color：font color
      endX：End horizontal axis
      endY：End vertical axis
*/
void Part_Text_Display(const char* content, int startX, int startY, int fontSize, int color, int endX, int endY) {
    int length = strlen(content);
    int i = 0;
    char line[(endX - startX) / (fontSize/2) + 1]; //Calculate the maximum number of characters per line based on the width of the area
    int currentX = startX;
    int currentY = startY;
    int lineHeight = fontSize;

    while (i < length) {
        int lineLength = 0;
        memset(line, 0, sizeof(line));

        //Fill the line until it reaches the width of the region or the end of the string
        while (lineLength < (endX - startX) / (fontSize/2) && i < length) {
            line[lineLength++] = content[i++];
        }

        // If the current Y coordinate plus font size exceeds the area height, stop displaying
        if (currentY + lineHeight > endY) {
            break;
        }
        // Display this line
        EPD_ShowString(currentX, currentY, line, fontSize, color); 

        // Update the Y coordinate for displaying the next line
        currentY += lineHeight;

        // If there are still remaining strings but they have reached the bottom of the area, stop displaying them
        if (currentY + lineHeight > endY) {
            break;
        }
    }
}

