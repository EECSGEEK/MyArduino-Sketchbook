/*  ★轻触开关问题探索★  */
#if 0
void Scan()
{
    if ( 0 == Key1 )
    {
        delay(20);
        if ( 0 == Key1 )
        {
            LED = ~LED;          //↓等待松手
            while ( 0 == Key1 ); //保证松手前状态只改变一次
        }
    }
}
#endif

//硬件连接与I/0分配
const int ADD = 0; //中断0，2脚
const int SUB = 1; //中断1，3脚

//变量定义
int set = 90;

void setup() 
{
    Serial.begin(9600); //设置串口波特率
    pinMode(ADD, INPUT_PULLUP); 
    pinMode(ADD, INPUT_PULLUP); 
    attachInterrupt(ADD, Add, FALLING);
    attachInterrupt(SUB, Sub, FALLING);
    //由于中断有四种触发方式，外接逻辑门某种意义上实现1控4
}

void loop() 
{
    //delay的时候会不会触发中断呢？
    Serial.println(set);
}

void Add()
{
    delay(5);
    set++;
    return;
}

void Sub()
{
    delay(5);
    set++;
    return;
}

//以前不靠谱的方案
/*方案一  普通轻触按键程序
    while (LOW == digitalRead(add))
    {
         delay(75);
         set++; 
         delay(75);  
    }
*/

/*方案二  上升沿/松手时执行操作
while (LOW == digitalRead(Add))
    {
        // while(1)
        // {
             bool last = digitalRead(Add);
             delay(10);
             bool now = digitalRead(Add);
             if (HIGH == now && LOW == last)
             {
                 set++;
                 goto add_exit;
             }
        // }
    }
    add_exit:
*/

