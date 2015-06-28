#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

const int numberOfSends = 3;

const int buzzerPin = 5;
const int switchPin = 2;

const int buzzerVolume = 100; // keep less that 153 for 3V
const int buzzMinDuration = 20;

byte data[] = {0x54, 0x12, 0x01, 0x00};

void setup()
{
  analogWrite(buzzerPin, 0);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("HELLO");
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  listenMode();
  Mirf.payload = 4;
  Mirf.config();
}


void loop()
{  
  if(!Mirf.isSending() && Mirf.dataReady())
  {
    Serial.println("got somethinhg");
    Mirf.getData(data);
    checkForBuzz();
  }
  if (digitalRead(switchPin) == LOW)
  {
    Serial.println("Sending Buzz");
    sendBuzz(); 
  }
}

void listenMode() 
{
  Mirf.setRADDR((byte *)"serv1");   
  Serial.println("Listening");
}

void sendMode() 
{
  Serial.println("Send mode");
  
}


void sendBuzz()
{
  sendMode();
  for (int i = 0; i < numberOfSends; i++)
  {
    Mirf.setTADDR((byte *)"serv1");
    Mirf.send(data);
    while(Mirf.isSending()){}
  }
  listenMode();
}


void checkForBuzz()
{
  if (data[0]==0x54 && data[1]==0x12 && data[2]==0x01)
  {
    analogWrite(buzzerPin, buzzerVolume);
    delay(buzzMinDuration);
    analogWrite(buzzerPin, 0);
  }
}
