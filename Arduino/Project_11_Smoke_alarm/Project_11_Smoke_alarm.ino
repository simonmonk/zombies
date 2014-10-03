

#include <LiquidCrystal.h>

const boolean project11 = true; // Fire Alarm

// Pin allocations
const int buzzerPin = 11;
const int backlightPin = 10;
const int switchPin = A0;
const int smokePin = 3;


//                RS,E,D4,D5,D6,D7         
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean mute = false;

void setup() 
{
  // This because of a defect in common cheap LCD displays
  // backlight controlled by transistor D10 high can
  // burn out Arduino pin
  pinMode(backlightPin, INPUT);
  pinMode(smokePin, INPUT);
  lcd.begin(16, 2);
}

void loop() 
{
  checkSmoke();
 
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


void checkSmoke()
{
  if (digitalRead(smokePin))
  {
    alarm("FIRE!!");
  }
}


