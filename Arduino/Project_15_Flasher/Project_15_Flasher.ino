const int flashPins[] = {2, 3, 4, 5};
const int chargePin = 6;

const int delaySeconds = 30;
const int chargeSeconds = 10;


void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(flashPins[i], OUTPUT);
    digitalWrite(flashPins[i], HIGH);
  }
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, HIGH);
}

void loop()
{
  chargingOff();
  delay(chargeSeconds * 1000l);
  flashCircle();
  chargingOn();
  delay(delaySeconds * 1000l);
}

void chargingOff()
{
  digitalWrite(chargePin, LOW);
}

void chargingOn()
{
  digitalWrite(chargePin, HIGH);
}

void flashCircle()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(flashPins[i], LOW);
    delay(200);
    digitalWrite(flashPins[i], HIGH);
    delay(500);
  }
}

