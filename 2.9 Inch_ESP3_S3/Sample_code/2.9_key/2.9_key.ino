#include <Arduino.h>
#include "EPD.h"

extern uint8_t ImageBW[ALLSCREEN_BYTES];
// Home button
#define HOME_KEY 2
int HOME_NUM = 0;

// Exit button
#define EXIT_KEY 1
int EXIT_NUM = 0;
// Carousel switch
// Previous page
#define PRV_KEY 6
int PRV_NUM = 0;
// Next page
#define NEXT_KEY 4
int NEXT_NUM = 0;
// Confirm
#define OK_KEY 5
int OK_NUM = 0;
int NUM_btn[5] = {0};

void clear_all()
{
  EPD_Init();
  EPD_Clear(0, 0, 296, 128, WHITE);
  EPD_ALL_Fill(WHITE);
  EPD_Update();
  EPD_Clear_R26H();
}

void count_btn(int NUM[5])
{
  char buffer[30];

  EPD_GPIOInit();
  clear_all();
  int length = sprintf(buffer, "HOME_KEY_NUM:%d", NUM[0]);
  buffer[length] = '\0';
  EPD_ShowString(0, 0 + 0 * 20, buffer, BLACK, 16);
  memset(buffer, 0, sizeof(buffer));

  length = sprintf(buffer, "EXIT_KEY_NUM:%d", NUM[1]);
  buffer[length] = '\0';
  EPD_ShowString(0, 0 + 1 * 20, buffer, BLACK, 16);
  memset(buffer, 0, sizeof(buffer));

  length = sprintf(buffer, "PRV_KEY_NUM:%d", NUM[2]);
  buffer[length] = '\0';
  EPD_ShowString(0, 0 + 2 * 20, buffer, BLACK, 16);
  memset(buffer, 0, sizeof(buffer));

  length = sprintf(buffer, "NEXT__NUM:%d", NUM[3]);
  buffer[length] = '\0';
  EPD_ShowString(0, 0 + 3 * 20, buffer, BLACK, 16);
  memset(buffer, 0, sizeof(buffer));

  length = sprintf(buffer, "OK_NUM:%d", NUM[4]);
  buffer[length] = '\0';
  EPD_ShowString(0, 0 + 4 * 20, buffer, BLACK, 16);

  EPD_DisplayImage(ImageBW);
  EPD_FastUpdate();
  //    EPD_PartUpdate();
  EPD_Sleep();
}

void setup() {
  Serial.begin(115200);
  // Screen power
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  pinMode(HOME_KEY, INPUT);
  pinMode(EXIT_KEY, INPUT);
  pinMode(PRV_KEY, INPUT);
  pinMode(NEXT_KEY, INPUT);
  pinMode(OK_KEY, INPUT);

  // Initialize the e-ink display
  EPD_Init();
  EPD_Clear(0, 0, 296, 128, WHITE);
  EPD_ALL_Fill(WHITE);
  EPD_Update();
  EPD_Clear_R26H();
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
      HOME_NUM++;
      flag = 1;
    }
  }
  else if (digitalRead(EXIT_KEY) == 0)
  {
    delay(100);
    if (digitalRead(EXIT_KEY) == 1)
    {
      Serial.println("EXIT_KEY");
      EXIT_NUM++;
      flag = 1;
    }
  }
  else if (digitalRead(PRV_KEY) == 0)
  {
    delay(100);
    if (digitalRead(PRV_KEY) == 1)
    {
      Serial.println("PRV_KEY");
      PRV_NUM++;
      flag = 1;
    }
  }
  else if (digitalRead(NEXT_KEY) == 0)
  {
    delay(100);
    if (digitalRead(NEXT_KEY) == 1)
    {
      Serial.println("NEXT_KEY");
      NEXT_NUM++;
      flag = 1;
    }
  }
  else if (digitalRead(OK_KEY) == 0)
  {
    delay(100);
    if (digitalRead(OK_KEY) == 1)
    {
      Serial.println("OK_KEY");
      OK_NUM++;
      flag = 1;
    }
  }
  if (flag == 1)
  {
    NUM_btn[0] = HOME_NUM;
    NUM_btn[1] = EXIT_NUM;
    NUM_btn[2] = PRV_NUM;
    NUM_btn[3] = NEXT_NUM;
    NUM_btn[4] = OK_NUM;

    count_btn(NUM_btn);
    flag = 0;
  }
}