#include <PID_v1.h>
double Setpoint, Input, Output;

#define FanLeft1_PWM  DAC0
#define FanRight2_PWM DAC1
#define FanLeft1_IN1 8
#define FanLeft1_IN2 9
#define FanRight2_IN1 6
#define FanRight2_IN2 7

// angleSensor ADvalue: 90°= 833, 0°= 581, 45°= 700, 135°= 952
// △10°≈△30AD 
float angle = 0;
void setup() 
{
    Serial.begin(9600);
    digitalWrite(FanLeft1_IN1, HIGH);
    digitalWrite(FanLeft1_IN2, LOW);
    digitalWrite(FanRight2_IN1, HIGH);
    digitalWrite(FanRight2_IN2, LOW);
    analogWriteResolution(12);
    analogReadResolution(12);
}

void loop() 
{
    angle = (analogRead(A0)-581)/3;
    Serial.println(angle);
    analogWrite(DAC1, 4095); // Mid value
}





