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
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = 4;
  Mirf.config();
  Serial.println("Started"); 
}

void loop()
{
  if (digitalRead(switchPin) == LOW)
  {
    Serial.println("Sending Buzz");
    sendBuzz(); 
  }
}

void sendBuzz()
{
  for (int i = 0; i < numberOfSends; i++)
  {
    Mirf.setTADDR((byte *)"serv1");
    Mirf.send(data);
    while(Mirf.isSending()){}
  }
}
