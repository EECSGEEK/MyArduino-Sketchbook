void setup() {
  // put your setup code here, to run once:
pinMode(A3, OUTPUT); //VCC
digitalWrite(A3, HIGH);
pinMode(A4, OUTPUT); //GND
digitalWrite(A4, LOW);
//pinMode(2, OUTPUT);
//analogReadResolution(12);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(A5));
itoa(123, str, 10);
}

