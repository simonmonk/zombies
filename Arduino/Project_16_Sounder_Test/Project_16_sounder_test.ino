const int sounderPinA = 8;
const int sounderPinB = 9;

void setup()
{
  pinMode(sounderPinA, OUTPUT);
  pinMode(sounderPinB, OUTPUT);  
  Serial.begin(9600);
  Serial.println("Enter frequency in Hz");
}

void loop()
{
  if (Serial.available())
  {
    long f = Serial.parseInt();
    beep(f, 1000);
  }
}

void beep(long f, long duration)
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
