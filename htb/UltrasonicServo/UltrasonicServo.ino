#include <Ultrasonic.h>
Ultrasonic ultrasonic1(A8, A9); // trig echo(1k)
#define beepPin 9
#define servoPin 8
#include <Adafruit_NeoPixel.h>
#define ledbarPin 6
#define BRIGHTNESS 50
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, ledbarPin, NEO_GRB + NEO_KHZ800);

#include <Servo.h>
Servo myServo; // 78是中间位，往左数值变高，往右数值变低
#define servoMid 78
int curAngle = 78;
bool direction = true; // clockwise
#define angleRange 120
#include <Metro.h> 
int beepFrequence = 1; // 1, 2, 4, 8, 16
int beepDutyRatio = 10; // 单位百分比
bool beepState = LOW;
Metro beepDelay = Metro(10*beepDutyRatio/beepFrequence);
Metro servoTurn = Metro(25);

int speed;
void setup() 
{
    myServo.attach(servoPin); // 舵机信号线不能用模拟脚
    myServo.write(servoMid); // 打到半偏防止复位时转动角度过大损坏舵机
    Serial.begin(9600);
    Serial1.begin(9600); // Serial1 on pins 19 (RX) and 18 (TX)
    pinMode(beepPin, OUTPUT); 
    strip.setBrightness(BRIGHTNESS);
    strip.begin();
    strip.show();
}

void loop() 
{
    //Serial.println( ultrasonic1.distanceRead() ); 
    if ( Serial1.available() )
    {
        delay(2);
        speed = Serial1.read();
        Serial.println(Serial1.read());
    }
    if (ultrasonic1.distanceRead() <= 25)
    {
        digitalWrite(beepPin, beepState);
        alarm( ultrasonic1.distanceRead() );
        if (beepDelay.check() == 1) 
        {
            if (beepState == HIGH) 
            { 
                beepState = LOW;
                beepDelay.interval(10*(100-beepDutyRatio)/beepFrequence);
            } 
            else 
            {
                beepState = HIGH; 
                beepDelay.interval(10*beepDutyRatio/beepFrequence); 
            }
            digitalWrite(beepPin, beepState);
        }
    }
    else digitalWrite(beepPin, LOW); // 做一个“补集”
    if (servoTurn.check() == 1)
    {
        if (curAngle == servoMid+angleRange/2)
            direction = false;
        if (curAngle == servoMid-angleRange/2)
            direction = true;
        if (direction == true) // clockwise
            myServo.write(++curAngle);
        if (direction == false) // anticlockwise
            myServo.write(--curAngle);
    }
    while ( Serial1.available() )
    {
                Serial.println( Serial1.read() , DEC);
        delay(2);
        if ( 'b' == Serial1.read() )
        {
            colorWipe(strip.Color(0, 0, 255), 50);
            break;
        }
        if ( 'g' == Serial1.read() )
        {
            colorWipe(strip.Color(0, 255, 0), 50);
            break;
        }
        if ( 'y' == Serial1.read() )
        {
            colorWipe(strip.Color(255, 255, 0), 50);
            break;
        }
        if ( 'r' == Serial1.read() )
        {
            colorWipe(strip.Color(255, 0, 0), 50);
            break;
        }

    }
}

void alarm(int frontDistant)
{
    int minDistant = frontDistant;
// 先对四个测距比大小，取最小的
    if (minDistant <= 4)
        beepFrequence = 16;
    else if (minDistant <= 9)
        beepFrequence = 8;
    else if (minDistant <= 14)
        beepFrequence = 4;
    else if (minDistant <= 19)
        beepFrequence = 2;
    else if (minDistant <= 24)
        beepFrequence = 1;
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

