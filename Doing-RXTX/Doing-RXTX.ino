#if 0
int val; //初始值是-1，Arduino对没有初始化的变量自动赋值-1
         //但是char类型范围0-127，赋值-1会向下溢出的
//此处的int最好放到loop里面
Serial.read()函数从串口获得数据。
Arduino语言提供的这个函数是不阻塞的，
也就是说不论串口上是否真的有数据到达，该函数都会立即返回。

函数Serial.available()的功能是返回串口缓冲区中当前剩余的字符个数，
按照Arduino提供的该函数的说明，串口缓冲区中最多能缓冲128个字节。
Serial.print("Available: ");
      Serial.println(Serial.available(), DEC);
#endif

const int Heat = 6;
const int LM35 = A0;
int temperature = 0;
String readString = "";
void setup() 
{
    Serial.begin(9600);
    pinMode(Heat, OUTPUT);
    pinMode(LM35, INPUT);
}

void loop() 
{
    temperature = map(analogRead(LM35), 0, 1023, 0, 500);
    constrain(temperature, 5, 75); 
    //Serial.println(temperature);
    /* ↓读取区 Reading↓ */
    while (Serial.available() > 0)  
    {
        readString += char( Serial.read() );
        delay(2); //读串口时的delay(2)不能删掉，否则串口缓冲区不够时间接受数据。
    }

    /* ↓操作区 Operating↓ */
    if (readString == "green")
    {
        Serial.println("\nArduino:Turn on green LED");
    }
    //这里不能输出字符串S2终端
    //[Error]:Serial.println("Arduino had read: ");

    int tempertureSet = readString[0];
    constrain(tempertureSet, 5, 75);
    analogWrite(Heat, tempertureSet*4);
    /* ↓清空区 Clear↓ */
    if (readString.length() > 0)
    {
        Serial.print("\nArduino had read: ");
        Serial.println(readString[0], DEC); //由于C++端发来的是ASCII码
        readString = "";
        Serial.println("\n\t------------------------\n");
    }
}

//int readData = Serial.read(); //自动刷新数据
//如果发送一个字节则用Serial.write(1);
//Serial.flush
//Serial.println(readData);
//再提醒一个：comdata说是一个字符串，也是一个数组，
//引用每个字的话可以用comdata[0]，comdata[1]。。。comdata[n]。
//如果我们要每个字节取出的话，可以每个引用。

//落后的写法1
#if 0
void setup() 
{
    Serial.begin(9600);
    Serial.println("Please input a word!");
}

void loop() 
{
    int val = Serial.read(); //默认以ASCII码读取串口数据
    if (-1 != val && 0 != val) //连上win后可能会发送0
    {
        if ( Serial.available() >= 2 )
        {

        }
        else
}
#endif

