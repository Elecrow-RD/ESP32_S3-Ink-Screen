#include "EPD.h"

uint8_t oldImage[12480];

/*******************************************************************
    函数说明:判忙函数
    入口参数:无
    说明:忙状态为0  
*******************************************************************/
void EPD_READBUSY(void)
{
  while(EPD_ReadBUSY==0);
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
  delay(20);
  EPD_RES_Set();
  delay(20);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:更新函数
    入口参数:无  
    说明:更新显示内容到E-Paper   
*******************************************************************/
void EPD_Update(void)
{
  EPD_WR_REG(0x04);  //Power ON
  EPD_READBUSY();
  EPD_WR_REG(0x12);
  EPD_READBUSY();
}
/*******************************************************************
    函数说明:局刷初始化函数
    入口参数:无
    说明:E-Paper工作在局刷模式
*******************************************************************/
void EPD_PartInit(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x00);
  EPD_WR_DATA8(0x1B);
  EPD_WR_REG(0xE0);
  EPD_WR_DATA8(0x02);
  EPD_WR_REG(0xE5);
  EPD_WR_DATA8(0x6E);

  //边框白色
  EPD_WR_REG(0x50);
  EPD_WR_DATA8(0xD7);
  EPD_READBUSY();
}
/*******************************************************************
    函数说明:快刷初始化函数
    入口参数:无
    说明:E-Paper工作在快刷模式
*******************************************************************/
void EPD_FastInit(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x00);
  EPD_WR_DATA8(0x1B);
  EPD_WR_REG(0xE0);
  EPD_WR_DATA8(0x02);
  EPD_WR_REG(0xE5);
  EPD_WR_DATA8(0x5F);

    //边框白色
  EPD_WR_REG(0x50);
  EPD_WR_DATA8(0xD7);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:休眠函数
    入口参数:无
    说明:屏幕进入低功耗模式    
*******************************************************************/
void EPD_DeepSleep(void)
{
  EPD_WR_REG(0x02); //Power OFF
  EPD_READBUSY();
  EPD_WR_REG(0x07);
  EPD_WR_DATA8(0xA5);
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
  EPD_WR_REG(0x00);
  EPD_WR_DATA8(0x1B);
}

/*******************************************************************
    函数说明:清屏函数
    入口参数:无
    说明:E-Paper刷白屏
*******************************************************************/
void EPD_Display_Clear(void)
{
  uint16_t i,j,Width,Height;
  Width=(EPD_W%8==0)?(EPD_W/8):(EPD_W/8+1);
  Height=EPD_H; 
  EPD_WR_REG(0x10);
  for (j=0;j<Height;j++) 
  {
    for (i=0;i<Width;i++) 
    {
      EPD_WR_DATA8(oldImage[i+j*Width]);
    }
  }
  EPD_WR_REG(0x13);
  for (j=0;j<Height;j++) 
  {
    for (i=0;i<Width;i++) 
    {
      EPD_WR_DATA8(0xFF);
      oldImage[i+j*Width]=0xFF;
    }
  }

}


/*******************************************************************
    函数说明:数组数据更新到E-Paper
    入口参数:无
    说明:
*******************************************************************/
void EPD_Display(const uint8_t *image)
{
  uint16_t i,j,Width,Height;
  Width=(EPD_W%8==0)?(EPD_W/8):(EPD_W/8+1);
  Height=EPD_H;
  EPD_WR_REG(0x10);
  for (j=0;j<Height;j++) 
  {
    for (i=0;i<Width;i++) 
    {
      EPD_WR_DATA8(oldImage[i+j*Width]);
    }
  }
  EPD_WR_REG(0x13);
  for (j=0;j<Height;j++) 
  {
    for (i=0;i<Width;i++) 
    {
      EPD_WR_DATA8(image[i+j*Width]);
      oldImage[i+j*Width]=image[i+j*Width];
    }
  }

}


