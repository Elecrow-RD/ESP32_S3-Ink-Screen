#include <Arduino.h>         // Introduce Arduino core library to provide basic Arduino functions
#include "EPD.h"             // Introduce EPD library for controlling electronic ink screens（E-Paper Display）
#include "pic_scenario.h"     // Introduce header files containing image data

uint8_t ImageBW[27200];      // Declare an array with a size of 27200 bytes for storing black and white image data


int startX = 100; //Starting horizontal axis
int startY = 50;  //Starting ordinate
int fontSize = 24; // font size
int endX = 500;    // End horizontal axis
int endY = 200;    // End vertical axis

const char *My_content_1 = "It boasts a high resolution of 272*792, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.";
char *My_content_2 = "This CrowPanel ESP32 5.79 HMI";

void setup() {
 // Initialize settings, executed once at program startup

  // Configure screen power pins
  pinMode(7, OUTPUT);         // Set pin 7 to output mode
  digitalWrite(7, HIGH);     // Set pin 7 to high level to activate the screen power supply

  EPD_GPIOInit();          // Initialize GPIO pin configuration for EPD e-ink screen
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); // Create a new image buffer with a size of EPD_W x EPD_H and a white background color
  Paint_Clear(WHITE);       // Clear the image buffer and fill it with white

 /************************Quick screen cleaning works in local flashing mode************************/
  EPD_FastMode1Init();       // Initialize EPD screen in Quick Mode 1
  EPD_Display_Clear();       // Clear screen content
  EPD_Update();              // Update screen display

  EPD_HW_RESET();           // Perform hardware reset operation to ensure the screen starts up normally

  // EPD_ShowChar(0, 190, 'h', 24, WHITE);
  // EPD_ShowChar(12, 190, 'e', 24, WHITE);
  // EPD_ShowChar(24, 190, 'l', 24, WHITE);
  // EPD_ShowChar(36, 190, 'l', 24, WHITE);
  // EPD_ShowChar(48, 190, 'o', 24, WHITE);//Introduce ShowChar function

  // EPD_ShowString(0, 0, My_content_2, 48, BLACK);
  // EPD_ShowString(0, 48, My_content_2, 24, BLACK);
  // EPD_ShowString(0, 72, My_content_2, 16, BLACK);
  // EPD_ShowString(0, 88, My_content_2, 12, BLACK);//Introduce font size

  Part_Text_Display(My_content_1, startX, startY, fontSize, BLACK, endX, endY);//局部显示文本

  EPD_Display(ImageBW);     // Display images stored in the ImageBW array
  EPD_PartUpdate();         // Update a portion of the screen to display new content
  EPD_DeepSleep();         //Set the screen to deep sleep mode to save power

  //delay(5000);             // Wait for 5000 milliseconds (5 seconds)

 // clear_all();            // Call the clear_all function to clear the screen content
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
        EPD_ShowString(currentX, currentY, line, fontSize, color); 

        // Update the Y coordinate for displaying the next line
        currentY += lineHeight;

        // If there are still remaining strings but they have reached the bottom of the area, stop displaying them
        if (currentY + lineHeight > endY) {
            break;
        }
    }
}

