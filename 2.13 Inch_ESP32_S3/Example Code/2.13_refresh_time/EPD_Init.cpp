#include "EPD_Init.h"

/**
   @brief       EPD读忙
   @param       无
   @retval      无
   @note        BUSY 高电平为忙状态 低电平为空闲状态
*/
void EPD_READBUSY(void)
{
  while (1)
  {
    if (EPD_ReadBUSY == 0)
    {
      break;
    }
  }
  delayMicroseconds(100);
}

/**
   @brief       EPD软硬件复位
   @param       无
   @retval      无
   @note        退出休眠时需要进行一次硬件复位
*/
void EPD_HW_SW_RESET(void)
{
  delay(100);
  EPD_RES_Set();
  delay(10);
  EPD_RES_Clr();
  delay(10);
  EPD_RES_Set();
  delay(10);
  EPD_READBUSY();   /* 检测是否完成硬件复位 */
  EPD_WR_REG(0x12); /* 软件复位指令 具体参考SSD1680 datasheet */
  EPD_READBUSY();   /* 检测是否完成软件复位 */
}

/**
   @brief       EPD进入休眠模式
   @param       无
   @retval      无
   @note        不同休眠模式下功耗不同 默认配置模式1 保留RAM数据
*/
void EPD_Sleep(void)
{
  EPD_WR_REG(0x10); /* 休眠指令 具体参考SSD1680 datasheet */
  EPD_WR_DATA8(0x01);

  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x01);
  delay(20);
}

/**
****************************************************************************
  此处简单对R22h做简单介绍，方便理解R22h的参数配置
  R22h寄存器可配置位为A7 A6 A5 A4 A3 A2 A1 A0;其功能如下
  A7 Enable internal clock oscillator                  使能内部时钟振荡器
  A6 Turn-on DC-Dc boost                               启动DC-DC升压
  A5 Read the temperature sensor                       读取温度传感器
  A4 Search and load the LUT from OTP                  搜索并从OTP加载LUT
  A3 Perform 0=DISPLAY Mode 1 1=DISPLAY Mode 2         控制EPD的显示模式
  A2 Perform image display (content in RAM)sequence    执行RAM中的图像显示
  A1 Turn-off DC-DC boost                              关闭DC-DC升压
  A0 Disable the internal clock oscillator             失能内部时钟振荡器
  关于温度传感器说明：EPD是通过内置的温度传感器进行相应的LUT加载 从而实现不
  同的显示模式如本工程中的快刷模式就是如此 通过给定温度系数 执行相应的刷新
  关于显示模式；模式1 模式2可以理解为全刷 局刷模式
****************************************************************************
*/

/**
   @brief       EPD全刷模式更新显示
   @param       无
   @retval      无
*/
void EPD_Update(void)
{
  EPD_WR_REG(0x22); /* 显示模式控制指令 具体参考SSD1680 datasheet */
  /* 更新显示之前 开时钟 开DC-DC 开始读取环温 加载LUT 工作在全刷模式 执行图像刷新 保持DC-DC 时钟开启*/
  EPD_WR_DATA8(0xF4);
  EPD_WR_REG(0x20); /* 激活指令 具体参考SSD1680 datasheet */
  EPD_READBUSY();
}

//Fast refresh 1 update function
void EPD_Update_Fast(void)
{   
  EPD_WR_REG(0x22); //Display Update Control
  EPD_WR_DATA8(0xC7);   
  EPD_WR_REG(0x20); //Activate Display Update Sequence
  EPD_READBUSY();   
}

/**
   @brief       EPD局刷模式更新显示
   @param       无
   @retval      无
*/
void EPD_PartUpdate(void)
{
  EPD_WR_REG(0x22);  /* 显示模式控制指令 具体参考SSD1680 datasheet */
  /* 如果局刷之前已经开启时钟以及DC-DC并且没有关闭的话那么这里我们就无需再次开启否则必须开启！！！ */
  /* 开启时钟 开启DC-DC 读取环温 加载LUT 工作在局刷模式 执行图像刷新 保持DC-DC 时钟开启*/
  EPD_WR_DATA8(0xFC); /* 未避免用户对使用流程不熟悉这里默认做开启配置,如前面已经开启此处可以修改为 0x1C*/
  EPD_WR_REG(0x20);
  EPD_READBUSY();

  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x01);
}

/**
************************************************************************
  此处简单对R26h做简单介绍说明
  SSD1680支持驱动 黑白EPD 黑白红EPD;
  驱动黑白EPD的时候 26H寄存器可以理解为存储的上 一帧的数据内容
  为了保证局刷模式可以达到理想的刷新效果需要擦除R26H寄存器的内容
  驱动黑白红EPD的时候 26H寄存器存储的为红色图像数据
************************************************************************
*/
/**
   @brief       EPD擦除26H寄存器
   @param       无
   @retval      无
*/
void EPD_Clear_R26H(void)
{
  uint32_t i;
  EPD_WR_REG(0x26); /* 写RAM指令 具体参考SSD1680 datasheet */
  for (i = 0; i < ALLSCREEN_BYTES; i++)
  {
    EPD_WR_DATA8(WHITE);
  }
  EPD_READBUSY();
}

/**
   @brief       EPD全屏颜色填充
   @param       color：填充颜色值
   @retval      无
*/
void EPD_ALL_Fill(uint8_t color)
{
  uint32_t i;
  EPD_WR_REG(0x3C);/* 边界波形控制指令 具体参考SSD1680 datasheet */
  if (color)
  {
    EPD_WR_DATA8(0x01);
  }
  else
  {
    EPD_WR_DATA8(0x00);
  }
  EPD_WR_REG(0x24); /* 写RAM指令 具体参考SSD1680 datasheet */
  for (i = 0; i < ALLSCREEN_BYTES; i++)
  {
    EPD_WR_DATA8(color);
  }
  EPD_READBUSY();
}

/**
   @brief       EPD全屏显示图像
   @param       ImageBW：图像数组名
   @retval      无
*/
void EPD_DisplayImage(const uint8_t *ImageBW)
{
  uint32_t i;
  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x01);
  EPD_WR_REG(0x24);
  for (i = 0; i < ALLSCREEN_BYTES; i++)
  {
    EPD_WR_DATA8(~ImageBW[i]);
  }
}

void EPD_Init(void)
{
  EPD_GPIOInit();
  EPD_HW_SW_RESET();

  EPD_WR_REG(0x01);    /* 配置驱动器输出控制 */
  EPD_WR_DATA8(0xF9); /* 配置MUX线设置 */
  EPD_WR_DATA8(0x00); /* 配置MUX线设置 */
  EPD_WR_DATA8(0x00); /* 配置EPD扫描方式 */

  EPD_WR_REG(0x11); /* 配置数据输入模式同时配置写入RAM按照逐行式写入 */
  EPD_WR_DATA8(0x03);

  EPD_WR_REG(0x44); /* 配置RAM起始X地址 以及Y地址 */
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x0F);

  EPD_WR_REG(0x45);
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0xF9);
  EPD_WR_DATA8(0x00);

  EPD_WR_REG(0x3C);   /* 配置边框线颜色 */
  EPD_WR_DATA8(0x01); // 0x01->0x05
  EPD_READBUSY();

  EPD_WR_REG(0x18); /* 配置为内部温度传感器 */
  EPD_WR_DATA8(0x80);

  //    EPD_WR_REG(0x22);
  //    EPD_WR_DATA8(0xF4);
  //    EPD_WR_REG(0x20);
  //    EPD_READBUSY();

  EPD_WR_REG(0x4E);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x4F);
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x00);

  //    EPD_WR_REG(0x0C);            /* 配置Booster启动时间 */

  EPD_READBUSY();

//  EPD_WR_REG(0x3C);
//  EPD_WR_DATA8(0x3);
//  EPD_READBUSY();
}

//Fast refresh 1 initialization
void EPD_HW_Init_Fast(void)
{
  EPD_RES_Clr();  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_RES_Set();
  delay(10); //At least 10ms delay 
  
  EPD_WR_REG(0x12);  //SWRESET
  EPD_READBUSY();   
  
  EPD_WR_REG(0x18); //Read built-in temperature sensor
  EPD_WR_DATA8(0x80);  
      
  EPD_WR_REG(0x22); // Load temperature value
  EPD_WR_DATA8(0xB1);    
  EPD_WR_REG(0x20); 
  EPD_READBUSY();   

  EPD_WR_REG(0x1A); // Write to temperature register
  EPD_WR_DATA8(0x64);    
  EPD_WR_DATA8(0x00);  
            
  EPD_WR_REG(0x22); // Load temperature value
  EPD_WR_DATA8(0x91);    
  EPD_WR_REG(0x20); 
  EPD_READBUSY();   
}
