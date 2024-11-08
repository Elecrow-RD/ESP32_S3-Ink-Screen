#include <Arduino.h>        // Include the core library for Arduino platform development
#include "EPD.h"            // Include the EPD library to control the E-Paper Display
#include "EPD_GUI.h"        // Include the EPD_GUI library which provides GUI functionalities
#include "pic_scenario.h"   // Include the header file containing image data

uint8_t Image_BW[15000];    // Declare an array of 15000 bytes to store black and white image data

void setup() {
  // Initialization settings, executed only once when the program starts
  // Configure pin 7 as output mode and set it to high level to activate the screen power
  pinMode(7, OUTPUT);            // Set pin 7 as output mode
  digitalWrite(7, HIGH);         // Set pin 7 to high level, activating the screen power

  EPD_GPIOInit();                // Initialize the GPIO pin configuration for the EPD e-ink screen

  // The SPI initialization part is commented out
  // SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  // SPI.begin ();

  EPD_Clear();                   // Clear the screen content, restoring it to its default state
  Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer, size EPD_W x EPD_H, background color white
  EPD_Full(WHITE);              // Fill the entire canvas with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW); // Display the image stored in the Image_BW array

  EPD_Init_Fast(Fast_Seconds_1_5s); // Quickly initialize the EPD screen, setting it to 1.5 second fast mode

  //EPD_ShowPicture(0, 0, 312, 152, gImage_1, WHITE); // Display image gImage_1, starting coordinates (0, 0), width 312, height 152, background color white
  EPD_ShowPicture(0, 0, 352, 104, gImage_tiaoma_1, WHITE);
  EPD_Display_Fast(Image_BW); // Quickly display the image stored in the Image_BW array

  EPD_Sleep();                // Set the screen to sleep mode to save power

  delay(5000);                // Wait for 5000 milliseconds (5 seconds), allowing the screen to stay in sleep mode for some time

  clear_all();               // Call the clear_all function to clear the screen content
}

void loop() {
  // Main loop function, currently does not perform any actions
  // Code that needs to be repeatedly executed can be added here
}

void clear_all() {
  // Function to clear the screen content
  EPD_Clear();                 // Clear the screen content, restoring it to its default state
  Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer, size EPD_W x EPD_H, background color white
  EPD_Full(WHITE);            // Fill the entire canvas with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW); // Display the image stored in the Image_BW array
}