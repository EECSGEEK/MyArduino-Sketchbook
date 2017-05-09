#include <UTFT.h>
UTFT myGLCD(ILI9481, 38, 39, 40, 41);
double r = 0.0;
double g = 0.0;
double b = 0.0;
int count = 400;
int y = 10;

void setup() 
{
    Serial.begin(9600);
    myGLCD.InitLCD(); // LANDSCAPE(default默认横屏显示) PORTRAIT竖屏显示
    myGLCD.clrScr();  // 清除旧的程序在上面显示的东西，清屏后变为白屏
}

void loop() 
{
    while (count < 701)
    {
        spectral_color(count);
        Serial.print(r, 4);
        Serial.print("    ");
        Serial.print(g, 4);
        Serial.print("    ");
        Serial.print(b, 4);
        Serial.println("    ");
        myGLCD.setColor(255-int(r*255), 255-int(g*255), 255-int(b*255));
        myGLCD.drawLine(0, y, 479, y);
        count++;
        y++;
        delay(1);
    }
    delay(100000);
}

void spectral_color(double l) // RGB <0,1> <- lambda l <400,700>[nm]
{
    double t;
//http://stackoverflow.com/questions/1472514/convert-light-frequency-to-rgb?rq=1
//http://stackoverflow.com/questions/3407942/rgb-values-of-visible-spectrum?noredirect=1&lq=1
         if ((l>=400.0)&&(l<410.0)) { t=(l-400.0)/(410.0-400.0); r=    +(0.33*t)-(0.20*t*t); }
    else if ((l>=410.0)&&(l<475.0)) { t=(l-410.0)/(475.0-410.0); r=0.14         -(0.13*t*t); }
    else if ((l>=545.0)&&(l<595.0)) { t=(l-545.0)/(595.0-545.0); r=    +(1.98*t)-(     t*t); }
    else if ((l>=595.0)&&(l<650.0)) { t=(l-595.0)/(650.0-595.0); r=0.98+(0.06*t)-(0.40*t*t); }
    else if ((l>=650.0)&&(l<700.0)) { t=(l-650.0)/(700.0-650.0); r=0.65-(0.84*t)+(0.20*t*t); }
         if ((l>=415.0)&&(l<475.0)) { t=(l-415.0)/(475.0-415.0); g=             +(0.80*t*t); }
    else if ((l>=475.0)&&(l<590.0)) { t=(l-475.0)/(590.0-475.0); g=0.8 +(0.76*t)-(0.80*t*t); }
    else if ((l>=585.0)&&(l<639.0)) { t=(l-585.0)/(639.0-585.0); g=0.84-(0.84*t)           ; }
         if ((l>=400.0)&&(l<475.0)) { t=(l-400.0)/(475.0-400.0); b=    +(2.20*t)-(1.50*t*t); }
    else if ((l>=475.0)&&(l<560.0)) { t=(l-475.0)/(560.0-475.0); b=0.7 -(     t)+(0.30*t*t); }
}

