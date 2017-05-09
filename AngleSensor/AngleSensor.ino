/* ★♥基于Arduino的4-bit接法1602显示实时角度♥★  */
//全局版goto
//#include <setjmp.h>
//jmp_buf jmpbuffer;
int mode = 0; 
#include <LiquidCrystal.h>
// ★I/O口分配★
const int MODE1 = 2; //就差把模式一和模式二的自锁开关换成轻触开关
const int MODE2 = 3; 
const int Left = 5; //5和6脚共用同一个定时器，故分配这两个管脚给PWM输出
const int Right = 6; 
const int OUT = 7; /* 声光提示，3脚接蜂鸣器和彩色LED */ 
const int RS = 8;  
const int E = 9;
const int D4 = 10; 
const int D5 = 11; 
const int D6 = 12; 
const int D7 = 13;
const int Sensor = A0; //角度传感器/电位器与A0连接
const int Angle = A1; //模式二确认角度引脚 
int cnt = 0; //模式二计数器
//A2A3A4空闲
const int Set = A5; 
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  //与1602通信的管脚定义(RS, E, D4, D5, D6, D7)

#define MAX_ANTICLOCKWISE 297 //(逆时针)最大角度,逆时针转到底对应297°，旋钮指针在12点钟方向时对应0°
//★每转1°B50K电位器变化146.6欧姆★ | 接个820欧姆的对地/下拉电阻，且电位器的地线单独
float rev = 0; //用于保存接收到的数据
//必须用float因为向 1602申请显示格数是固定的，int的话个位数也会强行凑成三位数造成丢失数据

/* 串口通信相关参数,不重要的变量所以挨一行写了 */
//int hour = 0; int minute = 0; int second = 0;  

float set = 90;

//···························································    
void setup() 
{
    lcd.begin(16, 2); //液晶屏是1602
    //*lcd.setCursor(int, int)的用法【第一个0表示从第一格开始显示】,第二个0表示第一行
    lcd.setCursor(0, 1); lcd.print("S:"); 
    lcd.setCursor(9, 0); lcd.print("1:"); 
    lcd.setCursor(9, 1); lcd.print("2:"); 
    
    pinMode(Sensor, INPUT); 
    pinMode(Set, INPUT);
    //有趣的是没有设置上拉输入状态，单片机会121212模式无限循环下去
    pinMode(MODE1, INPUT_PULLUP);  pinMode(MODE2, INPUT_PULLUP);
    pinMode(Angle, INPUT_PULLUP);
    
    pinMode(Left, OUTPUT); pinMode(Right, OUTPUT);
    pinMode(OUT, OUTPUT);

    //timeSet(17, 10, 0); /* 设置时间 */  
    //Serial.begin(9600); //设定串口的通讯波特率
    //Serial_Print_Information(); /* 往串口发送的一些重要信息 */
    
    attachInterrupt(MODE1 - 2, Mode_1, FALLING);
    attachInterrupt(MODE2 - 2, Mode_2, FALLING);
}

//因为在void loop()里面不能用条件预编译
//所以另外一种多模式的写法就是三个#if对应 void loop
void loop() 
{
    
if (0 == mode) //选择模式在主函数内时不能用预编译
{
    //Serial_Print_Time(); 
    Serial.println(analogRead(Sensor)); /* 显示实时时间与角度 */
    Display();
    digitalWrite(Left, 0); digitalWrite(Right, 0); analogWrite(OUT, 0);
    
}

if (1 == mode)
{
    //全局goto相关->int jmp_value = setjmp(jmpbuffer);
    lcd.setCursor(6, 0);  lcd.print("M1");
    Table(set); digitalWrite(OUT, HIGH);
    Display();
    while (abs(set-rev) >= 8)
    {
        Display(); 
        if (rev < set)
        {
            Set_PWM(250,50);
            Super_Delay(10);
        }
        if (rev < set)
        {
            Set_PWM(250, 50);
            Super_Delay(10);
        }
           
    }
    if (set >= 90)
        Set_PWM(125, 165);
    else 
        Set_PWM(75, 175);
    Super_Delay(5000);
    
    Set_PWM(255,0);
    Super_Delay(600);
    lcd.setCursor(6, 0);  lcd.print("  ");
    mode = 0;
}

if (2 == mode)
{
    //如何用一个I/O口控制N多功能的办法：定义一个2bit变量去计数，第一次按下松开锁定第一个设定的数据
    //右按下->右松开锁住第一个设定角度-> 左按下->左松开锁住第二个设定角度
    //->按下蓝色OK开始执行摇摆->最后松开所有键清屏
    lcd.setCursor(6, 0); lcd.print("M2");
    bool pre_state = digitalRead(Angle);
    float angle_1;
    while (cnt != 4)
    {
        Display();
        if (digitalRead(Angle) != pre_state)
        {
            pre_state = digitalRead(Angle);
            cnt++;
        }
        switch (cnt)
        {
        case 1:
            Display(); 
            lcd.setCursor(11, 0); lcd.print(set);
            break;
        case 2:
            Display();
            angle_1 = set;
            lcd.setCursor(11, 0); lcd.print(angle_1, 1);
            break; 
        case 3:
            Display();
            lcd.setCursor(11, 1); lcd.print(set);
            break;
        default:
            break;
        }
    }
    const float angle_2 = set;
    for (int i=0; i<3; ++i)
    { 
        digitalWrite(OUT, HIGH); 
        Table(angle_1); 
        Super_Delay(3000);
        
        digitalWrite(OUT, LOW); 
        Table(angle_2); 
        Super_Delay(3000);
    }
    Set_PWM(0, 255); Super_Delay(600);
    lcd.setCursor(11, 0); lcd.print("     ");
    lcd.setCursor(11, 1); lcd.print("     ");
    lcd.setCursor(6, 0);  lcd.print("  ");
    cnt = 0;
    mode = 0;
}

}
//···························································
//---------------------------------------------------------------------------------------------------------------------
//函数名称：【中断】Mode_2
//入口参数：无
//函数功能：【等待按键2按下进入★摇摆模式★】 
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Mode_2(void)
{
    mode = 2;
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：Display
//入口参数：无
//函数功能：显示必须实时输出的东西
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Display(void)
{
    //////////////////////必须实时采集显示部分//////////////////////////////////////////
    rev = map(analogRead(Sensor), 0, 1023, 0, MAX_ANTICLOCKWISE); //map是等比映射的意思
    set = map(analogRead(Set), 0, 1023, 45, 135);
    lcd.setCursor(0, 0);  lcd.print(rev, 1); //1602上显示小数点后一位
    lcd.setCursor(2, 1);  lcd.print(set, 1);
    //\\\\\\\\\\\\\\\\\\\\必须实时采集显示部分\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：Super_Delay
//入口参数：delay多少毫秒
//函数功能：延时的同时进行读当前角度和设置角度
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Super_Delay(int ms)
{
    unsigned long pre = millis();
    while (millis()-pre <= (unsigned long)ms)
    {
        //以下是必须实时交互的代码
        Display();
    }
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：Set_PWM
//入口参数：左风机转速， 右风机转速
//函数功能：修改两个全局变量的值
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Set_PWM(int l, int r)
{
    analogWrite(Left, l); analogWrite(Right, r); 
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：【中断】Mode_1
//入口参数：无
//函数功能：【等待按键按下】 
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Mode_1(void)
{
    //中断时时delay和时钟停止，程序永远无法推出中断Super_Delay(2000);
    //longjmp(jmpbuffer, 1); 
    mode = 1;
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：Table
//入口参数：设定角度
//函数功能：将角度与PWM输出关系一一对应
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Table(int set) //穷举法，先把风板打到半偏，然后再吹志设定角度
{
    if ( (50 <= set && set <= 85) )
    {
        Set_PWM(175, 225);
        Super_Delay(60);
    } 
    if (set > 90)
    {
        Set_PWM(135, 235);
        Super_Delay(60);
    }
    if (set <= 50)
        Set_PWM(45, 205);
    else if (set <= 55) 
        Set_PWM(52, 155);
    else if (set <= 60) 
        Set_PWM(57, 150);
    else if (set <= 65)
        Set_PWM(60, 131);
    else if (set <= 70)
        Set_PWM(80, 125);
    else if (set <= 75) 
        Set_PWM(105, 165);  
    else if (set <= 80) 
        Set_PWM(90, 35);
    else if (set <= 85)
        Set_PWM(95, 33);
    else if (set <= 90) 
        Set_PWM(170, 25); 
    else if (set <= 95)
        Set_PWM(60, 25);
    else if (set <= 100)
        Set_PWM(90, 25);
    else if (set <= 105)
        Set_PWM(90, 25);
    else if (set <= 110)
        Set_PWM(90, 25);
    else if (set <= 115)
        Set_PWM(90, 25);
    else if (set <= 120)
        Set_PWM(87, 30); 
    else if (set <= 125)
        Set_PWM(60, 45);
    else if (set <= 130)
        Set_PWM(205, 40);  
    else if (set <= 135)
        Set_PWM(80, 25);
    return;
}

#if 0
//---------------------------------------------------------------------------------------------------------------------
//函数名称：timeSet
//入口参数：时(int),分(int),秒(int)
//函数功能：设置当前时间，赋值给三个时分秒相关的外部(全局)变量
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void timeSet(int h, int m, int s)
{
    hour = h; minute = m; second = s;
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：Serial_Print_Time
//入口参数：无
//函数功能：在串口每行左侧显示实时时间
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Serial_Print_Time(void)
{
    second = (millis()/1000);
    if (60 == second)
    {
        second = 0;
        minute++;
    }
    if (60 == minute)
    {
         minute = 0; 
         hour++;          
    }
    Serial.print(hour);   Serial.print(": ");
    Serial.print(minute); Serial.print(": ");
    Serial.print(second); Serial.print(":  ");
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//函数名称：Serial_Print_Information
//入口参数：无
//函数功能：串口复位时显示重要参数信息
//函数返回：无
//---------------------------------------------------------------------------------------------------------------------
void Serial_Print_Information(void)
{    
    Serial.println(" ");
    Serial.println("*********************************************");  
    Serial.print("****Max(Vector_anticlockwise) = ");  Serial.print(MAX_ANTICLOCKWISE); Serial.println("degree****");
    Serial.println("*********************************************"); 
    Serial.println(" ");
    return;
}
#endif

//···························································
//无法处理的几个问题：
//[1] 代码鲁棒性不足，无法对错误的按键操作进行屏蔽
#if 0
新学习到的表达式： while (size-- >= 0)
新学习到的函数： 
    constrain(x, a, b); //约束函数，下限 a，上限 b，x 必须在 ab 之间才能返回。 
    long random(minn, maxx);
新学到的中断方法：
    外部逻辑门扩展中断
    n个按键编号，对应模式1到n，按一下，一个变量就变为该数值，
    两个外部中断按键，一个执行模式[变量]，一个终止并把变量清0
#endif
/* 目录 */
//一、IO分配
//二、外部中断
//三、函数与关键词【工具箱】
/* 1.1 ★模拟与数字引脚互用问题★
 *     1.1.1 模拟引脚也可以当作数字引脚使用
 *           ★编号为14(对应模拟引脚0)到19(对应模拟引脚5)★
 *           ★编号为14(对应模拟引脚0)到19(对应模拟引脚5)★
 *           ★编号为14(对应模拟引脚0)到19(对应模拟引脚5)★
 *           可以说模拟引脚比数字引脚更【高级】
 *           模拟引脚【继承】了数字引脚的读写函数
 *     1.1.2 只有nano有A6和A7，所以别想着数字当模拟用
 * 1.2 ★analogWrite()和analogRead()★
 *     ★只有PWM输出脚能用analogWrite()实现PWM★
 *     只有A0-A5能用analogRead
 *     ★模拟引脚不能模拟输出★
 *     千万别写analogWrite(A1, 128)不会报错，但是会导致一个未知的错误
 *     真尴尬，模拟管脚不能模拟输出
 *     The analogWrite function has nothing to do with the analog pins or the analogRead function. 
 * 1.3 PWM-analogWrite()    
 *     5和6共用一个定时器驱动PWM，980hz，其余都是490hz，9和10也是一对，3和11也是一对
 * 1.4 digitalRead()读轻触开关    
 *     void setup()  
 * ★核心★pinMode(18, INPUT_PULLUP);       
 *     while (LOW == digitalRead(18))
 *     {
 *         if (HIGH == digitalRead(18))
 *         {
 *             delay(10); //去上升沿振荡，去抖动
 *             //不加delay有时按一下触发几次
 *             //上升沿边缘应该是微秒级别的，可以考虑微秒延时
 *             Serial.println("Press!!");
 *             break;
 *         }
 *     } //代码缺点，有时按键会失灵，大概按三下中间那下就读不到了，10下能用7下
 * 1.5 analogRead(A0-A5)
 *     ？？？【可以通过AREF调整输入上限】？？？
 * 1.6 中断引脚对应的编号    
 *     2号脚中断号0，3号脚中断号1触发中断引脚  
 * ______________________________________________________________________________________________________________________    
 *     
 * 2.1 【中断编号】
 *     2号脚中断号0，3号脚中断号1触发中断引脚
 * 2.2 【中断触发方式】
 *     上升沿RISING、下降沿FALLING、同时触发CHANGE、低电平LOW
 * 2.3 ★中断函数★
 *     2.3.1 attachInterrupt(interrupt_number, function, mode) //(中断编号， 中断调用函数， 中断触发方式)
 *         函数在setup中调用一次就行了
 *     2.3.2 detachInterrupt(interrupt_number)
 *         detachInterrupt(中断号)
 *     2.3.3 ★开关中断★
 *         //nointerrupts()[先出现]与Interrupts()[后出现]必须成对出现
 *         //nointerrupts()必须在Interrupts()上面
 *         void loop()
 *         {
 *             noInterrupts(); 
 *             // critical, time-sensitive code here
 *             interrupts();
 *             // other code here
 *         }    
 *     2.3.4 重新分配中断
 *         当重新使用attachInterrupt()时，先前分配的中断就会从对应引脚上移除。
 * 2.4 ★中断、delay与millis★【待补充】
 *     2.4.1 delay时millis暂停，delay会影响millis
 *     2.4.2 当中断函数发生时，delya()和millis()的数值将不会继续变化。
 * 2.5 中断会影响串口通信
 *     当中断发生时，串口收到的数据可能会丢失。你应该声明一个变量来在未发生中断时储存变量。
 * 2.6 其它I/O口通过外加门电路与中断引脚连接也能实现"中断"
 * ______________________________________________________________________________________________________________________    
 * 
 * 3.1 时间类函数
 *     micros(void); //返回程序运行了多少微秒 
 *     delayMicroseconds(int); //微秒级延时
 *     millis(void); //返回程序运行了多少毫秒
 *     delay(int); //毫秒级延时
 * 
 * 3.1 陌生的关键词
 *     run、clock、signal、send、stop、time、step
 * 
 */

