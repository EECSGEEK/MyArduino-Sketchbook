/* ★L298N练习题★
 * ·设置一个按键实现电机的启动和停止
 * 
 * ·一个电位器控制电机
 *   逆时针最大时正转最快
 *   顺时针最大时反转最快
 *   中间有一个死区/静止区
 *   
 * ·指示灯和蜂鸣器
 *   连续短鸣一次+红灯 -- 正转
 *   连续长鸣一次+蓝灯 -- 反转
 *   连续短鸣三次+黄灯 -- 停止
 *   红蓝两灯亮度随转速变化
 * 
 * ·提高部分 
 *   转动时蜂鸣器能用tone函数唱歌
 */

//硬件连接与IO分配
//电位器棍子朝人，右手边接VCC
//灯的亮度变化不明显可能因为是共用一个220欧姆对地电阻
//也可能是PWM的频率太快了，PWM1档输出居然都很亮
//所以放弃灯随转速变化，另外tone函数很鸡肋，按钮没意思
//最后，反转居然有问题
const int Potentiometer = A0; //电位器5V-AD-GND接法，这连着中间脚
const int Button = 2;  //轻触按键连着中断脚2
//const int Beep = 3;    //蜂鸣器
const int ENA = 5;     //连接L298N使能端A
const int LEDred = 6; //tone函数会对3和11脚PWM产生干扰
const int IN1 = 7; //连接L298N逻辑端1
const int IN2 = 8; //连接L298N逻辑端2
const int LEDblue = 11;
const int LEDyellow = 12; 

int val = 300; //量化研究方法
//[0, 255]   正转区间 1 0
//[256, 337] 静止区间 0 0
//[338, 593] 反转区间 0 1
bool mode = HIGH;

void setup() 
{
    pinMode(Potentiometer, INPUT);
    pinMode(Button, INPUT_PULLUP);
    attachInterrupt(Button-2, Mode_Change, FALLING);

    //pinMode(Beep ,OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(LEDred, OUTPUT);
    pinMode(LEDblue, OUTPUT);
    pinMode(LEDyellow, OUTPUT);

    Serial.begin(9600);
}

void loop() 
{
    
if (LOW == mode)
{//↓停止模式↓
    ;
}//↑停止模式↑
else
{//运行模式
    val = map(analogRead(Potentiometer), 0, 1023, 0, 593);
    if (0 <= val && val <= 255)
    {//正转
        //tone(Beep, 450*val, 3000);
        //当进入tone时，系统会开辟一个新的线程给tone记时
        //即便不在这个if内，也会响完
        //analogWrite(Beep, val);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 255-val);
        
        digitalWrite(LEDred, HIGH);
        digitalWrite(LEDblue, LOW);
        digitalWrite(LEDyellow, LOW);
        
    }
    if (256 <= val && val <= 337)
    {//停机
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);

        digitalWrite(LEDred, LOW);
        digitalWrite(LEDblue, LOW);
        digitalWrite(LEDyellow, HIGH);
        
    }
    if (338 <= val && val <= 593)
    {//反转
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA, val-338);
        
        digitalWrite(LEDred, LOW);
        digitalWrite(LEDblue, HIGH);
        digitalWrite(LEDyellow, LOW);
        Serial.println(val);
    }

}

}

void Mode_Change()
{
    mode = !mode; //取反一般用叹号，按位取反特殊场合用
}

//附录一 tone函数
#if 0
任意脚产生占空比50%的方波
持续时间可以设定，否则波形会一直产生知道调用noTone
★同一时间只能产生一个声音(意思是定时器就一个，不能驱动双声道)
  如果希望多个引脚多个声音，请务必在下次调用前先noTone()
语法：
  tone(pin, frequency)
  tone(pin, frequency, duration) //持续时间unsigned long型 毫秒
  //就像一个英语单词又多种形式，动词副词等等，用对了才行
  noTone(pin);
#endif

//附录二 delay和中断的问题
#if 0
   中断时四个时间类函数全部停止：  delayMicroseconds micros millis delay
   有经验的程序员都会避免超过10ms的delay
       delay 必须小于looptime 
   使用中断时，需定义一个变量时刻保存串口收到数据防止中断丢失
#endif

#if 0
//附录三 串口通信二次开荒-理论准备篇
void setup()
{
    Serial.begin(9600);
    while (!Serial); //等待连接 Serial当又连接时返回true
}
#endif

