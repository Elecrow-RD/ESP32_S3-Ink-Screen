#include "EPD.h"
#include "EPDfont.h"
#include "string.h"

uint8_t ImageBW[ALLSCREEN_BYTES];

/**
 * @brief       在EPD上画一个点
 * @param       x:像素点列坐标
 * @param       y:像素点行坐标
 * @param       color:填充颜色值
 * @retval      无
 */
void EPD_DrawPoint(uint16_t x, uint16_t y, uint8_t color)
{
    uint8_t dat = 0;
    uint16_t xpoint, ypoint;
    uint32_t Addr;
    switch (USE_HORIZONTIAL)
    {
    case 0:
        xpoint = EPD_H - y - 1;
        ypoint = x;
        break;
    case 1:
        xpoint = x;
        ypoint = y;
        break;
    case 2:
        xpoint = y;
        ypoint = EPD_W - x - 1;
        break;
    case 3:
        xpoint = EPD_W - x - 1;
        ypoint = EPD_H - y - 1;
        break;
    default:
        return;
    }
#if USE_HORIZONTIAL == 0 | USE_HORIZONTIAL == 2
    Addr = xpoint / 8 + ypoint * ((EPD_H % 8 == 0) ? (EPD_H / 8) : (EPD_H / 8 + 1));
#else
    Addr = xpoint / 8 + ypoint * ((EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1));
#endif
    dat = ImageBW[Addr];
    if (color == BLACK)
    {
        ImageBW[Addr] = dat | (0x80 >> (xpoint % 8));
    }
    else
    {
        ImageBW[Addr] = dat & ~(0x80 >> (xpoint % 8));
    }
}

/**
 * @brief       填充缓存函数
 * @param       xs:填充位置的起始列坐标
 * @param       ys:填充位置的起始行坐标
 * @param       xe:填充位置的结束列坐标
 * @param       ye:填充位置的结束行坐标
 * @param       color:填充位置的颜色值
 * @retval      无
 */
void EPD_Clear(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color)
{
    uint16_t x, y;
    uint32_t Addr;
    for (y = ys; y < ye; y++)
    {
        for (x = xs; x < xe; x++)
        {
            EPD_DrawPoint(x, y, color);
        }
    }
}

/**
 * @brief       两点之间画线函数
 * @param       xs:画线的起始列坐标
 * @param       ys:画线的起始行坐标
 * @param       xe:画线的结束列坐标
 * @param       ye:画线的结束行坐标
 * @param       color:画线的颜色值
 * @retval      无
 */
void EPD_DrawLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = xe - xs; // 计算坐标增量
    delta_y = ye - ys;
    uRow = xs;
    uCol = ys;
    if (delta_x > 0)
    {
        incx = 1; // 设置单步方向
    }
    else if (delta_x == 0)
    {
        incx = 0; // 垂直线
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0; // 水平线
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
    {
        distance = delta_x; // 选取基本增量坐标轴
    }
    else
    {
        distance = delta_y;
    }
    for (t = 0; t <= distance + 1; t++) // 画线输出
    {
        EPD_DrawPoint(uRow, uCol, color); // 画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
 * @brief       绘制空心矩形函数
 * @param       xs:矩形的起始列坐标
 * @param       ys:矩形的起始行坐标
 * @param       xe:矩形的结束列坐标
 * @param       ye:矩形的结束行坐标
 * @param       color:矩形的颜色值
 * @retval      无
 */
void EPD_DrawRectangle(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color)
{
    EPD_DrawLine(xs, ys, xe, ys, color);
    EPD_DrawLine(xs, ys, xs, ye, color);
    EPD_DrawLine(xs, ye, xe, ye, color);
    EPD_DrawLine(xe, ys, xe, ye, color);
}

/**
 * @brief       8分法绘制圆形(内部调用)
 * @param       xc:圆心列坐标
 * @param       yc:圆心行坐标
 * @param       x:相对于圆心的列坐标
 * @param       y:相对于圆心的行坐标
 * @param       color:圆形的颜色值
 * @retval      无
 */
void Draw_Circle(int xc, int yc, int x, int y, uint8_t color)
{
    EPD_DrawPoint(xc + x, yc + y, color);
    EPD_DrawPoint(xc - x, yc + y, color);
    EPD_DrawPoint(xc + x, yc - y, color);
    EPD_DrawPoint(xc - x, yc - y, color);
    EPD_DrawPoint(xc + y, yc + x, color);
    EPD_DrawPoint(xc - y, yc + x, color);
    EPD_DrawPoint(xc + y, yc - x, color);
    EPD_DrawPoint(xc - y, yc - x, color);
}

/**
 * @brief       绘制圆形
 * @param       xc:圆心列坐标
 * @param       yc:圆心行坐标
 * @param       r:圆形半径
 * @param       color:圆形的颜色值
 * @param       mode:是否填充圆形
 * @retval      无
 */
void EPD_DrawCircle(uint16_t xc, uint16_t yc, uint16_t r, uint8_t color, uint16_t mode)
{
    int x = 0, y = r, yi, d;
    d = 3 - 2 * r;
    /*绘制实心圆*/
    if (mode)
    {
        while (x <= y)
        {
            for (yi = x; yi <= y; yi++)
            {
                Draw_Circle(xc, yc, x, yi, color);
            }
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    /*绘制空心圆*/
    else
    {
        while (x <= y)
        {
            Draw_Circle(xc, yc, x, y, color);
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

/**
 * @brief       绘制空心三角形
 * @param       x:三角形坐标列起始坐标
 * @param       y:三角形坐标行起始坐标
 * @param       xs:三角形顶点列坐标
 * @param       ys:三角形顶点行坐标
 * @param       xe:三角形末端列坐标
 * @param       ye:三角形末端行坐标
 * @param       color:三角形的颜色值
 * @retval      无
 */
void EPD_DrawTriangel(uint16_t x, uint16_t y, uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint8_t color)
{
    EPD_DrawLine(x, y, xs, ys, color);
    EPD_DrawLine(xs, ys, xe, ye, color);
    EPD_DrawLine(xe, ye, x, y, color);
}

/**
 * @brief       显示单个字符
 * @param       x:字符显示位置列起始坐标
 * @param       y:字符显示位置行起始坐标
 * @param       num:显示字符的ASCII码
 * @param       color:字符颜色
 * @param       sizey:字符大小
 * @retval      无
 */
void EPD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t color, uint8_t sizey)
{
    uint8_t temp, sizex, t;
    uint16_t i, TypefaceNum; // 一个字符所占字节大小
    uint16_t x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    num = num - ' '; // 得到偏移后的值
    for (i = 0; i < TypefaceNum; i++)
    {
        if (sizey == 12)
            temp = ascii_1206[num][i]; // 调用6x12字体
        else if (sizey == 16)
            temp = ascii_1608[num][i]; // 调用8x16字体
        else if (sizey == 24)
            temp = ascii_2412[num][i]; // 调用12x24字体
        else if (sizey == 32)
            temp = ascii_3216[num][i]; // 调用16x32字体
        else if (sizey == 48)
            temp = ascii_4824[num][i]; // 调用24x48字体
        else
            return;
        for (t = 0; t < 8; t++)
        {
            if (temp & (0x01 << t))
            {
                EPD_DrawPoint(x, y, color); // 画一个点
            }
            else
            {
                EPD_DrawPoint(x, y, !color);
            }
            x++;
            if ((x - x0) == sizex)
            {
                x = x0;
                y++;
                break;
            }
        }
    }
}

/**
 * @brief       显示字符串
 * @param       x:字符串显示位置列起始坐标
 * @param       y:字符串显示位置行起始坐标
 * @param       *s:显示的字符串内容
 * @param       color:字符颜色
 * @param       sizey:字符大小
 * @retval      无
 */
void EPD_ShowString(uint16_t x, uint16_t y, const char *s, uint8_t color, uint16_t sizey)
{
    while ((*s <= '~') && (*s >= ' ')) // 判断是不是非法字符
    {
        if (x > (EPD_W - 1) || y > (EPD_H - 1))
            return;
        EPD_ShowChar(x, y, *s, color, sizey);
        x += sizey / 2;
        s++;
    }
}

/**
 * @brief       幂运算(内部调用)
 * @param       m:底数
 * @param       n:指数
 * @retval      result:m的n次幂
 */
uint32_t mypow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

/**
 * @brief       显示数字
 * @param       x:数字显示位置列起始坐标
 * @param       y:数字显示位置行起始坐标
 * @param       num:显示的数字(0~4294967295)
 * @param       len:显示数字的位数
 * @param       color:字符颜色
 * @param       sizey:字符大小
 * @retval      无
 */
void EPD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t color, uint8_t sizey)
{
    uint8_t t, temp, enshow = 0;
    uint8_t sizex = sizey / 2;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                EPD_ShowChar(x + t * sizex, y, ' ', color, sizey);
                continue;
            }
            else
            {
                enshow = 1;
            }
        }
        EPD_ShowChar(x + t * sizex, y, temp + '0', color, sizey);
    }
}

/**
 * @brief       显示浮点数
 * @param       x:数字显示位置列起始坐标
 * @param       y:数字显示位置行起始坐标
 * @param       num:显示的浮点数
 * @param       pre:显示浮点数精度
 * @param       len:显示浮点数的位数(不包含小数点)
 * @param       color:字符颜色
 * @param       sizey:字符大小
 * @retval      无
 */
void EPD_ShowFloatNum(uint16_t x, uint16_t y, float num, uint8_t pre, uint8_t len, uint8_t color, uint8_t sizey)
{
    uint32_t i, temp, num1;
    uint8_t sizex = sizey / 2;
    num1 = num * mypow(10, pre);
    for (i = 0; i < len; i++)
    {
        temp = (num1 / mypow(10, len - i - 1)) % 10;
        if (i == (len - pre))
        {
            EPD_ShowChar(x + (len - pre) * sizex, y, '.', color, sizey);
            i++;
            len += 1;
        }
        EPD_ShowChar(x + i * sizex, y, temp + '0', color, sizey);
    }
}

///**
// * @brief       显示12x12汉字
// * @param       x:汉字显示位置列起始坐标
// * @param       y:汉字显示位置行起始坐标
// * @param       *s:显示中文字符起始地址
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_ShowChinese12x12(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    uint8_t i, j;
//    uint16_t k, HZnum;    // 汉字数目
//    uint16_t TypefaceNum; // 一个字符所占字节大小
//    uint16_t x0 = x;
//    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
//    HZnum = sizeof(tfont12) / sizeof(typFONT_GB12); // 统计汉字数目
//    for (k = 0; k < HZnum; k++)
//    {
//        if ((tfont12[k].Index[0] == *(s)) && (tfont12[k].Index[1] == *(s + 1)))
//        {
//            for (i = 0; i < TypefaceNum; i++)
//            {
//                for (j = 0; j < 8; j++)
//                {
//                    if (tfont12[k].Msk[i] & (0x01 << j))
//                    {
//                        EPD_DrawPoint(x, y, color); // 画一个点
//                    }
//                    else
//                    {
//                        EPD_DrawPoint(x, y, !color);
//                    }
//                    x++;
//                    if ((x - x0) == sizey)
//                    {
//                        x = x0;
//                        y++;
//                        break;
//                    }
//                }
//            }
//        }
//        continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//    }
//}
//
///**
// * @brief       显示16x16汉字
// * @param       x:汉字显示位置列起始坐标
// * @param       y:汉字显示位置行起始坐标
// * @param       *s:显示中文字符起始地址
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_ShowChinese16x16(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    uint8_t i, j;
//    uint16_t k, HZnum;    // 汉字数目
//    uint16_t TypefaceNum; // 一个字符所占字节大小
//    uint16_t x0 = x;
//    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
//    HZnum = sizeof(tfont16) / sizeof(typFONT_GB16); // 统计汉字数目
//    for (k = 0; k < HZnum; k++)
//    {
//        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
//        {
//            for (i = 0; i < TypefaceNum; i++)
//            {
//                for (j = 0; j < 8; j++)
//                {
//                    if (tfont16[k].Msk[i] & (0x01 << j))
//                    {
//                        EPD_DrawPoint(x, y, color); // 画一个点
//                    }
//                    else
//                    {
//                        EPD_DrawPoint(x, y, !color);
//                    }
//                    x++;
//                    if ((x - x0) == sizey)
//                    {
//                        x = x0;
//                        y++;
//                        break;
//                    }
//                }
//            }
//        }
//        continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//    }
//}
//
///**
// * @brief       显示24x24汉字
// * @param       x:汉字显示位置列起始坐标
// * @param       y:汉字显示位置行起始坐标
// * @param       *s:显示中文字符起始地址
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_ShowChinese24x24(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    uint8_t i, j;
//    uint16_t k, HZnum;    // 汉字数目
//    uint16_t TypefaceNum; // 一个字符所占字节大小
//    uint16_t x0 = x;
//    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
//    HZnum = sizeof(tfont24) / sizeof(typFONT_GB24); // 统计汉字数目
//    for (k = 0; k < HZnum; k++)
//    {
//        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
//        {
//            for (i = 0; i < TypefaceNum; i++)
//            {
//                for (j = 0; j < 8; j++)
//                {
//                    if (tfont24[k].Msk[i] & (0x01 << j))
//                    {
//                        EPD_DrawPoint(x, y, color); // 画一个点
//                    }
//                    else
//                    {
//                        EPD_DrawPoint(x, y, !color);
//                    }
//                    x++;
//                    if ((x - x0) == sizey)
//                    {
//                        x = x0;
//                        y++;
//                        break;
//                    }
//                }
//            }
//        }
//        continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//    }
//}
//
///**
// * @brief       显示32x32汉字
// * @param       x:汉字显示位置列起始坐标
// * @param       y:汉字显示位置行起始坐标
// * @param       *s:显示中文字符起始地址
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_ShowChinese32x32(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    uint8_t i, j;
//    uint16_t k, HZnum;    // 汉字数目
//    uint16_t TypefaceNum; // 一个字符所占字节大小
//    uint16_t x0 = x;
//    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
//    HZnum = sizeof(tfont32) / sizeof(typFONT_GB32); // 统计汉字数目
//    for (k = 0; k < HZnum; k++)
//    {
//        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
//        {
//            for (i = 0; i < TypefaceNum; i++)
//            {
//                for (j = 0; j < 8; j++)
//                {
//
//                    if (tfont32[k].Msk[i] & (0x01 << j))
//                    {
//                        EPD_DrawPoint(x, y, color); // 画一个点
//                    }
//                    else
//                    {
//                        EPD_DrawPoint(x, y, !color);
//                    }
//                    x++;
//                    if ((x - x0) == sizey)
//                    {
//                        x = x0;
//                        y++;
//                        break;
//                    }
//                }
//            }
//        }
//        continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//    }
//}
//
///**
// * @brief       显示汉字串
// * @param       x:汉字显示位置列起始坐标
// * @param       y:汉字显示位置行起始坐标
// * @param       *s:显示中文字符
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_ShowChinese(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    while (*s != 0)
//    {
//        if (sizey == 12)
//            EPD_ShowChinese12x12(x, y, s, color, sizey);
//        else if (sizey == 16)
//            EPD_ShowChinese16x16(x, y, s, color, sizey);
//        else if (sizey == 24)
//            EPD_ShowChinese24x24(x, y, s, color, sizey);
//        else if (sizey == 32)
//            EPD_ShowChinese32x32(x, y, s, color, sizey);
//        else
//            return;
//        s += 2;
//        x += sizey;
//    }
//}
//
///**
// * @brief       中英字符混显
// * @param       x:显示位置列起始坐标
// * @param       y:显示位置行起始坐标
// * @param       *s:显示字符起始地址
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_ShowStr(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    uint16_t x0 = x;
//    uint8_t bHz = 0; // 字符或者中文
//    while (*s != 0)  // 数据未结束
//    {
//        if (!bHz) // 英文
//        {
//            if (x > (EPD_W - sizey / 2) || y > (EPD_H - sizey))
//            {
//                return;
//            }
//            if (*s > 0x80)
//            {
//                bHz = 1; // 中文
//            }
//            else // 字符
//            {
//                if (*s == 0x0D) // 换行符号
//                {
//                    y += sizey;
//                    x = x0;
//                    s++;
//                }
//                else
//                {
//                    EPD_ShowChar(x, y, *s, color, sizey);
//                    x += sizey / 2; // 字符,为全字的一半
//                }
//                s++;
//            }
//        }
//        else // 中文
//        {
//            if (x > (EPD_W - sizey) || y > (EPD_H - sizey))
//            {
//                return;
//            }
//            bHz = 0;
//            if (sizey == 12)
//                EPD_ShowChinese12x12(x, y, s, color, sizey);
//            else if (sizey == 16)
//                EPD_ShowChinese16x16(x, y, s, color, sizey);
//            else if (sizey == 24)
//                EPD_ShowChinese24x24(x, y, s, color, sizey);
//            else
//                EPD_ShowChinese32x32(x, y, s, color, sizey);
//            s += 2;
//            x += sizey;
//        }
//    }
//}

///**
// * @brief       字符居中显示
// * @param       x:此输入参数无效
// * @param       y:显示位置行起始坐标
// * @param       *s:显示字符起始地址
// * @param       color:字符颜色
// * @param       sizey:字符大小
// * @retval      无
// */
//void EPD_StrCenter(uint16_t x, uint16_t y, const char *s, uint8_t color, uint8_t sizey)
//{
//    uint16_t len = strlen((const char *)s);
//    uint16_t x1 = (EPD_W - len * 8) / 2;
//    EPD_ShowStr(x1, y, s, color, sizey);
//}

/**
 * @brief       图片显示函数
 * @param       x:图片显示位置列起始坐标
 * @param       y:图片显示位置行起始坐标
 * @param       width:图片宽度
 * @param       height:图片高度
 * @param       pic:图片取模数组
 * @param       color:图片颜色
 * @note        图片宽度宽度限制248以下包含248
 * @retval      无
 */
void EPD_ShowPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t pic[], uint8_t color)
{
    uint8_t t, temp;
    uint16_t x0 = x;
    uint32_t i, TypefaceNum; // 一个图片所占字节大小
    TypefaceNum = ((width % 8) ? (width / 8 + 1) : (width / 8)) * height;
    for (i = 0; i < TypefaceNum; i++)
    {
        temp = pic[i];
        for (t = 0; t < 8; t++)
        {
            if (temp & 0x80)
            {
                EPD_DrawPoint(x, y, color);
            }
            else
            {
                EPD_DrawPoint(x, y, !color);
            }
            x++;
            temp <<= 1;
        }
        if ((x - x0) == width)
        {
            x = x0;
            y++;
        }
    }
}

/**
 * @brief       利用字符函数实现秒表UI
 * @param       x:UI显示位置列起始坐标
 * @param       y:UI显示位置行起始坐标
 * @param       num:显示的浮点数
 * @param       pre:显示浮点数精度
 * @param       len:显示浮点数的位数(不包含小数点)
 * @param       color:字符颜色
 * @param       sizey:字符大小
 * @retval      无
 */
void EPD_ShowWatch(uint16_t x, uint16_t y, float num, uint8_t pre, uint8_t len, uint8_t color, uint8_t sizey)
{
    uint8_t t, temp, sizex;
    uint16_t num1;
    sizex = sizey / 2;
    num1 = num * mypow(10, pre);
    for (t = 0; t < len; t++)
    {
        temp = (num1 / mypow(10, len - t - 1)) % 10;
        if (t == (len - pre))
        {
            EPD_ShowChar(x + (len - pre) * sizex + (sizex / 2 - 2), y - 6, ':', color, sizey);
            t++;
            len += 1;
        }
        EPD_ShowChar(x + t * sizex, y, temp + 48, color, sizey);
    }
}
