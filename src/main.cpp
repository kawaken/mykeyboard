#include "Arduino.h"
#include "Keyboard.h"

const int keyNum = 2;

const int inputPin[keyNum] = {3, 4};
const byte keyMap[keyNum] = {0x61, 0x62};

bool currentState[keyNum];
bool beforeState[keyNum];

void setup()
{
  for (int i = 0; i < keyNum; i++)
  {
    pinMode(inputPin[i], INPUT);
    currentState[i] = LOW;
    beforeState[i] = LOW;
  }

  Serial.begin(9600);
  Keyboard.begin();
}

void loop()
{
  for (int i = 0; i < keyNum; i++)
  {
    currentState[i] = digitalRead(inputPin[i]);

    if (currentState[i] != beforeState[i])
    {
      Serial.print("key");
      Serial.print(i);

      if (currentState[i] == HIGH)
      {
        Serial.println("\tPush!");
        Keyboard.press(keyMap[i]);
      }
      else
      {
        Serial.println("\tRelease!");
        Keyboard.release(keyMap[i]);
      }

      beforeState[i] = currentState[i];
    }
  }
}
