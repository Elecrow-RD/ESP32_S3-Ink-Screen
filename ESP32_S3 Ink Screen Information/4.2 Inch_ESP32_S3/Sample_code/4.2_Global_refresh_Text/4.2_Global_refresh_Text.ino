#include <Arduino.h>        // Include the core library for Arduino platform development
#include "EPD.h"            // Include the EPD library for controlling E-Paper Displays
#include "EPD_GUI.h"        // Include the EPD_GUI library which provides graphical user interface functions
#include "pic_scenario.h"   // Include the header file containing image data

#define Max_CharNum_PerLine 33//---400/12  Maximum number of characters per line

uint8_t Image_BW[15000];    // Declare an array of 15000 bytes to store black and white image data
char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios. Support multiple development environments (Arduino IDE, ESP IDF, MicroPython), suitable for different people's needs, simplifying the secondary development process. Due to its excellent characteristics such as low power consumption, high contrast, and high reflectivity, this electronic paper screen is widely applicable to shelf tags, price tags, badges, smart tags, smart home devices, e-readers, smart wearable devices, and other portable devices, making it an ideal choice for various smart devices and applications.";

void setup() {
  // Initialization settings, only executed once at startup
  // Initialize the screen power
  pinMode(7, OUTPUT);            // Set pin 7 to output mode for controlling the screen power
  digitalWrite(7, HIGH);         // Set pin 7 to high level to activate the screen power

  EPD_GPIOInit();                // Initialize the GPIO pin configuration for the EPD e-ink screen

  // SPI initialization part is commented out
  // SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  // SPI.begin ();

  EPD_Clear();                   // Clear the screen content, restoring it to the default state
  Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer, set the size to EPD_W x EPD_H, background color to white
  EPD_Full(WHITE);              // Fill the entire canvas with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW); // Display the image stored in the Image_BW array

  EPD_Init_Fast(Fast_Seconds_1_5s); // Fast initialize the EPD screen, set to 1.5 second fast mode

  // Display the startup interface
  Long_Text_Display(0, 0, My_content_1, 24, BLACK);
  // EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW); // Commented code for displaying the image in the Image_BW array
  EPD_Display_Fast(Image_BW); // Quickly display the image stored in the Image_BW array
  EPD_Sleep();                // Set the screen to sleep mode to save power

  delay(5000);                // Wait for 5000 milliseconds (5 seconds), allowing the screen to stay in sleep mode for some time

  clear_all();               // Call the clear_all function to clear the screen content
}

void loop() {
  // Main loop function, currently does not perform any operations
  // You can add code here that needs to be executed repeatedly
}

void clear_all() {
  // Function to clear the screen content
  EPD_Clear();                 // Clear the screen content, restoring it to the default state
  Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer, set the size to EPD_W x EPD_H, background color to white
  EPD_Full(WHITE);            // Fill the entire canvas with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW); // Display the image stored in the Image_BW array
}

/*
--------Text display--------
*x: Starting horizontal position
*y: Starting vertical position
*Content: Text to display
*FontSize: Font size
*Color: Font color
*/
void Long_Text_Display(int x, int y, const char* content, int fontSize, int color) {
    int length = strlen(content);
    int i = 0;
    char line[Max_CharNum_PerLine + 1]; //+1 is to place the string terminator '\0'

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
        //For example, if your screen height is 300 pixels and the height of each character is 24 pixels, then you can display 12 lines
        if (y >= 300) {
            break;
        }
    }
}