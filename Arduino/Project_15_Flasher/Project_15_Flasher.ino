const int flashPins[] = {7, 6, 5};

const long overallDelay = 20; // seconds
const long delayBetweenFlashes = 1; // seconds

void setup()
{
  pinMode(flashPins[0], OUTPUT);
  pinMode(flashPins[1], OUTPUT);
  pinMode(flashPins[2], OUTPUT);
}

void loop()
{
  flashCircle();
  delay(overallDelay * 1000);
}

void flashCircle()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(flashPins[i], HIGH);
    delay(200);
    digitalWrite(flashPins[i], LOW);
    delay(delayBetweenFlashes * 1000);
  }
}

