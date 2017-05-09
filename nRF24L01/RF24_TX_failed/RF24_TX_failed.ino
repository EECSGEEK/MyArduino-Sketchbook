#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#define RS 7
#define E  6
#define D4 5
#define D5 4
#define D6 3
#define D7 2
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

RF24 radio(7, 8); // CNS, CE
const byte addresses[][6] = {"00001", "00002"};

void setup() 
{
    radio.begin();
    radio.openWritingPipe(addresses[1]); // 00001
    radio.openReadingPipe(1, addresses[0]); // 00002
    radio.setPALevel(RF24_PA_MIN);
}
int direction[3] = {0};
#define Up    1
#define Down  2
#define Left  3 
#define Right 4
int count = 0;

void loop() 
{
    delay(5);
    
    radio.stopListening();
    int potValue = analogRead(A0);
    radio.write( &potValue, sizeof(potValue) );
    delay(5);

    radio.startListening(); 
    while ( !radio.available() ); //同步
    radio.read( &count, sizeof(count) );
    lcd.setCursor(0, 0); lcd.print(count);
}
