// HC-05蓝牙模块,只连四条线(RX TX 5V GND)
// 烧录前记得拔掉RXTX的线
String readString = "";

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    /* ↓读取区 Reading↓ */
    while (Serial.available() > 0)  
    {
        readString += char( Serial.read() );
        delay(2); // 读串口时的delay(2)不能删掉，否则串口缓冲区不够时间接受数据。
    }

    /* ↓操作区 Operating↓ */
    if (readString == "green")
    {
        Serial.println("\nArduino:Turn on green LED");
    }
    // 这里不能输出字符串S2终端
    // [Error]:Serial.println("Arduino had read: ");
    
    /* ↓清空区 Clear↓ */
    if (readString.length() > 0)
    {
        Serial.print("\nArduino had read: ");
        Serial.println(readString);
        readString = "";
        Serial.println("\n\t--------------------\n");
    }
}


//········································
#if 0 //极客工坊的两个串口通信例子[懒得改Tab缩进了]
再附送一个例子，在串口输入1011101..的话，就会令Arduino的D2~Dx引脚产生高/低电平，
当然，一次发送的数据视Arduino引脚数而定，比如Arduino UNO/nano之类的，
只有D2~D13十二个引脚。我们打12个数字就好。比如101101011010，
如果中间有非0和1的字符，则自动跳过该位设置：比如122202221222这样。
因为2不是允许范围内，就只设置D2/D6/D10的值了：
String comdata = "";
void setup()
{
  Serial.begin(9600);
  for(int i = 2; i <= 13; i++) pinMode(i, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)
  {
    comdata += int(Serial.read()) - '0';
    delay(2);
  }
  if(comdata.length() > 0)
  {
    for(int i = 0; i < comdata.length(); i++)
    {
      if(comdata[i]=='0'||comdata[i]=='1')
      {
        digitalWrite(i + 2, comdata[i] - '0');
        Serial.print("Pin ");
        Serial.print(i + 2);
        Serial.print(" is ");
        Serial.println(comdata[i]);
      }
    }
    comdata = "";
  }
}

// 第二个例子
功能如题目。
在串口收到逗号分割的6串数字比如
100,200,45,4,87,99
然后在6个PWM端口3, 5, 6, 9, 10, 11输出对应PWM值

String comdata = "";
//numdata是分拆之后的数字数组
int numdata[6] = {0}, PWMPin[6] = {3, 5, 6, 9, 10, 11}, mark = 0;
void setup()
{
// 定义0~6脚是输出
  for(int i = 0; i < 6; i++) pinMode(PWMPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
// j是分拆之后数字数组的位置记数
  int j = 0;
  
  // 不断循环检测串口缓存，一个个读入字符串，
  while (Serial.available() > 0)
  {
  // 读入之后将字符串，串接到comdata上面。
    comdata += char(Serial.read());
      //延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，
    delay(2);
    //标记串口读过数据，如果没有数据的话，直接不执行这个while了。
    mark = 1;
  }
   
  if (mark == 1)  //如果接收到数据则执行comdata分析操作，否则什么都不做。
  {
  //显示刚才输入的字符串（可选语句）
    Serial.println(comdata);
      //显示刚才输入的字符串长度（可选语句）
    Serial.println(comdata.length());
   
/*******************下面是重点*******************/
// 以串口读取字符串长度循环，
    for(int i = 0; i < comdata.length() ; i++)
    {
        // 逐个分析comdata字符串的文字，如果碰到文字是分隔符（这里选择逗号分割）则将结果数组位置下移一位
        // 即比如11,22,33,55开始的11记到numdata[0];碰到逗号就j等于1了，
        // 再转换就转换到numdata[1];再碰到逗号就记到numdata[2];以此类推，直到字符串结束
      if(comdata == ',')
      {
        j++;
      }
      else
      {
         // 如果没有逗号的话，就将读到的数字*10加上以前读入的数字，
         // 并且(comdata - '0')就是将字符'0'的ASCII码转换成数字0（下面不再叙述此问题，直接视作数字0）。
         // 比如输入数字是12345，有5次没有碰到逗号的机会，就会执行5次此语句。
         // 因为左边的数字先获取到，并且numdata[0]等于0，
         // 所以第一次循环是numdata[0] = 0*10+1 = 1
         // 第二次numdata[0]等于1，循环是numdata[0] = 1*10+2 = 12
         // 第三次是numdata[0]等于12，循环是numdata[0] = 12*10+3 = 123
         // 第四次是numdata[0]等于123，循环是numdata[0] = 123*10+4 = 1234
         // 如此类推，字符串将被变成数字0。
        numdata[j] = numdata[j] * 10 + (comdata - '0');
      }
    }
    //comdata的字符串已经全部转换到numdata了，清空comdata以便下一次使用，
    //如果不请空的话，本次结果极有可能干扰下一次。
    comdata = String("");


    //循环输出numdata的内容，并且写到PWM引脚
    for(int i = 0; i < 6; i++)
    {
      Serial.print("Pin ");
      Serial.print(PWMPin);
      Serial.print(" = ");
      Serial.println(numdata);
      analogWrite(PWMPin, numdata);
      numdata = 0;
    }
    //输出之后必须将读到数据的mark置0，不置0下次循环就不能使用了。
    mark = 0;
  }
}
代码注释很详细了，就不再说明了。
#endif

