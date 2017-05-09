//一个早期FORTRAN语言写的可见光波长转RGB份量的代码
//Document: 【FORTRAN】Spectra Code.pdf
#include <UTFT.h>
UTFT myGLCD(ILI9481, 38, 39, 40, 41);

double R = 0.0;
double G = 0.0;
double B = 0.0;
double count = 380;
void trans(int w)
{
    if (w >= 380 && w < 440)
    {
        R = -(w - 440.) / (440. - 380.);
        G = 0.0;
        B = 1.0;
    }
    else if (w >= 440 && w < 490)
    {
        R = 0.0;
        G = (w - 440.) / (490. - 440.);
        B = 1.0;
    }
    else if (w >= 490 && w < 510)
    {
        R = 0.0;
        G = 1.0;
        B = -(w - 510.) / (510. - 490.);
    }
    else if (w >= 510 && w < 580)
    {
        R = (w - 510.) / (580. - 510.);
        G = 1.0;
        B = 0.0;
    }
    else if (w >= 580 && w < 645)
    {
        R = 1.0;
        G = -(w - 645.) / (645. - 580.);
        B = 0.;
    }
    else if (w >= 645 && w <= 720)
    {
        R = 1.0; 
        G = 0.0;
        B = 0.0;
    }
}

int y = 0;

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
        trans(count);
        Serial.print(R, 4);
        Serial.print("    ");
        Serial.print(G, 4);
        Serial.print("    ");
        Serial.print(B, 4);
        Serial.println("    ");
        myGLCD.setColor(255-int(R*255), 255-int(G*255), 255-int(B*255));
        myGLCD.drawLine(0, y, 479, y);
        count++;
        y++;
        delay(1);
    }
    delay(100000);
}
