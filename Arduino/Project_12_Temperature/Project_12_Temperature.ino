

#include <LiquidCrystal.h>

// Pin allocations
const int buzzerPin = 11;
const int backlightPin = 10;
const int switchPin = A0;
const int tempPin = A2;    

// Project 12 constants
// these can be in C or F
const float maxTemp = 45.0;
const float minTemp = -10.0;


//                RS,E,D4,D5,D6,D7         
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean mute = false;

void setup() 
{
  // This because of a defect in common cheap LCD displays
  // backlight controlled by transistor D10 high can
  // burn out Arduino pin
  pinMode(backlightPin, INPUT);
  lcd.begin(16, 2);
}

void loop() 
{
  checkTemp();
  
  if (analogRead(switchPin) < 1000) // any key pressed
  {
    mute = ! mute;
    if (mute) 
    {
      noTone(buzzerPin);
      lcd.setCursor(12, 1);
      lcd.print("MUTE");
    }
    else
    {
      lcd.setCursor(12, 1);
      lcd.print("    ");
    }
    delay(300);
  }
  delay(100);
}

void alarm(char message[])
{
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("            ");
  if (!mute)
  {
    tone(buzzerPin, 1000);
  }
  delay(100);
}

void alarm(char message[], float value)
{
  alarm(message);
  lcd.setCursor(5, 1);
  lcd.print(" ");
  lcd.print(value);
}

void checkTemp()
{
  float t = readTemp();
  if (t > maxTemp)
  {
    alarm("HOT", t);
  }
  else if (t < minTemp)
  {
    alarm("COLD", t);
  }
}

float readTemp()
{
  int raw = analogRead(tempPin);
  float volts = raw / 205.0;
  float tempC = 100.0 * volts - 50;
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  // One of the following two lines must be uncommented
  // Either return the temperature in C or F
  return tempC;
  // return tempF;
}
