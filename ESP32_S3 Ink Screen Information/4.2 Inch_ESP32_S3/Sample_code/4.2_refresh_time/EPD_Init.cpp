#include "EPD_Init.h"
#include "EPD.h"



void EPD_ReadBusy(void)
{
  while (1)
  {
    if (EPD_ReadBUSY == 0)
    {
      break;
    }
  }
}

void EPD_RESET(void)
{
  EPD_RES_Set();
  delay(100);
  EPD_RES_Clr();
  delay(10);
  EPD_RES_Set();
  delay(10);
}

void EPD_Sleep(void)
{
  EPD_WR_REG(0x10);
  EPD_WR_DATA8(0x01);
  delay(50);
}


// void EPD_Update(void)
// {
//   EPD_WR_REG(0x22);
//   EPD_WR_DATA8(0xF7);
//   EPD_WR_REG(0x20);
//   EPD_ReadBusy();
// }

void EPD_Update(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xF7);
  EPD_WR_REG(0x20);
  EPD_ReadBusy();
}

void EPD_Update_Fast(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xC7);
  EPD_WR_REG(0x20);
  EPD_ReadBusy();
}

void EPD_Update_Part(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xFC);
  EPD_WR_REG(0x20);
  EPD_ReadBusy();
}


void EPD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
  EPD_WR_REG(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
  EPD_WR_DATA8((xs >> 3) & 0xFF);
  EPD_WR_DATA8((xe >> 3) & 0xFF);

  EPD_WR_REG(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
  EPD_WR_DATA8(ys & 0xFF);
  EPD_WR_DATA8((ys >> 8) & 0xFF);
  EPD_WR_DATA8(ye & 0xFF);
  EPD_WR_DATA8((ye >> 8) & 0xFF);
}


void EPD_SetCursor(uint16_t xs, uint16_t ys)
{
  EPD_WR_REG(0x4E); // SET_RAM_X_ADDRESS_COUNTER
  EPD_WR_DATA8(xs & 0xFF);

  EPD_WR_REG(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
  EPD_WR_DATA8(ys & 0xFF);
  EPD_WR_DATA8((ys >> 8) & 0xFF);
}


void EPD_Init(void)
{
  EPD_RESET();
  EPD_ReadBusy();
  EPD_WR_REG(0x12);   // soft  reset
  EPD_ReadBusy();

  // EPD_WR_REG(0x21); //  Display update control
  // EPD_WR_DATA8(0x40);
  // EPD_WR_DATA8(0x00);

  EPD_WR_REG(0x3C); //BorderWavefrom
  EPD_WR_DATA8(0x05);
  EPD_WR_REG(0x11); // data  entry  mode
  EPD_WR_DATA8(0x03);   // X-mode
  EPD_Address_Set(0, 0, EPD_W - 1, EPD_H - 1);
  EPD_SetCursor(0, 0);
  EPD_ReadBusy();
}

void EPD_Init_Fast(uint8_t mode)
{
  EPD_RESET();
  EPD_ReadBusy();
  EPD_WR_REG(0x12);   // soft  reset
  EPD_ReadBusy();
  EPD_WR_REG(0x21);
  EPD_WR_DATA8(0x40);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x05);
  if (mode == Fast_Seconds_1_5s)
  {
    EPD_WR_REG(0x1A); // Write to temperature register
    EPD_WR_DATA8(0x6E);
  }
  else if (mode == Fast_Seconds_1_s)
  {
    EPD_WR_REG(0x1A); // Write to temperature register
    EPD_WR_DATA8(0x5A);
  }
  EPD_WR_REG(0x22); // Load temperature value
  EPD_WR_DATA8(0x91);
  EPD_WR_REG(0x20);
  EPD_ReadBusy();
  EPD_WR_REG(0x11); // data  entry  mode
  EPD_WR_DATA8(0x03);   // X-mode
  EPD_Address_Set(0, 0, EPD_W - 1, EPD_H - 1);
  EPD_SetCursor(0, 0);
  EPD_ReadBusy();
}


// void EPD_Clear(void)
// {
//   uint16_t i, j, Width, Height;
//   Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
//   Height = EPD_H;
//   EPD_Init();
//   EPD_WR_REG(0x24);
//   for (j = 0; j < Height; j++)
//   {
//     for (i = 0; i < Width; i++)
//     {
//       EPD_WR_DATA8(0xFF);
//     }
//   }

//   EPD_WR_REG(0x26);
//   for (j = 0; j < Height; j++)
//   {
//     for (i = 0; i < Width; i++)
//     {
//       EPD_WR_DATA8(0xFF);
//     }
//   }
//     EPD_Update();
// //  EPD_Update_Fast();
// //  EPD_Update_Part();
// }
void EPD_Clear(void)
{
  uint16_t i, j, Width, Height;
  Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
  Height = EPD_H;
  EPD_WR_REG(0x24);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }
  EPD_WR_REG(0x26);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(0x00);
    }
  }
}

void EPD_Clear_R26H(const uint8_t *Image)
{

  uint16_t i, j, Width, Height;
  Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
  Height = EPD_H;
  EPD_WR_REG(0x26);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(Image[i + j * Width]);
    }
  }
  EPD_ReadBusy();
}

void EPD_Clear_R26A6H(void)
{

  uint16_t i, j, Width, Height;
  Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
  Height = EPD_H;
  
  EPD_Init();
  EPD_WR_REG(0x26);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }

  EPD_WR_REG(0xA6);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }
}

void EPD_Display(const uint8_t *Image)
{
  uint16_t i, j, Width, Height;
  Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
  Height = EPD_H;
  EPD_WR_REG(0x24);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(Image[i + j * Width]);
    }
  }
  EPD_ReadBusy();
}


void EPD_Display_Fast(const uint8_t *Image)
{
  uint16_t i, j, Width, Height;
  Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
  Height = EPD_H;
  EPD_WR_REG(0x24);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(Image[i + j * Width]);
    }
  }
  EPD_Update_Fast();
}


void EPD_Display_Part(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, const uint8_t *Image)
{
  uint16_t Width, Height, i, j;
  Width = (sizex % 8 == 0) ? (sizex / 8) : (sizex / 8 + 1);
  Height = sizey;
  EPD_WR_REG(0x3C); //BorderWavefrom,
  EPD_WR_DATA8(0x80);
  EPD_WR_REG(0x21);
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x80);
  EPD_Address_Set(x, y, x + sizex - 1, y + sizey - 1);
  EPD_SetCursor(x, y);
  EPD_WR_REG(0x24);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(Image[i + j * Width]);
    }
  }
  EPD_Update_Part();
}

