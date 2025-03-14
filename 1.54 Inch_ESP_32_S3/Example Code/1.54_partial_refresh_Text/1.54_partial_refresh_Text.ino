#include <Arduino.h>         // Include the Arduino core library which provides basic Arduino functionality
#include "EPD_GUI.h"            // Include the EPD library used to control the Electronic Paper Display (E-Paper Display)
#include "Pic.h"

uint8_t ImageBW[2888];

int startX = 0; //Starting horizontal axis
int startY = 0;  //Starting ordinate
int fontSize = 16; // font size
int endX = 76;    // End horizontal axis
int endY = 152;    // End vertical axis

const char *My_content_1 = "It boasts a high resolution of 128*296, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.";

// Setup function, executed once when the program starts
void setup() {
    // Initialization settings

    // Configure the screen power pin
    pinMode(7, OUTPUT);        // Set pin 7 to output mode
    digitalWrite(7, HIGH);     // Set pin 7 to high level to activate the screen power

    EPD_GPIOInit();
    Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);
    Paint_Clear(WHITE);

    EPD_FastMode1Init();
    EPD_Display_Clear();
    EPD_FastUpdate();
    EPD_Clear_R26H();

    EPD_HW_RESET();

    Part_Text_Display(My_content_1, startX, startY, fontSize, BLACK, endX, endY);

    EPD_Display(ImageBW);
    EPD_FastUpdate();
    EPD_DeepSleep();

    delay(5000);             // Wait for 5000 milliseconds (5 seconds)

    clear_all();            // Call the clear_all function to clear the screen content
}

// Main loop function, currently no operations are being executed in this function
// Code that needs to be executed repeatedly can be added here
void loop() {

}

// Function to clear all content on the screen
void clear_all()
{
    EPD_Init();
    EPD_Display_Clear();
    EPD_Update();
    EPD_DeepSleep();
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

