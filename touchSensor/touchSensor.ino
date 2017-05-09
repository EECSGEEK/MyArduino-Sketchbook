//touchSensor触摸板比轻触按键好多了
//按住的话一直是1，灵敏度基本满足要求，无需程序调节
//人碰一下大概是80ms左右，含触摸模块时程序delay不宜大于80ms
const int VCC = 13; //引脚当VCC，请勿模仿
const int touchSIG = 12;

const int huoerSensor = A0;

void setup() 
{
    pinMode(touchSIG, INPUT);
    pinMode(VCC, OUTPUT);
    digitalWrite(VCC, HIGH);
    Serial.begin(9600);
}

void loop() 
{
    //Serial.println( digitalRead(touchSIG) );
    Serial.println( analogRead(huoerSensor) );
}

