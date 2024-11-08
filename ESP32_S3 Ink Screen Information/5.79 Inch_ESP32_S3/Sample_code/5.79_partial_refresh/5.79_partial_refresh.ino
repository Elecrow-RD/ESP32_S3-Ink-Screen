#include <Arduino.h>         // Introduce Arduino core library to provide basic Arduino functions
#include "EPD.h"             // Introduce EPD library for controlling electronic ink screens（E-Paper Display）
#include "pic_scenario.h"    // Introduce header files containing image data

uint8_t ImageBW[27200];      // Declare an array with a size of 27200 bytes for storing black and white image data

void setup() {
  // Initialize settings, executed once at program startup

  // Configure screen power pins
  pinMode(7, OUTPUT);        // Set pin 7 to output mode
  digitalWrite(7, HIGH);     // Set pin 7 to high level to activate the screen power supply

  EPD_GPIOInit();            // Initialize GPIO pin configuration for EPD e-ink screen
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); // Create a new image buffer with a size of EPD_W x EPD_H and a white background color
  Paint_Clear(WHITE);       // Clear the image buffer and fill it with white

  /************************Quick screen cleaning works in local flashing mode************************/
  EPD_FastMode1Init();       // Initialize EPD screen in Quick Mode 1
  EPD_Display_Clear();       // Clear screen content
  EPD_Update();              // Update screen display

  EPD_HW_RESET();           // Perform hardware reset operation to ensure the screen starts up normally

  EPD_ShowPicture(0, 0, 312, 152, gImage_1, WHITE); // Display image gImage_1 with starting coordinates of (0,0), width of 312, height of 152, and a white background color
  EPD_ShowPicture(320, 0, 256, 184, gImage_demo1, WHITE); // Display image gImage_1 with starting coordinates of (320,0), width of 312, height of 152, and a white background color

  EPD_Display(ImageBW);     // Display images stored in the ImageBW array
  EPD_PartUpdate();         // Update a portion of the screen to display new content
  EPD_DeepSleep();         //Set the screen to deep sleep mode to save power

  delay(5000);             // Wait for 5000 milliseconds (5 seconds)

 clear_all();            // Call the clear_all function to clear the screen content
}

void loop() {
  // Main loop function, currently not performing any operation
  // You can add code that needs to be executed repeatedly in this function
  
}

void clear_all()
{
  // Function to clear screen content
  EPD_FastMode1Init();     // Initialize EPD screen in Quick Mode 1
  EPD_Display_Clear();     // Clear screen content
  EPD_Update();            // Update screen display
}
