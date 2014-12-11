#include <Servo.h> 

const int minServoAngle = 10;
const int maxServoAngle = 170;
const int stepPause = 5;

const int sounderPinA = 8;
const int sounderPinB = 9;
const int servoPin = 10;

const long f = 700; // find f using Project_16_sounder_test

Servo arm;

void setup()
{
  arm.attach(servoPin);
  pinMode(sounderPinA, OUTPUT);
  pinMode(sounderPinB, OUTPUT);  
}

void loop()
{
  wave();
  wave();
  makeNoise();
}

void wave()
{
  // wave vigously from left to right
  for (int angle = minServoAngle; angle < maxServoAngle; angle++)
  {
    arm.write(angle);
    delay(stepPause);
  }
  for (int angle = maxServoAngle; angle > minServoAngle; angle--)
  {
    arm.write(angle);
    delay(stepPause);
  }  
}

void makeNoise()
{
  for (int i = 0; i < 5; i++)
  {
    beep(500);
    delay(1000);
  }
}


void beep(long duration)
{
  long sounderPeriodMicros = 500000l / f;
  long cycles = (duration * 1000) / sounderPeriodMicros / 2;
  for (int i = 0; i < cycles; i++)
  {
    digitalWrite(sounderPinA, HIGH);
    digitalWrite(sounderPinB, LOW);
    delayMicroseconds(sounderPeriodMicros);
    digitalWrite(sounderPinA, LOW);
    digitalWrite(sounderPinB, HIGH);
    delayMicroseconds(sounderPeriodMicros);    
  } 
}
