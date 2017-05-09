//LM35 1脚VCC 2脚信号线 3脚GND
//温度为0°时输出0V，温度为100°时输出1V
//精度不到0.5°，建议用int类型就行了
const int LM35 = A0;

int temperature = 0;

void setup() 
{
    pinMode(LM35, INPUT);
    Serial.begin(9600);
}

void loop() 
{
    temperature = map(analogRead(LM35), 0, 1023, 0, 500);
    constrain(temperature, 0, 120); //超出范围至多显示120
    //Serial.print(temperature);
    Serial.println( analogRead(LM35) ); 
}

