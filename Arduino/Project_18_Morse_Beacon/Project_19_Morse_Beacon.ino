#include <EEPROM.h>
#include "EEPROMAnything.h"

const int ledPin = 13;
int dotDelay = 100; // milliseconds
const int gapBetweenRepeats = 10; // seconds
const int maxMessageLen = 255;
char message[maxMessageLen];
long lastFlashTime = 0;

char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};

char* numbers[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void setup()                 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready");
  EEPROM_readAnything(0, message);
  if (! isalnum(message[0]))
  {
    strcpy(message, "SOS");
  }
  flashMessage();
}

void loop()                    
{
  char ch;
  if (Serial.available())      // is there anything to be read from USB?
  {
    int n = Serial.readBytesUntil('\n', message, maxMessageLen-1);
    message[n] = '\0';
    EEPROM_writeAnything(0, message);
    Serial.println(message);
    flashMessage();
  }
  if (millis() > lastFlashTime + gapBetweenRepeats * 1000L)
  {
    flashMessage();
  }
}
    
void flashMessage()
{
  Serial.print("Sending: ");
  Serial.println(message);
  int i = 0;
  while (message[i] != '\0' && i < maxMessageLen)
  {
    if (Serial.available()) return;  // new message 
    char ch = message[i];
    i++;
    if (ch >= 'a' && ch <= 'z')
    {
      flashSequence(letters[ch - 'a']);
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
      flashSequence(letters[ch - 'A']);
    }
    else if (ch >= '0' && ch <= '9')
    {
      flashSequence(numbers[ch - '0']);
    }
    else if (ch == ' ')
    {
     delay(dotDelay * 4);      // gap between words  
    }
  }
  lastFlashTime = millis();
}

void flashSequence(char* sequence)
{
   int i = 0;
   while (sequence[i] != NULL)
   {
       flashDotOrDash(sequence[i]);
       i++;
   }
   delay(dotDelay * 3);    // gap between letters
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '.')
  {
    delay(dotDelay);           
  }
  else // must be a -
  {
    delay(dotDelay * 3);           
  }
  digitalWrite(ledPin, LOW);    
  delay(dotDelay); // gap between flashes
}

