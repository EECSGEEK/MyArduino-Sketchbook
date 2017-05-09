#include <TFT_HX8357_Due.h> 
#include "Free_Fonts.h"
TFT_HX8357_Due tft = TFT_HX8357_Due(); 
#define BLACK 0xFFFF
#define WHITE 0x0000
#define RED   0x07FF
#define AQUA  0xF800  // 浅绿，由于配色鲜艳看起来像蓝绿
#define GREEN 0x8010 
#define PURPLE 0x0400
#define BLUE  0xFFE0
#define YELLOW 0x001F
#define MAROON 0x0410 // 棕色，褐红色
#define TEAL  0x8000  // 蓝绿色，由于蓝绿混合显得
#define FUCHSIA 0x07E0// 紫红色
#define LIME  0xF81F  // 亮绿色/石灰的单词
#define OLIVE 0x0010  // 橄榄色,淡黄的
#define NAVY  0x8400  // 藏青色(其实是暗蓝色)
#define ORANGE 0x041F
/***************************************************************************************
** Function name:           color565
** Description:             convert three 8 bit RGB levels to a 16 bit colour value
***************************************************************************************/
uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void setup() //再高级的作图函数内部也是通过drawLine实现，而drawLine的实现是通过drawPixes 
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(WHITE); //颜色不要改
    for (int i=0; i<480; i++) //与fillScreen(color)配合才能实现黑屏
        tft.drawFastHLine(0, i, tft.width(), 0xffff);

    //标题
    tft.setFreeFont(FSBI18); //高大约30
    tft.setTextColor(WHITE, BLACK);  
    tft.drawString("              htb Car Project               ", 0, 3, GFXFF);
    tft.drawLine(0, 36, 479, 36, RED);

    //四个测距初始显示
    tft.setTextColor(AQUA, BLACK);  
    tft.drawString("Front    Distance:", 20, 40, GFXFF);  tft.setCursor(279, 63); tft.print("void"); tft.drawString("cm", 440, 40, GFXFF); 
    tft.drawString("Back     Distance:", 20, 70, GFXFF);  tft.setCursor(279, 93); tft.print("void"); tft.drawString("cm", 440, 70, GFXFF);
    tft.drawString("LEFT    Distance:", 20, 100, GFXFF); tft.setCursor(279, 123); tft.print("void"); tft.drawString("cm", 440, 100, GFXFF);
    tft.drawString("RIGHT Distance:", 20, 130, GFXFF);   tft.setCursor(279, 153); tft.print("void"); tft.drawString("cm", 440, 130, GFXFF);

    //RPM显示
    tft.setTextColor(ORANGE, BLACK);
    tft.setCursor(5, 183); tft.print("RPM: "); tft.setCursor(89, 183); tft.print("void"); 
    Serial.begin(9600); 

    //ALARM显示
    tft.setTextColor(MAROON, BLACK);
    tft.setCursor(240, 183); tft.print("ALARM "); 
    tft.setTextColor(GREEN, BLACK); tft.setCursor(379, 183); tft.print("OFF"); 

    //分割线 虚线
    for (int i=0; i<480; i++)
    {
        if (i%3 == 0)
            tft.drawPixel(i, 186, BLACK);
        else
            tft.drawPixel(i, 186, FUCHSIA);
    }
    tft.drawLine(0, 36, 479, 36, RED);
    
    //SMOKE显示
    tft.setTextColor(PURPLE, BLACK);
    tft.setCursor(0, 213); tft.print("SMOKE:");
    tft.setCursor(129, 213); tft.print("void");

    //显示文件路径
    tft.setFreeFont(FSB9); tft.setTextColor(LIME, BLACK);
    tft.setCursor(0, 299); tft.print(__FILE__);
    
    //最后的Last upload时间日期显示 
    tft.setFreeFont(FSB12); tft.setTextColor(OLIVE, BLACK);
    tft.setCursor(0, 319); tft.print("Last Burn Time: ");
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(189, 319); tft.setFreeFont(FSB18); tft.print(__TIME__);
    tft.setCursor(349, 319); tft.setFreeFont(FSB12); tft.print(__DATE__);

    //画一个椭圆娱乐一下
    tft.drawEllipse(419, 239, 60, 30, BLUE);
    tft.fillEllipse(419, 239, 60, 30, YELLOW);

    Serial.begin(9600); 
    
    analogWriteResolution(12);
    analogReadResolution(12);

    pinMode(A8, OUTPUT); 
}

void loop() 
{

}


