#include "Arduino.h"
#include "Keyboard.h"

#define INPUT_PIN 3

bool prevStatus = LOW;

void setup()
{
    pinMode(INPUT_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    Keyboard.begin();

    Serial.begin(9600);
}

void loop()
{
    bool status = digitalRead(INPUT_PIN);
    if (prevStatus == status)
    {
        return;
    }

    prevStatus = status;

    switch (status)
    {
    case HIGH:
        digitalWrite(LED_BUILTIN, HIGH);
        Keyboard.press(0x61);
        Serial.println("Press");

        break;
    case LOW:
        digitalWrite(LED_BUILTIN, LOW);
        Keyboard.release(0x61);
        Serial.println("Release");

        break;
    }
}
