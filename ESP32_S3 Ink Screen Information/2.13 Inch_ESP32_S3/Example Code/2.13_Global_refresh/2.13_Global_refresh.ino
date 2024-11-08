#include <Arduino.h>         // Include Arduino core library for basic Arduino functions
#include "EPD.h"             // Include library for controlling Electronic Paper Display (EPD)
#include "Pic.h"        // Include header file containing picture data

// Define an array to store image data for the EPD.
extern uint8_t ImageBW[ALLSCREEN_BYTES];

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
    EPD_ShowPicture(0, 0, 248, 122, gImage_black_ground, BLACK);
    EPD_DisplayImage(ImageBW); // Display the image stored in ImageBW array.
    EPD_PartUpdate();          // Perform a partial update on the EPD.
    EPD_Sleep();               // Put the EPD to sleep mode.

    delay(5000);               // Wait for 5000 milliseconds (5 seconds).

    clear_all();               // Call the clear_all function to clear the screen.
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
