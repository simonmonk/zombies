

#include <LiquidCrystal.h>


const int buzzerPin = 11;
const int backlightPin = 10;
const int switchPin = A0;
const int pirPin = 2;     


//                RS,E,D4,D5,D6,D7         
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
boolean silent = false;

void setup() 
{
  // This because of a defect in common cheap LCD displays
  // backlight controlled by transistor D10 high can
  // burn out Arduino pin
  pinMode(backlightPin, INPUT);
  pinMode(pirPin, INPUT);       
}

void loop() 
{
  checkPIR();                    
  if (analogRead(switchPin) < 1000) // any key pressed
  {
    silent = ! silent;
    if (silent) noTone(buzzerPin);
    delay(300);
  }
  delay(100);
}

void checkPIR()
{
  boolean zombies = digitalRead(pirPin);
  if (zombies)
  {
    if (! silent)
    {
      tone(buzzerPin, 1000);
    }
    lcd.setCursor(0, 1);
    lcd.print("ZOMBIES!!");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("         ");    
  }
  if (silent)
  {
   lcd.setCursor(12, 0);
   lcd.print("MUTE");
  }
  else
  {
   lcd.setCursor(12, 0);
   lcd.print("    ");
  }  
}




