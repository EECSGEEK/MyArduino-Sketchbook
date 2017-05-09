#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
RF24 radio(7, 8); // CNS, CE
const byte addresses[][6] = {"00001", "00002"};

void setup() 
{
    radio.begin();
    radio.openWritingPipe(addresses[0]); // 00001
    radio.openReadingPipe(1, addresses[1]); // 00002
    radio.setPALevel(RF24_PA_MIN);
    Serial.begin(9600);
}
int count = 0;
void loop() 
{
    delay(5);
    
    radio.startListening();
    if ( radio.available() ) 
    {
        while (radio.available()) 
        {
            int V = 0;
            radio.read(&V, sizeof(V));
            Serial.println(V, DEC);
        }
    }
    delay(5);
    
    radio.stopListening();
    count++;
    if (200 ==count)
        count = 0;
    radio.write( &count, sizeof(count) );
}
