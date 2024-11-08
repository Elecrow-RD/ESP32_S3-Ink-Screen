#include <Arduino.h>         // Introduce Arduino core library to provide basic Arduino functions
#include "EPD.h"             // Introduce EPD library for controlling electronic ink screens（E-Paper Display）
#include "pic_home.h"        // Introduce header files containing image data

#define Max_CharNum_PerLine 66//---792/12

uint8_t ImageBW[27200];    // Declare an array with a size of 27200 bytes for storing black and white image data
char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.Support multiple development environments (Arduino IDE, ESP IDF, MicroPython), suitable for different people's needs, simplifying the secondary development process.Due to its excellent characteristics such as low power consumption, high contrast, and high reflectivity, this electronic paper screen is widely applicable to shelf tags, price tags, badges, smart tags, smart home devices, e-readers, smart wearable devices, and other portable devices, making it an ideal choice for various smart devices and applications.";
//char *My_content_2 = "Due to its excellent characteristics such as low power consumption, high contrast, and high reflectivity, this electronic paper screen is widely applicable to shelf tags, price tags, badges, smart tags, smart home devices, e-readers, smart wearable devices, and other portable devices, making it an ideal choice for various smart devices and applications.";


void setup() {
 // Initialize settings, executed once at program startup

  // Configure screen power pins
  pinMode(7, OUTPUT);         // Set pin 7 to output mode
  digitalWrite(7, HIGH);     // Set pin 7 to high level to activate the screen power supply

  EPD_GPIOInit();            // Initialize GPIO pin configuration for EPD e-ink screen
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); // Create a new image buffer with a size of EPD_W x EPD_H and a white background color
  Paint_Clear(WHITE);       // Clear the image buffer and fill it with white

 /************************Quick screen cleaning works in local flashing mode************************/
  EPD_FastMode1Init();       // Initialize EPD screen in Quick Mode 1
  EPD_Display_Clear();       // Clear screen content
  EPD_Update();              // Update screen display

  EPD_GPIOInit();           //Initialize the GPIO pin configuration of the EPD e-ink screen again
  EPD_FastMode1Init();       //Reinitialize the EPD screen in Quick Mode 1

  Long_Text_Display(0, 0, My_content_1, 24, BLACK);
  //Long_Text_Display(0, 120, My_content_2, 24, BLACK);

  EPD_Display(ImageBW);      //Display images stored in the ImageBW array
  //  EPD_WhiteScreen_ALL_Fast(gImage_boot_setup); //Annotated code: Display boot settings image using quick mode
  //  EPD_PartUpdate();       //Annotated code: Updating a part of the screen
  EPD_FastUpdate();          //Perform quick updates to refresh the screen
  EPD_DeepSleep();          //Set the screen to deep sleep mode to save power
  //delay(5000);              //Wait for 5000 milliseconds (5 seconds)

  //clear_all();             //Call the clear_all function to clear the screen content
}

void loop() {
 //Main loop function, currently not performing any operation
//You can add code that needs to be executed repeatedly in this function
}

void clear_all()
{
  // Function to clear screen content
  EPD_FastMode1Init();     // Initialize EPD screen in Quick Mode 1
  EPD_Display_Clear();     // Clear screen content
  EPD_Update();            // Update screen display
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

        EPD_ShowString(x, y, line, fontSize, color);//Display this line
        y += fontSize; //Update the y-coordinate for displaying the next line

      //If there are still remaining strings and the next line exceeds the screen height, stop displaying
      //You need to decide when to stop displaying based on your screen height here
      //For example, if your screen height is 272 pixels and the height of each character is 24 pixels, then you can display 11行
        if (y >= 272) {
            break;
        }
    }
}

