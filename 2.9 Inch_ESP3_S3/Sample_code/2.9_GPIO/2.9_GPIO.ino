#include <Arduino.h>
#include "EPD.h"

extern uint8_t ImageBW[ALLSCREEN_BYTES];
void judgement_function(int* pin)
{
  char buffer[30];

  EPD_GPIOInit();
  clear_all();
  for (int i = 0; i < 12; i++)
  {
    int state = digitalRead(pin[i]);

    if (state == HIGH) {
      // Use sprintf to format the string and output it to buffer
      int length = sprintf(buffer, "GPIO%d : on", pin[i]);
      buffer[length] = '\0';

      if (i < 6)
        EPD_ShowString(0, 0 + i * 20, buffer, BLACK, 16);
      else if (i > 6)
        EPD_ShowString(100, 0 + i % 6 * 20, buffer, BLACK, 16);

    } else {
      // Use sprintf to format the string and output it to buffer
      int length = sprintf(buffer, "GPIO%d : off", pin[i]);
      buffer[length] = '\0';
      if (i < 6)
        EPD_ShowString(0, 0 + i * 20, buffer, BLACK, 16);
      else if (i > 6)
        EPD_ShowString(100, 0 + i % 6 * 20, buffer, BLACK, 16);
    }
  }
  EPD_DisplayImage(ImageBW);
  EPD_FastUpdate();
}

int pin_Num[12] = {8, 3, 14, 9, 16, 15, 18, 17, 20, 19, 38, 21};
void setup() {
  Serial.begin(115200);

  // put your setup code here, to run once:
  // Screen power
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  // GPIO output mode
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(21, OUTPUT);

  // Set GPIO pins to HIGH
  digitalWrite(8, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(20, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(38, HIGH);
  digitalWrite(21, HIGH);

  // Initialize the e-ink display
  EPD_Init();
  EPD_Clear(0, 0, 296, 128, WHITE);
  EPD_ALL_Fill(WHITE);
  EPD_Update();
  EPD_Clear_R26H();
  judgement_function(pin_Num);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
}

void clear_all()
{
  EPD_Init();
  EPD_Clear(0, 0, 296, 128, WHITE);
  EPD_ALL_Fill(WHITE);
  EPD_Update();
  EPD_Clear_R26H();
}