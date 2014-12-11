
const int buzzerPin = 5;
const int switchPin = 2;

const int V3 = 153; // analogWrite value for 3V


void setup()
{
  analogWrite(buzzerPin, 0);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("HELLO");
}


void loop()
{  
  if (digitalRead(switchPin) == LOW)
  {
    analogWrite(buzzerPin, V3);
    delay(100);
    analogWrite(buzzerPin, 0);
  }
}

