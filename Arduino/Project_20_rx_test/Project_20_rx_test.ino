#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

const int buzzerPin = 4;
const int switchPin = 5;

//            sig    sig   cmd   data
//            0x54   0x12  0x01  0x00
byte data[4];


void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("HELLO");
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = 4;
  Mirf.config();
}


void loop()
{  
  if(!Mirf.isSending() && Mirf.dataReady())
  {
    Mirf.getData(data);
    checkForBuzz();
  }
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

