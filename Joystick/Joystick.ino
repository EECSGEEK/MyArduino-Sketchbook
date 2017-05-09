//摇杆驱动,【注意同款摇杆也会出现静态电压不一致】
#if 0
注意 Mouse 和 Keyboard 两个库只能Leonboard用 
#endif 
#if 0
API怎么接啊！
    Firmata 库
        for communicating with 
        applications on the computer 
        using a standard serial protocol. 
        #include <Board.h>
        #include <Firmata.h>
        
    Messenger 库  
        for processing text-based messages from the compute
    MsTimer2 库
        uses the timer 2 interrupt to 
        trigger an action every N milliseconds.
    Simple Message System
        send messages between Arduino and the computer
    TextString 
        handle strings
    TLC5940
        16 channel 12 bit PWM controller
#endif
const int horizontal = A2; //水平
const int vertical = A1; //带轻触开关的是y轴，也就是跟文字垂直方向
//这个设计很坑啊，明明传感器度y轴线，
//都出来的却是实际上横的方向
int x;
int y;
long order = 0;

void setup() 
{
    Serial.begin(9600); 
    //查找FFT.h
}

void loop() 
{
while (1)
{
    x = analogRead(horizontal);
    y = analogRead(vertical);
    if ( (x<=503 || x>=513) || (y<=490 || y>=500) )
    {
        /* ★串口绘图器代码★
        Serial.print("X= "); 
        Serial.print(x);
        Serial.print("    ");
        Serial.print("Y= "); 
        Serial.println(y);
        */
        Serial.print(order);
        Serial.print(": ");
        delay(15);
        if (x >= 550)
        {
            Serial.println("Turn Up");
            order++;
            continue;
        } 
        if (x <= 490)
        {
            Serial.println("Turn Down");
            order++; 
            continue; 
        }
        if (y >= 525)
        {
            Serial.println("Turn Right");
            order++;
            continue;
        }
        if (y <= 475)
        {
            Serial.println("Turn Left");
            order++;
            continue;        
        }
    }

}

}

//总结：
//摇杆很容易动一下就飙到0或1023，建议只控制方向
//摇杆过渡过程很快很不平滑非线性，不建议调速

