#include <Arduino.h>
#include "EPD.h"
#include "EPD_GUI.h"
#include "pic_scenario.h"
uint8_t ImageBW[12480];
void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  EPD_GPIOInit();
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 180, WHITE);
  Paint_Clear(WHITE); //clear Canvas

  EPD_FastInit();
  EPD_Display_Clear();
  EPD_Update();

  EPD_FastInit();
  EPD_ShowPicture(0, 0, 312, 152, gImage_1, WHITE);
  EPD_Display(ImageBW);
  EPD_Update();
  EPD_DeepSleep();
  delay(5000);
  clear_all();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void clear_all()
{
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE); //clear Canvas
  EPD_FastInit();
  EPD_Display_Clear();
  EPD_Update();  //Before flashing, clear the screen of E-Paper first
}
