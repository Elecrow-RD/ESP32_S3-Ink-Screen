#include <Arduino.h>      // Include Arduino core library for development on Arduino platform
#include "EPD.h"          // Include EPD library for controlling the electronic ink screen (E-Paper Display)
#include "pic_scenario.h" // Include header file containing image data

extern uint8_t ImageBW[ALLSCREEN_BYTES]; // External declaration of an array ImageBW to store image data

int startX = 0; // Starting horizontal axis
int startY = 0;  // Starting vertical axis
int fontSize = 16; // Font size
int endX = 148;    // End horizontal axis
int endY = 128;    // End vertical axis

const char *My_content_1 = "It boasts a high resolution of 128*296, offering a vivid display effect, and features the classic black and white display, suitable for various application scenarios.";

void setup() {
  // Initialization settings, executed only once when the program starts
  // Initialize screen power
  pinMode(7, OUTPUT);             // Set pin 7 to output mode to control the screen power
  digitalWrite(7, HIGH);          // Set pin 7 to high level to activate the screen power

  EPD_GPIOInit();  // Initialize screen GPIO
  clear_all();     // Clear the screen display
  
  // EPD_Init();                     // Initialize the EPD electronic ink screen to prepare for screen operations
  // EPD_Clear(0, 0, 296, 128, WHITE); // Clear the region from (0,0) to (296,128) on the screen, background color is white
  // EPD_ALL_Fill(WHITE);           // Fill the entire screen with white
  // EPD_Update();                  // Update the screen display content to make the clear and fill operations take effect
  // EPD_Clear_R26H();              // Clear the content in the R26H region, the specific cleared area depends on the screen design

  EPD_HW_RESET();  // Hardware reset the e-paper

  Part_Text_Display(My_content_1, startX, startY, fontSize, BLACK, endX, endY);
 
  EPD_DisplayImage(ImageBW);    // Display the image stored in the ImageBW array
  EPD_FastUpdate();             // Quickly update the screen content to display the image
  // EPD_PartUpdate(); // Commented out code, possibly used to update a portion of the screen
  EPD_Sleep();                  // Set the screen to sleep mode to reduce power consumption

  delay(5000);                  // Wait for 5000 milliseconds (5 seconds), allowing the screen to stay in sleep mode for some time
  clear_all();                  // Call the clear_all function to clear the screen content
}

void loop() {
  // Main loop function, currently does not perform any actions
  // Code that needs to be repeatedly executed can be added here
}

void clear_all() {
  // Function to clear the screen content
  EPD_Init();                  // Initialize the EPD electronic ink screen
  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the region from (0,0) to (296,128) on the screen, background color is white
  EPD_ALL_Fill(WHITE);        // Fill the entire screen with white
  EPD_Update();               // Update the screen display content to make the clear and fill operations take effect
  EPD_Clear_R26H();           // Clear the content in the R26H region
}

/*
*---------Function description: Display text content locally------------
*----Parameter introduction:
      content: Text content
      startX: Starting horizontal axis
      startY: Starting vertical axis
      fontSize: Font size
      color: Font color
      endX: End horizontal axis
      endY: End vertical axis
*/
void Part_Text_Display(const char* content, int startX, int startY, int fontSize, int color, int endX, int endY) {
    int length = strlen(content);
    int i = 0;
    char line[(endX - startX) / (fontSize/2) + 1]; // Calculate the maximum number of characters per line based on the width of the area
    int currentX = startX;
    int currentY = startY;
    int lineHeight = fontSize;

    while (i < length) {
        int lineLength = 0;
        memset(line, 0, sizeof(line));

        // Fill the line until it reaches the width of the region or the end of the string
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