#include <Arduino.h>         // Include the Arduino core library which provides basic Arduino functionality
#include "EPD_GUI.h"             // Include the EPD library used to control the Electronic Paper Display (E-Paper Display)
#include "Pic.h"        // Include the header file that contains picture data

uint8_t ImageBW[2888];

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

    EPD_ShowPicture(0, 0, 152, 152, gImage_1, BLACK);
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