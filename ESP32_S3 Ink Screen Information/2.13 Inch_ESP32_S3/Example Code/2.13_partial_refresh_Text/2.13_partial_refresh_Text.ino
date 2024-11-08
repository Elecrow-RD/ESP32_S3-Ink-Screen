#include <Arduino.h>         // Include Arduino core library for basic Arduino functions
#include "EPD.h"           // Include library for controlling Electronic Paper Display (EPD)
#include "Pic.h"

// Define an array to store image data
extern uint8_t ImageBW[ALLSCREEN_BYTES];

int startX = 0; //Starting horizontal axis
int startY = 0;  //Starting ordinate
int fontSize = 16; // font size
int endX = 125;    // End horizontal axis
int endY = 122;    // End vertical axis

const char *My_content_1 = "It boasts a high resolution of 128*296, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.";

// Function to set up the system. Executed once when the program starts.
void setup() {
    // Configure pin 7 for screen power control
    pinMode(7, OUTPUT);        // Set pin 7 as output
    digitalWrite(7, HIGH);     // Activate screen power by setting pin 7 high

    EPD_Init();                // Initialize the EPD
    EPD_ALL_Fill(WHITE);       // Fill the entire EPD with white color
    EPD_Update();              // Update the EPD display
    EPD_Clear_R26H();          // Clear the EPD using a specific method

    Part_Text_Display(My_content_1, startX, startY, fontSize, BLACK, endX, endY);

    EPD_DisplayImage(ImageBW); // Display the image stored in ImageBW array
    EPD_PartUpdate();          // Perform a partial update on the EPD
    EPD_Sleep();               // Put the EPD to sleep mode

    delay(5000);               // Wait for 5000 milliseconds (5 seconds)

    clear_all();               // Call the clear_all function to clear the screen
}

// The main loop function. Currently, it does not perform any operations.
// In this function, code that needs to be repeated can be added.
void loop() {
}

// Function to clear all content on the EPD.
void clear_all() {
    EPD_Init();                // Initialize the EPD
    EPD_ALL_Fill(WHITE);       // Fill the entire EPD with white color
    EPD_Update();              // Update the EPD display
    EPD_Clear_R26H();          // Clear the EPD using a specific method
    EPD_Sleep();               // Put the EPD to sleep mode
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
        EPD_ShowString(currentX, currentY, line, color, fontSize); 

        // Update the Y coordinate for displaying the next line
        currentY += lineHeight;

        // If there are still remaining strings but they have reached the bottom of the area, stop displaying them
        if (currentY + lineHeight > endY) {
            break;
        }
    }
}


