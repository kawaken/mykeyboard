#include "Arduino.h"
#include "Keyboard.h"

const int rowNum = 2;
const int colNum = 2;

const int rowPin[rowNum] = {3, 4};
const int colPin[colNum] = {5, 6};
const byte keyMap[rowNum][colNum] = {
    {0x61, 0x62},
    {0x63, 0x64}};

bool currentState[rowNum][colNum];
bool beforeState[rowNum][colNum];

void setup()
{

  for (int i = 0; i < rowNum; i++)
  {
    pinMode(rowPin[i], OUTPUT);
  }

  for (int i = 0; i < colNum; i++)
  {
    pinMode(colPin[i], INPUT_PULLUP);
  }

  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      currentState[i][j] = HIGH;
      beforeState[i][j] = HIGH;
    }
    digitalWrite(rowPin[i], HIGH);
  }

  Serial.begin(9600);
  Keyboard.begin();
}

void loop()
{
  for (int i = 0; i < rowNum; i++)
  {
    digitalWrite(rowPin[i], LOW);

    for (int j = 0; j < colNum; j++)
    {
      currentState[i][j] = digitalRead(colPin[j]);

      if (currentState[i][j] != beforeState[i][j])
      {

        Serial.print("key(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");

        if (currentState[i][j] == LOW)
        {
          Serial.println(" Push!");
          Keyboard.press(keyMap[i][j]);
        }
        else
        {
          Serial.println(" Release!");
          Keyboard.release(keyMap[i][j]);
        }
        beforeState[i][j] = currentState[i][j];
      }
    }
    digitalWrite(rowPin[i], HIGH);
  }
}
