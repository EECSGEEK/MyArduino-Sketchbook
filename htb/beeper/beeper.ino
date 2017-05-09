#define beepPin 9
int beepFrequence = 1; // 1, 2, 4, 8, 16
int beepDutyRatio = 10; // 单位百分比
bool beepState = LOW;
#include <Metro.h> 
Metro beepMetro = Metro(1000); 
Metro beepDelay = Metro(10*beepDutyRatio/beepFrequence);
void setup() 
{
    pinMode(beepPin, OUTPUT); digitalWrite(beepPin, beepState);
}
void loop() 
{
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
    if (beepMetro.check() == 1) 
    {
        beepFrequence *= 2;
        if (beepFrequence == 16)
            beepFrequence = 1;
    }
}
