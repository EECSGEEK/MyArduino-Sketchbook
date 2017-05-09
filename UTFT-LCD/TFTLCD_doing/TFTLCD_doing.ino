// UTFT库下载地址：http://www.henningkarlsen.com/electronics
/* LCD扩展板重要信息
 * Driver(液晶屏型号)：HX8357B/ILI9481
 * Dots：480x320 pixels
 * Bus：16Bit(16位并行数据通信总线)
 * Reset Button：LCD扩展板上面有个按键是reset，因为扩展板遮挡了板载原有的reset按键
 */
#include <math.h>
#include <UTFT.h>
UTFT myGLCD(ILI9481, 38, 39, 40, 41); 
//库文件里面的颜色应该改为以下才能正常
//TODO把UTFT.h修改版本保存起来
//配色color问题↓
//myGLCD.setColor(0, 255, 255); // 用inverse的观点来看
//这句话的意思是红色占255-0份，G和B占0份，所以最终纯红色
#define BLACK 0xFFFF
#define WHITE 0x0000
//以下的颜色RGB值可能不是特别准
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
#define OLIVE 0x0010  // 橄榄色(其实是暗黄色)
#define NAVY  0x8400  // 藏青色(其实是暗蓝色)

//↓Rainbow 7color 彩虹七色↓ colours in spectrum
// 红   橙     黄      绿     蓝      靛(靛青实际是深紫色)      紫  
//Red Orange Yellow  Green   Blue     Indigo            Violet(紫甘蓝的紫)   
//以上彩虹色序(color order)摘自维基百科https://en.wikipedia.org/wiki/Rainbow                           
#define setColor_Red    myGLCD.setColor(0, 255, 255)   // 实际的RGB是(255, 0, 0)
#define setColor_Orange myGLCD.setColor(0, 128, 255)   // 实际的RGB是(255, 128, 0)
#define setColor_Yellow myGLCD.setColor(0, 0, 255)     // 实际的RGB是(255, 255, 0) 红+绿=黄
#define setColor_Green  myGLCD.setColor(255, 0, 255)   // 实际的RGB是(0, 255, 0)
#define setColor_Blue   myGLCD.setColor(255, 255, 0)   // 实际的RGB是(0, 0, 255)
#define setColor_Indigo myGLCD.setColor(180, 255, 125) // 实际的RGB是(75, 0, 130)
#define setColor_Violet myGLCD.setColor(128, 255, 0)   // 实际的RGB是(127, 0, 255)
//↑Rainbow 7color 彩虹七色↑ colours in spectrum
/* C/C++的多行宏定义在Arduino中不能用
#define WECOMLE(a, b) 
    printf("Wecomle!!!\n"); \
    printf("请问您需要什么\n"); \
    printf("a + b = %d\n", add(a, b)); \
*/
//↓其它重要的颜色↓

//↑其它重要的颜色↑
extern uint8_t SmallFont[]; //uint8_t代表1个字节
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

void setup()
{
    myGLCD.InitLCD(); // LANDSCAPE(default默认横屏显示) PORTRAIT竖屏显示
    myGLCD.clrScr();  // 清除旧的程序在上面显示的东西，清屏后变为白屏
    myGLCD.fillScr(VGA_WHITE); // 黑色背景
    //第一行横向显示标题" htb Car Project "
    myGLCD.setBackColor(VGA_BLACK); // 文本框背景颜色为黑色
    myGLCD.setColor(VGA_WHITE);     // 文字颜色为白色
    myGLCD.setFont(BigFont);        // 文字大小为大号，字体高度12个像素点
    myGLCD.print(" htb Car Project ", CENTER, 10); // 从纵向第十个像素点开始居中显示
    //标题下面画一条红线
    myGLCD.setColor(VGA_RED);
    myGLCD.drawLine(0, 32, 479, 32); //线段起点(0, 32)终点(479, 32)
    ////////////////////////////////////////////////////////////////////////////////////
    setColor_Red;    for (int i=40; i<80; i++)   myGLCD.drawLine(0, i, 479, i);
    setColor_Orange; for (int i=80; i<120; i++)  myGLCD.drawLine(0, i, 479, i);
    setColor_Yellow; for (int i=120; i<160; i++) myGLCD.drawLine(0, i, 479, i);
    setColor_Green;  for (int i=160; i<200; i++) myGLCD.drawLine(0, i, 479, i);
    setColor_Blue;   for (int i=200; i<240; i++) myGLCD.drawLine(0, i, 479, i);
    setColor_Indigo; for (int i=240; i<280; i++) myGLCD.drawLine(0, i, 479, i);
    setColor_Violet; for (int i=280; i<320; i++) myGLCD.drawLine(0, i, 479, i);
}

void loop()
{
    
    //myGLCD.setBackColor(VGA_WHITE);
    //myGLCD.setBackColor(VGA_BLACK);
    //myGLCD.fillScr(VGA_BLACK);   

//    myGLCD.setColor(VGA_WHITE);

//    
//
//  delay(3000);
  //  myGLCD.fillRect(0, 0, 479, 13);
//  myGLCD.fillRect(0, 0, 479, 13);
//  myGLCD.setColor(64, 64, 64);
//  myGLCD.fillRect(0, 306, 479, 319);
//  myGLCD.setColor(255, 255, 255);
//  myGLCD.setBackColor(255, 0, 0);
//  myGLCD.print("* Universal Color TFT Display Library *", CENTER, 1);
//  myGLCD.setBackColor(64, 64, 64);
//  myGLCD.setColor(255,255,0);
//  myGLCD.print("<http://electronics.henningkarlsen.com>", CENTER, 307);
//
//  myGLCD.setColor(0, 0, 255);
//  myGLCD.drawRect(0, 14, 479, 305);

////////////////////////////////////////////////////////////////////////////////
/*
// Draw crosshairs
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(239, 15, 239, 304);
  myGLCD.drawLine(1, 159, 478, 159);
  for (int i=9; i<470; i+=10)
    myGLCD.drawLine(i, 157, i, 161);
  for (int i=19; i<220; i+=10)
    myGLCD.drawLine(237, i, 241, i);

// Draw sin-, cos- and tan-lines  
  myGLCD.setColor(0,255,255);
  myGLCD.print("Sin", 5, 15);
  for (int i=1; i<478; i++)
  {
    myGLCD.drawPixel(i,159+(sin(((i*1.13)*3.14)/180)*95));
  }
  
  myGLCD.setColor(255,0,0);
  myGLCD.print("Cos", 5, 27);
  for (int i=1; i<478; i++)
  {
    myGLCD.drawPixel(i,159+(cos(((i*1.13)*3.14)/180)*95));
  }

  myGLCD.setColor(255,255,0);
  myGLCD.print("Tan", 5, 39);
  for (int i=1; i<478; i++)
  {
    myGLCD.drawPixel(i,159+(tan(((i*1.13)*3.14)/180)));
  }

  delay(2000);

  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(239, 15, 239, 304);
  myGLCD.drawLine(1, 159, 478, 159);

// Draw a moving sinewave
  x=1;
  for (int i=1; i<(478*15); i++) 
  {
    x++;
    if (x==479)
      x=1;
    if (i>479)
    {
      if ((x==239)||(buf[x-1]==159))
        myGLCD.setColor(0,0,255);
      else
        myGLCD.setColor(0,0,0);
      myGLCD.drawPixel(x,buf[x-1]);
    }
    myGLCD.setColor(0,255,255);
    y=159+(sin(((i*0.7)*3.14)/180)*(90-(i / 100)));
    myGLCD.drawPixel(x,y);
    buf[x-1]=y;
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some filled rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255,0,255);
        break;
      case 2:
        myGLCD.setColor(255,0,0);
        break;
      case 3:
        myGLCD.setColor(0,255,0);
        break;
      case 4:
        myGLCD.setColor(0,0,255);
        break;
      case 5:
        myGLCD.setColor(255,255,0);
        break;
    }
    myGLCD.fillRect(150+(i*20), 70+(i*20), 210+(i*20), 130+(i*20));
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some filled, rounded rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255,0,255);
        break;
      case 2:
        myGLCD.setColor(255,0,0);
        break;
      case 3:
        myGLCD.setColor(0,255,0);
        break;
      case 4:
        myGLCD.setColor(0,0,255);
        break;
      case 5:
        myGLCD.setColor(255,255,0);
        break;
    }
    myGLCD.fillRoundRect(270-(i*20), 70+(i*20), 330-(i*20), 130+(i*20));
  }
  
  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some filled circles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        myGLCD.setColor(255,0,255);
        break;
      case 2:
        myGLCD.setColor(255,0,0);
        break;
      case 3:
        myGLCD.setColor(0,255,0);
        break;
      case 4:
        myGLCD.setColor(0,0,255);
        break;
      case 5:
        myGLCD.setColor(255,255,0);
        break;
    }
    myGLCD.fillCircle(180+(i*20),100+(i*20), 30);
  }
  
  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some lines in a pattern
  myGLCD.setColor (255,0,0);
  for (int i=15; i<304; i+=5)
  {
    myGLCD.drawLine(1, i, (i*1.6)-10, 304);
  }
  myGLCD.setColor (255,0,0);
  for (int i=304; i>15; i-=5)
  {
    myGLCD.drawLine(478, i, (i*1.6)-11, 15);
  }
  myGLCD.setColor (0,255,255);
  for (int i=304; i>15; i-=5)
  {
    myGLCD.drawLine(1, i, 491-(i*1.6), 15);
  }
  myGLCD.setColor (0,255,255);
  for (int i=15; i<304; i+=5)
  {
    myGLCD.drawLine(478, i, 490-(i*1.6), 304);
  }
  
  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some random circles
  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=32+random(416);
    y=45+random(226);
    r=random(30);
    myGLCD.drawCircle(x, y, r);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some random rectangles
  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(476);
    y=16+random(289);
    x2=2+random(476);
    y2=16+random(289);
    myGLCD.drawRect(x, y, x2, y2);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

// Draw some random rounded rectangles
  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(476);
    y=16+random(289);
    x2=2+random(476);
    y2=16+random(289);
    myGLCD.drawRoundRect(x, y, x2, y2);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

  for (int i=0; i<100; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(476);
    y=16+random(289);
    x2=2+random(476);
    y2=16+random(289);
    myGLCD.drawLine(x, y, x2, y2);
  }

  delay(2000);
  
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,478,304);

  for (int i=0; i<10000; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    myGLCD.drawPixel(2+random(476), 16+random(289));
  }

  delay(2000);

  myGLCD.fillScr(0, 0, 255);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(160, 70, 319, 169);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("That's it!", CENTER, 93);
  myGLCD.print("Restarting in a", CENTER, 119);
  myGLCD.print("few seconds...", CENTER, 132);
  
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Runtime: (msecs)", CENTER, 290);
  myGLCD.printNumI(millis(), CENTER, 305);
  
  delay (10000);
*/
}


