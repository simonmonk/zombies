#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

const int numberOfSends = 3;

const int buzzerPin = 4;
const int switchPin = 5;

byte data[] = {0x54, 0x12, 0x01, 0x00};

void setup()
{
  pinMode(buzzerPin, OUTPUT);
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
  Mirf.setRADDR((byte *)"clie1");
}

void checkForBuzz()
{
  if (data[0]==0x54 && data[1]==0x12 && data[2]==0x01)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
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
