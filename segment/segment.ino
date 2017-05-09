//单个数码管共阴极数字编码表

//硬件连接和I/O分配-别用0-7脚连接数码管，会下不了程序的
#if 0
！警告！
8个LED如果共阴不加对地限流电阻的话
    >单片机芯片会很【烫】，危险！！！
        ——《爱上单片机》说得对，当时无知的我还以为瞎扯
0和1脚驱动大电流时或者被接上外电路时可能无法下载程序
#endif

int segmentPins[] = {
    13, 12, 11, 10, 9, 8, 7, 6
}; //【数组低位先读h】h到a,a在最右边，因为读位是右往左读(←)
   //而读数组是左往右读(→)所以引脚定义取反，得保持一致
byte numbersTable[] = { //右边是低位,最左边是a，最右边是h
    B11111100, //0      【数字表低位先读h】
    B01100000, //1
    B11011010, //2
    B11110010, //3
    B01100110, //4
    B10110110, //5
    B10111110, //6
    B11100000, //7
    B11111110, //8    
    B11100110  //9
};

void setup() 
{
    for (int i=0; i<8; i++)
    {
        pinMode(segmentPins[i], OUTPUT);
    }

}

//如何实现6段数码管显示6位数
//除10取模,逐位显示
void loop() 
{//程序功能：每隔1秒循环显示0-9   
    for (int number=0; number<10; number++)
    {
        numberDisplay(number);
        delay(1000);
    }
}

void numberDisplay(int number) //首单词不大写的话突出显示Display意思
{
    bool bitValue = LOW;
    for (int i=0; i<8; i++)
    {
        bitValue = bitRead(numbersTable[number], i);
        digitalWrite(segmentPins[i], bitValue);
    }            
}

