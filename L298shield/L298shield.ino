// L298 shield
#define SPEED 8
#define PWMB 11
#define DIRB 13
int read;
void setup() 
{
    pinMode(PWMB, OUTPUT); // 使能端PWM占空比0停机
    digitalWrite(DIRB, HIGH);
    pinMode(DIRB, OUTPUT); // 高电平正转 低电平反转

    /* 红外对管测速部分初始化 */
    pinMode(9, OUTPUT);
    digitalWrite(9, LOW);
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    pinMode(SPEED, INPUT); // 红外对管被遮挡返回高电平

    Serial.begin(9600);
    
}

void loop() 
{
    Serial.println(pulseIn(SPEED, HIGH) ); // unsigned long 型返回的是微妙
    while (Serial.available() ) // 如果LabVIEW向Arduino发数据
    {
        read = Serial.parseInt();
        analogWrite(PWMB, read);
        read = 0; // 清空串口读取数据
    }
//    if (Serial.available() ) 
//    {
//        byte r = Serial.read();
//        analogWrite(PWMB, r); // 虽然我们不能打印这个byte
//    } // 但是read到的byte可以直接无损发给DA的
}

