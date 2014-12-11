
const int scanPin = A0;
const int resetPin = A1;
const int pulseLength = 1000;
const int period = 5000;
const int numStations = 5;

int count = 0;

void setup()                 
{
  pinMode(scanPin, INPUT);
  pinMode(resetPin, INPUT);
}

void loop()                    
{
  delay(period);
  pinMode(scanPin, OUTPUT);
  digitalWrite(scanPin, HIGH);
  delay(pulseLength);
  pinMode(scanPin, INPUT);
  count ++;
  if (count == numStations)
  {
    count = 0;
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
    delay(pulseLength);
    pinMode(resetPin, INPUT);
  }
}
 
