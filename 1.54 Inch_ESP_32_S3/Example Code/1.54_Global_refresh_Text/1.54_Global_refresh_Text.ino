#include <Arduino.h>         // Include the Arduino core library which provides basic Arduino functionality
#include "EPD_GUI.h"             // Include the EPD library used to control the Electronic Paper Display (E-Paper Display)
#include "Pic.h"        // Include the header file that contains picture data

#define Max_CharNum_PerLine 19//---152/8 (fontsize:16) Maximum number of characters per line

uint8_t ImageBW[2888];

char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.Support multiple development environments (Arduino IDE, ESP IDF, MicroPython), suitable for different people's needs, simplifying the secondary development process.Due to its excellent characteristics such as low power consumption, high contrast, and high reflectivity, this electronic paper screen is widely applicable to shelf tags, price tags, badges, smart tags, smart home devices, e-readers, smart wearable devices, and other portable devices, making it an ideal choice for various smart devices and applications.";

// Setup function, executed once when the program starts
void setup() {
    // Initialization settings
    pinMode(7, OUTPUT);        // Set pin 7 to output mode
    digitalWrite(7, HIGH);     // Set pin 7 to high level to activate the screen power

    EPD_GPIOInit();
    Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);
    Paint_Clear(WHITE);

    EPD_FastMode1Init();
    EPD_Display_Clear();
    EPD_FastUpdate();
    EPD_Clear_R26H();

    Long_Text_Display(0, 0, My_content_1, 16, BLACK);

    EPD_Display(ImageBW);
    EPD_FastUpdate();
    EPD_DeepSleep();

    delay(5000);              // Wait for 5000 milliseconds (5 seconds)
    clear_all();              // Call the clear_all function to clear the screen content
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
      //For example, if your screen height is 152 pixels and the height of each character is 16 pixels, then you can display 9 line
        if (y >= 152) {
            break;
        }
    }
}