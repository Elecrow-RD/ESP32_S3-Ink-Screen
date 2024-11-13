#include <Arduino.h>         // Include Arduino core library for basic Arduino functions
#include "EPD.h"             // Include library for controlling Electronic Paper Display (EPD)
#include "Pic.h"        // Include header file containing picture data

#define Max_CharNum_PerLine 31//---250/8 (fontsize:16) Maximum number of characters per line

// Define an array to store image data for the EPD.
extern uint8_t ImageBW[ALLSCREEN_BYTES];

char *My_content_1 = "Name: Rob Oudendijk";

// Function to set up the system. Executed once when the program starts.
void setup() {
    // Configure pin 7 for screen power control.
    pinMode(7, OUTPUT);        // Set pin 7 as output.
    digitalWrite(7, HIGH);     // Activate screen power by setting pin 7 high.

    EPD_Init();                // Initialize the EPD.
    EPD_ALL_Fill(WHITE);       // Fill the entire EPD with white color.
    EPD_Update();              // Update the EPD display.
    EPD_Clear_R26H();          // Clear the EPD using a specific method.

    // Display a picture on the EPD.
    Long_Text_Display(0, 0, My_content_1, 24, BLACK);
    EPD_DisplayImage(ImageBW); // Display the image stored in ImageBW array.
    EPD_PartUpdate();          // Perform a partial update on the EPD.
    EPD_Sleep();               // Put the EPD to sleep mode.

    // delay(5000);               // Wait for 5000 milliseconds (5 seconds).

    // clear_all();               // Call the clear_all function to clear the screen.
}

// The main loop function. Currently, it does not perform any operations.
// In this function, code that needs to be repeated can be added.
void loop() {
}

// Function to clear all content on the EPD.
void clear_all() {
    EPD_Init();                // Initialize the EPD.
    EPD_ALL_Fill(WHITE);       // Fill the entire EPD with white color.
    EPD_Update();              // Update the EPD display.
    EPD_Clear_R26H();          // Clear the EPD using a specific method.
    EPD_Sleep();               // Put the EPD to sleep mode.
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

        EPD_ShowString(x, y, line, color, fontSize);//Display this line
        y += fontSize; //Update the y-coordinate for displaying the next line

      //If there are still remaining strings and the next line exceeds the screen height, stop displaying
      //You need to decide when to stop displaying based on your screen height here
      //For example, if your screen height is 122 pixels and the height of each character is 16 pixels, then you can display 7 line
        if (y >= 122) {
            break;
        }
    }
}
