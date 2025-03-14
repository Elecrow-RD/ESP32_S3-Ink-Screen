#include <Arduino.h>
#include "EPD.h"           // Include EPD library for operating the e-paper display
#include "pic_scenario.h" // Include header file containing image data

extern uint8_t ImageBW[ALLSCREEN_BYTES]; // External declaration of an array to store image data

void setup() {
  // Initialization settings, executed only once
  pinMode(7, OUTPUT);             // Set pin 7 to output mode
  digitalWrite(7, HIGH);          // Set pin 7 to high level to power on the screen

  EPD_Init();                     // Initialize the EPD e-paper display
  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the area from (0,0) to (296,128) on the screen, background color is white
  EPD_ALL_Fill(WHITE);           // Fill the entire screen with white
  EPD_Update();                  // Update the screen display content to make the clear operation take effect

  EPD_Clear_R26H();              // Clear the R26H area of the screen

  EPD_ShowPicture(0, 0, 296, 128, gImage_scenario_home, BLACK); // Display the image in the area from (0,0) to (296,128), background color is black
  EPD_DisplayImage(ImageBW);     // Display the image stored in the ImageBW array
  EPD_FastUpdate();              // Quickly update the screen content

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
  EPD_ALL_Fill(WHITE);         // Fill the entire screen with white
  EPD_Update();                // Update the screen display content to make the clear operation take effect
  EPD_Clear_R26H();            // Clear the R26H area of the screen
}