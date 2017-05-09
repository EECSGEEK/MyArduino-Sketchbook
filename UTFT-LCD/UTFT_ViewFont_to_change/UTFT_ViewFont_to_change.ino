// UTFT_ViewFont (C)2014 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the included fonts.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>
//#define setColor_Red do { \
//    myGLCD.setColor(0, 255, 255);\    // 实际的RGB是(255, 0, 0)
//} while (0)
#define setColor_Red myGLCD.setColor(0, 255, 255)

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT myGLCD(ILI9481,38,39,40,41);

void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  setColor_Red;
}

void loop()
{
  static char i=1;
  myGLCD.clrScr();
  if(i==1)
  myGLCD.setColor(255, 0, 0);  
  else if(i==2)
  myGLCD.setColor(0, 255, 0);
  else if(i==3)
  {
  myGLCD.setColor(0, 0, 255);
  i=0;
  }
  i++;
  myGLCD.setBackColor(VGA_WHITE); //文字背景色
  myGLCD.setFont(BigFont);
  myGLCD.print(" htb Car Project ", CENTER, 0);
  myGLCD.print("0123456789:;<=>?", CENTER, 16);
  myGLCD.print("@ABCDEFGHIJKLMNO", CENTER, 32);
  myGLCD.print("PQRSTUVWXYZ[\\]^_", CENTER, 48);
  myGLCD.print("`abcdefghijklmno", CENTER, 64);
  myGLCD.print("pqrstuvwxyz{|}~ ", CENTER, 80);

  myGLCD.setFont(SmallFont);
  myGLCD.print(" !\"#$%&'()*+,-./0123456789:;<=>?", CENTER, 120);
  myGLCD.print("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", CENTER, 132);
  myGLCD.print("`abcdefghijklmnopqrstuvwxyz{|}~ ", CENTER, 144);

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.print("0123456789", CENTER, 190);
  delay(1000);
  //while(1) {}; 
}

