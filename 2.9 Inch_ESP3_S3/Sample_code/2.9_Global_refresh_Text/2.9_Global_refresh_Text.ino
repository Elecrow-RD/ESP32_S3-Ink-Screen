#include <Arduino.h>
#include "EPD.h"           // Include EPD library for operating the e-paper display
#include "pic_scenario.h" // Include header file containing image data

#define Max_CharNum_PerLine 37 // 296/8 (font size: 16) Maximum number of characters per line

extern uint8_t ImageBW[ALLSCREEN_BYTES]; // External declaration of an array to store image data

char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios. Support multiple development environments (Arduino IDE, ESP IDF, MicroPython), suitable for different people's needs, simplifying the secondary development process. Due to its excellent characteristics such as low power consumption, high contrast, and high reflectivity, this electronic paper screen is widely applicable to shelf tags, price tags, badges, smart tags, smart home devices, e-readers, smart wearable devices, and other portable devices, making it an ideal choice for various smart devices and applications.";

void setup() {
  // Initialization settings, executed only once
  pinMode(7, OUTPUT);             // Set pin 7 to output mode
  digitalWrite(7, HIGH);          // Set pin 7 to high level to power on the screen

  EPD_Init();                     // Initialize the EPD e-paper display
  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the area from (0,0) to (296,128) on the screen, background color is white
  EPD_ALL_Fill(WHITE);           // Fill the entire screen with white
  EPD_Update();                  // Update the screen display content to make the clear operation take effect
  EPD_Clear_R26H();              // Clear the R26H area of the screen

  Long_Text_Display(0, 0, My_content_1, 16, BLACK);

  EPD_DisplayImage(ImageBW);    // Display the image stored in the ImageBW array
  EPD_FastUpdate();             // Quickly update the screen content
  //  EPD_PartUpdate(); // Commented-out code, possibly used to update a part of the screen
  EPD_Sleep();                  // Set the screen to sleep mode to reduce power consumption

  delay(5000);                  // Wait for 5000 milliseconds (5 seconds)
  clear_all();                  // Call the clear_all function to clear the screen content
}

void loop() {
  // Main loop code, no operations here
}

void clear_all() {
  // Function to clear all screen content
  EPD_Init();                  // Initialize the EPD e-paper display
  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the area from (0,0) to (296,128) on the screen, background color is white
  EPD_ALL_Fill(WHITE);        // Fill the entire screen with white
  EPD_Update();               // Update the screen display content to make the clear operation take effect
  EPD_Clear_R26H();           // Clear the R26H area of the screen
}

/*
--------Text display--------
*x: Starting horizontal axis
*y: Starting vertical axis
*content: Displayed text
*fontSize: Font size
*color: Font color
*/
void Long_Text_Display(int x, int y, const char* content, int fontSize, int color) {
    int length = strlen(content);
    int i = 0;
    char line[Max_CharNum_PerLine + 1]; // +1 is to place the string terminator '\0'

    while (i < length) {
        int lineLength = 0;
        memset(line, 0, sizeof(line)); // Clear the line buffer

        // Fill the line until it reaches the screen width or the end of the string
        while (lineLength < Max_CharNum_PerLine && i < length) {
            line[lineLength++] = content[i++];
        }

        EPD_ShowString(x, y, line, color, fontSize); // Display this line
        y += fontSize; // Update the y-coordinate for displaying the next line

        // If there are still remaining strings and the next line exceeds the screen height, stop displaying
        // You need to decide when to stop displaying based on your screen height here
        // For example, if your screen height is 128 pixels and the height of each character is 16 pixels, then you can display 8 lines
        if (y >= 128) {
            break;
        }
    }
}