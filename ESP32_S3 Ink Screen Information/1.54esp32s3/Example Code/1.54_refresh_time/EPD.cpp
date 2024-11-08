#include "EPD.h"



/*******************************************************************
    函数说明:判忙函数
    入口参数:无
    说明:忙状态为1
*******************************************************************/
void EPD_READBUSY(void)
{
  while (1)
  {
    if (EPD_ReadBusy == 0)
    {
      break;
    }
  }
}

/*******************************************************************
    函数说明:硬件复位函数
    入口参数:无
    说明:在E-Paper进入Deepsleep状态后需要硬件复位
*******************************************************************/
void EPD_HW_RESET(void)
{
  delay(100);
  EPD_RES_Clr();
  delay(10);
  EPD_RES_Set();
  delay(10);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:更新函数
    入口参数:无
    说明:更新显示内容到E-Paper
*******************************************************************/
void EPD_Update(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xF4);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}
/*******************************************************************
    函数说明:局刷更新函数
    入口参数:无
    说明:E-Paper工作在局刷模式
*******************************************************************/
void EPD_PartUpdate(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xDC);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}
/*******************************************************************
    函数说明:快刷更新函数
    入口参数:无
    说明:E-Paper工作在快刷模式
*******************************************************************/
void EPD_FastUpdate(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xC7);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:休眠函数
    入口参数:无
    说明:屏幕进入低功耗模式
*******************************************************************/
void EPD_DeepSleep(void)
{
  EPD_WR_REG(0x10);
  EPD_WR_DATA8(0x01);
  delay(20);

//  EPD_WR_REG(0x3C);
//  EPD_WR_DATA8(0x3);
}

/*******************************************************************
    函数说明:初始化函数
    入口参数:无
    说明:调整E-Paper默认显示方向
*******************************************************************/
void EPD_Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12);  //SWRESET
  EPD_READBUSY();
  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x01);
}

/*******************************************************************
    函数说明:快刷初始化函数
    入口参数:无
    说明:E-Paper工作在快刷模式1
*******************************************************************/
void EPD_FastMode1Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12);
  EPD_READBUSY();
  EPD_WR_REG(0x18);
  EPD_WR_DATA8(0x80);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xB1);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
  EPD_WR_REG(0x1A);
  EPD_WR_DATA8(0x64);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0x91);
  EPD_WR_REG(0x20);
  EPD_READBUSY();


}
/*******************************************************************
    函数说明:快刷初始化函数
    入口参数:无
    说明:E-Paper工作在快刷模式2
*******************************************************************/
void EPD_FastMode2Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12);
  EPD_READBUSY();
  EPD_WR_REG(0x18);
  EPD_WR_DATA8(0x80);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xB1);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
  EPD_WR_REG(0x1A);
  EPD_WR_DATA8(0x5A);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0x91);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:清屏函数
    入口参数:无
    说明:E-Paper刷白屏
*******************************************************************/
void EPD_Display_Clear(void)
{
  uint16_t i;
  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x05);
  EPD_WR_REG(0x24);
  for (i = 0; i < 2888; i++)
  {
    EPD_WR_DATA8(0xFF);
  }
  EPD_READBUSY();
  EPD_WR_REG(0x26);
  for (i = 0; i < 2888; i++)
  {
    EPD_WR_DATA8(0x00);
  }
}

/*******************************************************************
    函数说明:局刷擦除旧数据
    入口参数:无
    说明:E-Paper工作在局刷模式下调用
*******************************************************************/
void EPD_Clear_R26H(void)
{
  uint16_t i;
  EPD_READBUSY();
  EPD_WR_REG(0x26);
  for (i = 0; i < 2888; i++)
  {
    EPD_WR_DATA8(0xFF);
  }
}

/*******************************************************************
    函数说明:数组数据更新到E-Paper
    入口参数:无
    说明:
*******************************************************************/
void EPD_Display(uint8_t *image)
{
  uint16_t i, j, Width, Height;
  Width = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
  Height = EPD_H;
  EPD_WR_REG(0x24);
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      EPD_WR_DATA8(image[i + j * Width]);
    }
  }
}
