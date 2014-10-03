

#include <LiquidCrystal.h>

/* 
Any projects that you want to exclude from this program should have a
value of "false". That way, you will not get any false alarms because
of missing hardware.
*/
const boolean project2 = true; // Battery Monitor
const boolean project6 = true; // PIR Alarm
const boolean project10 = true; // Door Monitor
const boolean project11 = true; // Fire Alarm
const boolean project12 = true; // Temperature Monitor

// Pin allocations
const int buzzerPin = 11;
const int voltagePin = A3;
const int backlightPin = 10;
const int switchPin = A0;
const int pirPin = 2;   
const int doorPin = 12;   
const int smokePin = 3;
const int tempPin = A2;    


// Project 2 constants
const float maxV = 12.6;
const float minV = 11.7;
const float warnV = 11.7;
const float R1 = 470.0;
const float R2 = 270.0;
const float k = (R1 + R2) / R2;

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
  pinMode(pirPin, INPUT);   
  pinMode(smokePin, INPUT);
  pinMode(doorPin, INPUT_PULLUP);
  lcd.begin(16, 2);
}

void loop() 
{
  if (project2) checkBattery();
  if (project6) checkPIR();     
  if (project10) checkDoor(); 
  if (project11) checkSmoke();
  if (project12) checkTemp();
  
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

void warn(char message[])
{
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("            ");
  if (!mute)
  {
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
  }
  delay(100);
}


void checkBattery()
{
  if (readVoltage() < warnV)
  {
    alarm("VOLTS!!");
  }
  displayVoltage();
  displayBar();
}


void displayVoltage()
{
  lcd.setCursor(0, 0);
  lcd.print("Battery");
  lcd.setCursor(8, 0);
  lcd.print("        ");
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
  
  int numBars = fullness * 10;
  lcd.setCursor(0, 1);
  for (int i = 0; i < 10; i++)
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
}


void checkPIR()
{
  if (digitalRead(pirPin))
  {
    alarm("ZOMBIES!!");
  }
}

void checkDoor()
{
  if (digitalRead(doorPin))
  {
    warn("DOOR");
  }
}

void checkSmoke()
{
  if (digitalRead(smokePin))
  {
    alarm("FIRE!!");
  }
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
