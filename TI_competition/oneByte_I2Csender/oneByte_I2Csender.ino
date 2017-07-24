#include <Wire.h>

void setup() {
    analogReadResolution(8);
    Wire.begin(0x1E);         
    Wire.onRequest(requestEvent); // register event
    Serial.begin(9600);
}

void loop() {
    delay(100);
    
    uint16_t AD = analogRead(A0);
    int AD2 = analogRead(A0);
    Serial.println( sizeof(AD2) ); // Don't froget sizeof function
    Serial.println(AD);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
    uint8_t AD_8bit = analogRead(A0);
    Wire.write(AD_8bit);
}
