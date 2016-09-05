#include <Arduino.h>
#include "SevenSegmentArrayDisplay.h"

void SevenSegmentArrayDisplay::setup()
{
  for (int i = 0; i < 7; i++) {
    pinMode(SEVEN_SEG_PINS[i], OUTPUT);
    digitalWrite(SEVEN_SEG_PINS[i], LOW);
  }
  for (int i = 0; i < DISPLAY_COUNT; i++) {
    pinMode(SEVEN_SEG_CATHODES[i], OUTPUT);
    digitalWrite(SEVEN_SEG_CATHODES[i], HIGH);
  }
  lastUpdate = millis();
}

void SevenSegmentArrayDisplay::update()
{
  unsigned long currentMillis = millis();
  if ((currentMillis - lastUpdate) > updateInterval) // time to update
  {
    lastUpdate = currentMillis;

    int displayIndex = lastDisplayIndex - 1;
    if (displayIndex < 0) {
      displayIndex = 2;
    }

    //calc number to print
    bool doPrint = true;
    int digit;
    long counter = min(999, currentMillis / 100);
    if (displayIndex == 0) {
      digit = counter % 10;
    }
    else if (displayIndex == 1) {
      digit = (counter / 10) % 10;
      if (lastDigit == 0 && digit == 0) {
        doPrint = false;
      }
    }
    else if (displayIndex == 2) {
      digit =  counter / 100;
      if (digit == 0) {
        doPrint = false;
      }
    }

    //disable previous cathode
    digitalWrite(SEVEN_SEG_CATHODES[lastDisplayIndex], HIGH);

    lastDigit = digit;
    lastDisplayIndex = displayIndex;

    if (doPrint) {
      //set states of each segment pin
      for (int i = 0; i < 7; i++) {
        digitalWrite(SEVEN_SEG_PINS[i], SEVEN_SEG_PIN_STATES[digit][i]);
      }

      //enable current cathode
      digitalWrite(SEVEN_SEG_CATHODES[displayIndex], LOW);
    }
  }
}

