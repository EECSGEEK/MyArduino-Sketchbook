#include <Ultrasonic.h>
#include <Servo.h>
Servo myServo; // 78是中间位，往左数值变高，往右数值变低
#define servoMid 78
int curAngle = 78;
bool direction = true; // clockwise
#define angleRange 120
#include <Metro.h> 
#define beepPin 9
#define trigPin A8
#define echoPin A9
int distance;
long duration;
int beepFrequence = 1; // 1, 2, 4, 8, 16
int beepDutyRatio = 10; // 单位百分比
bool beepState = LOW;
Metro beepDelay = Metro(10*beepDutyRatio/beepFrequence);
Metro servoTurn = Metro(25);
void setup() 
{
    myServo.attach(8); // 舵机信号线不能用模拟脚
    myServo.write(servoMid); // 打到半偏防止复位时转动角度过大损坏舵机
    Serial.begin(9600);
    pinMode(beepPin, OUTPUT); 
}

void loop() 
{
    Serial.println( distanceRead() ); 
    if (distanceRead() <= 25)
    {
        digitalWrite(beepPin, beepState);
        alarm( distanceRead() );
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

int distanceRead()
{ 
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
    distance= duration*0.034/2;
    return distance;
}
