#include <Arduino.h>
#include "SevenSegmentArrayDisplay.h"

void SevenSegmentArrayDisplay::setup(long maxVal)
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
  maxValue = (unsigned long)maxVal;
}

void SevenSegmentArrayDisplay::shutdown() {
   for (int i = 0; i < DISPLAY_COUNT; i++) {
    digitalWrite(SEVEN_SEG_CATHODES[i], HIGH);
  }
}

bool SevenSegmentArrayDisplay::update(unsigned long startTime)
{
  unsigned long currentMillis = millis();
  unsigned long endTime = startTime + (maxValue * MILLIS_PER_INCREMENT);

  if ((currentMillis - lastUpdate) >= UPDATE_INTERVAL) // time to update
  {
    lastUpdate = currentMillis;

    int displayIndex = lastDisplayIndex - 1;
    if (displayIndex < 0) {
      displayIndex = 2;
    }

    //calc number to print
    bool doPrint = true;
    int digit;
    unsigned long counter = 0UL;
    if(currentMillis > endTime) {
      counter = maxValue;
    } else if(currentMillis > startTime) {
      counter = (currentMillis-startTime) / MILLIS_PER_INCREMENT;
    }
    
    if (displayIndex == 0) {
      digit = (int)(counter % 10);
    }
    else if (displayIndex == 1) {
      if (counter < 10UL) {
        doPrint = false;
      } else {
        digit = (int)((counter / 10) % 10);
      }
    }
    else if (displayIndex == 2) {
      if(counter < 100UL) {
        doPrint = false;
      } else {
        digit =  (int)(counter / 100);
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
  return currentMillis >= startTime && currentMillis <= endTime;
}

