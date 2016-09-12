#include <Arduino.h>
#include "SevenSegmentArrayDisplay.h"

void SevenSegmentArrayDisplay::setup(int maxVal)
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
  maxValue = maxVal;
}

bool SevenSegmentArrayDisplay::update(unsigned long startTime)
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
    long counter = (currentMillis-startTime) / 100;
    if(counter >= maxValue) {
      counter = maxValue;
      reachedMax = true;
    }
    
    if(startTime > currentMillis) {
      counter = 0;
    }
    if (displayIndex == 0) {
      digit = counter % 10;
    }
    else if (displayIndex == 1) {
      if (counter < 10) {
        doPrint = false;
      } else {
        digit = (counter / 10) % 10;
      }
    }
    else if (displayIndex == 2) {
      if(counter < 100) {
        doPrint = false;
      } else {
        digit =  counter / 100;
      }
    }

    //disable previous cathode
    digitalWrite(SEVEN_SEG_CATHODES[lastDisplayIndex], HIGH);

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
  return reachedMax;
}

