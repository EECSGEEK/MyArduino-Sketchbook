void setup() {
    analogReadResolution(12);
    Serial.begin(115200);
}

void loop() {
    Serial.println( analogRead(A0) );
}

