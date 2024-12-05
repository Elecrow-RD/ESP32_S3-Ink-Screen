#include <Arduino.h>
#include "EPD.h"

extern uint8_t ImageBW[ALLSCREEN_BYTES];
// Home button
#define HOME_KEY 2
int HOME_NUM = 0;

void clear_all()
{
  EPD_Init();
  EPD_Clear(0, 0, 296, 128, WHITE);
  EPD_ALL_Fill(WHITE);
  EPD_Update();
  EPD_Clear_R26H();
}

void setup() {
  // Initialization settings, executed only once
  Serial.begin(115200);
  // Screen power
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  // Power LED
  pinMode(41, OUTPUT);

  pinMode(HOME_KEY, INPUT);
}

void loop() {
  // Main loop code, to run repeatedly
  int flag = 0;
  if (digitalRead(HOME_KEY) == 0)
  {
    delay(100);
    if (digitalRead(HOME_KEY) == 1)
    {
      Serial.println("HOME_KEY");
      HOME_NUM = !HOME_NUM;

      flag = 1;
    }
  }
  if (flag == 1)
  {
    char buffer[30];

    EPD_GPIOInit();
    clear_all();
    if (HOME_NUM == 1)
    {
      digitalWrite(41, HIGH);
      strcpy(buffer, "PWR:on");
    } else
    {
      digitalWrite(41, LOW);
      strcpy(buffer, "PWR:off");
    }
    EPD_ShowString(0, 0 + 0 * 20, buffer, BLACK, 16);
    EPD_DisplayImage(ImageBW);
    EPD_FastUpdate();
    //    EPD_PartUpdate();
    EPD_Sleep();
  }
}