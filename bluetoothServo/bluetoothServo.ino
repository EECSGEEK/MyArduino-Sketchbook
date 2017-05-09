#include <SoftwareSerial.h> // TX RX software library for bluetooth

#include <Servo.h>  // servo library
Servo myservo1, myservo2, myservo3; // servo name

int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin
int motorPin =6; // usamos un pin de salida al LED
int state = 2; // variable lectura dato serial
int bandera=1;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo1.attach(3); //attach servo signal wire to pin 9
  myservo2.attach(4);
  myservo3.attach(5);

  //Setup usb serial connection to computer
  Serial.begin(9600);  

  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);

  pinMode(motorPin, OUTPUT); // declara pin de salida
  digitalWrite(motorPin, LOW); // normalmente apagado

}

void loop()
{
  //Read from bluetooth and write to usb serial
  
  if(bluetooth.available ()>= 3 )
  {
    unsigned int servopos =bluetooth.read();
    delay(2);
    unsigned int servopos1= bluetooth.read();
    unsigned int realservo =(servopos1 *256) +servopos;
    Serial.println(realservo);

    if (realservo >=1000 && realservo <1180) {
      int servo1 = realservo;
      servo1 = map(servo1, 1000,1180, 0, 180);
      myservo1.write(servo1);
      Serial.println("Servo 1 ON");
      delay(10);
      
    }
    if (realservo >= 2000 && realservo <2180){
      int servo2 = realservo;
      servo2= map(servo2, 2000,2180, 0, 180);
      myservo2.write(servo2);
      Serial.println("Servo 2 ON");
      delay(10);
    }
    if (realservo >= 3000 && realservo <3180){
      int servo3 = realservo;
      servo3= map(servo3, 3000,3180, 0, 180);
      myservo3.write(servo3);
      Serial.println("Servo 3 ON");
      delay(10);
    }
    if(Serial.available() > 0){
    }
    state = Serial.read(); 
    } 
    if (state == "1"  && bandera == 1) 
    { 
      digitalWrite(motorPin, HIGH); 
      bandera = 1; 
      state = 1; 
      } 
      if (state == "2" && bandera == 0) 
      { 
        digitalWrite(motorPin,LOW); 
        bandera = 0; 
        state = 2;
      }
  }﻿
