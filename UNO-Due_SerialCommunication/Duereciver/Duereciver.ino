// Due reciver
char str[4];

void setup() 
{
Serial.begin(9600);
Serial1.begin(9600);
}

void loop() 
{
int i = 0;
if ( Serial1.available() )
{
    delay(2);
    Serial.println( Serial1.read() );
}
}
