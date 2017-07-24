#define Potentiometer A0
#define IN1 22
#define IN2 24
#define PWM 7

void setup() {
    analogWriteResolution(12);
    analogReadResolution(12);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    pinMode(PWM, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int PWM_value = analogRead(Potentiometer);
    analogWrite(PWM, PWM_value);
}


