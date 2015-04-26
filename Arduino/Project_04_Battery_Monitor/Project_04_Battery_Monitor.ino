

#include <LiquidCrystal.h>

// Project 2 thresholds
const float maxV = 12.6;
const float minV = 11.7;
const float warnV = 11.7;

// Pin allocations
const int buzzerPin = 11;
const int voltagePin = A3;
const int backlightPin = 10;
const int switchPin = A0;

// Project 2 constants
const float R1 = 470.0;
const float R2 = 270.0;
const float k = (R1 + R2) / R2;


//                RS,E,D4,D5,D6,D7         
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean mute = false;

void setup()
{
// Because of a defect in common cheap LCD displays,
// backlight controlled by transistor D10 high can
// burn out Arduino pin
  pinMode(backlightPin, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Battery ");
}

void loop()
{
  displayVoltage();
  displayBar();
  if (readVoltage() < warnV && ! mute)
  {
    tone(buzzerPin, 1000);
  }
  if (analogRead(switchPin) < 1000) // any key pressed
  {
    mute = ! mute;
    if (mute) noTone(buzzerPin);
    delay(300);
  }
  delay(100);
}

void displayVoltage()
{
  lcd.setCursor(8, 0);
  lcd.print(" ");
  lcd.setCursor(8, 0);
  lcd.print(readVoltage());
  lcd.setCursor(14, 0);
  lcd.print("V");
}


float readVoltage()
{
  int raw = analogRead(voltagePin);
  float vout = (float(raw) / 1023.0) * 5.0;
  float vin = (vout * k);
  return vin;
}

void displayBar()
{
  float v = readVoltage();
  float range = maxV - minV;
  float fullness = (v - minV) / range;
  int numBars = fullness * 16;
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++)
  {
    if (numBars > i)
    {
      lcd.print("*");
    }
    else
    {
      lcd.print(" ");
    }
  }
  if (mute)
  {
    lcd.setCursor(12, 1);
    lcd.print("MUTE");
  }
}


