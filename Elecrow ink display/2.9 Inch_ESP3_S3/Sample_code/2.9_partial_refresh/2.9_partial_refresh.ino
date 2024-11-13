#include <Arduino.h>      // Include the Arduino core library for development on the Arduino platform
#include "EPD.h"          // Include the EPD library for controlling the electronic ink screen (E-Paper Display)
#include "pic_scenario.h" // Include the header file containing image data

extern uint8_t ImageBW[ALLSCREEN_BYTES]; // External declaration of an array to store image data ImageBW

void setup() {
  // Initialization settings, executed only once at program startup
  // Initialize the screen power supply
  pinMode(7, OUTPUT);             // Set pin 7 to output mode to control the screen power
  digitalWrite(7, HIGH);          // Set pin 7 to high level to activate the screen power

  EPD_Init();                     // Initialize the EPD electronic ink screen to prepare for screen operations

  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the area from (0,0) to (296,128) on the screen, background color is white
  EPD_ALL_Fill(WHITE);           // Fill the entire screen with white
  EPD_Update();                  // Update the screen display content to make the clear and fill operations take effect

  EPD_Clear_R26H();              // Clear the content of the R26H area, the specific cleared area depends on the screen design

  // Display image
  EPD_ShowPicture(0, 0, 112, 96, gImage_12, BLACK); // Display the image gImage_12 in the area from (0,0) to (112,96) on the screen, background color is black
  EPD_DisplayImage(ImageBW);    // Display the image stored in the ImageBW array
  EPD_FastUpdate();             // Quickly update the screen content to display the image

  // EPD_PartUpdate(); // Commented-out code, possibly used to update a part of the screen

  EPD_Sleep();                  // Set the screen to sleep mode to reduce power consumption
  delay(5000);                  // Wait for 5000 milliseconds (5 seconds), allowing the screen to stay in sleep mode for some time

  clear_all();                  // Call the clear_all function to clear the screen content
}

void loop() {
  // Main loop function, currently does not perform any actions
  // Code that needs to be executed repeatedly can be added in this function
}

void clear_all() {
  // Function to clear the screen content
  EPD_Init();                  // Initialize the EPD electronic ink screen
  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the area from (0,0) to (296,128) on the screen, background color is white
  EPD_ALL_Fill(WHITE);        // Fill the entire screen with white
  EPD_Update();               // Update the screen display content to make the clear and fill operations take effect
  EPD_Clear_R26H();           // Clear the content of the R26H area
}