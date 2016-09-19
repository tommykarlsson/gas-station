#include <Arduino.h>
#include "SevenSegmentArrayDisplay.h"

SevenSegmentArrayDisplay::SevenSegmentArrayDisplay() {
  lastUpdate = 0UL;
  maxValue = 0UL;
  lastDisplayIndex = 0;
}

void SevenSegmentArrayDisplay::setup(int maxVal)
{
  maxValue = maxVal;

  for (int i = 0; i < 7; i++) {
    pinMode(SEVEN_SEG_PINS[i], OUTPUT);
    digitalWrite(SEVEN_SEG_PINS[i], LOW);
  }
  for (int i = 0; i < DISPLAY_COUNT; i++) {
    pinMode(SEVEN_SEG_CATHODES[i], OUTPUT);
    digitalWrite(SEVEN_SEG_CATHODES[i], HIGH);
  }
}

//void SevenSegmentArrayDisplay::shutdown() {
//  for (int i = 0; i < DISPLAY_COUNT; i++) {
//    digitalWrite(SEVEN_SEG_CATHODES[i], HIGH);
//  }
//}

int SevenSegmentArrayDisplay::calcCounter(unsigned long startTime, unsigned long currentMillis, unsigned long endTime) {
  int counter = 0;
  if (currentMillis > startTime) {
    counter = (currentMillis - startTime) / MILLIS_PER_INCREMENT;
  }
  return constrain(counter, 0, maxValue);

  //  unsigned long counter = 0UL;
  //  if (currentMillis > endTime) {
  //    counter = maxValue;
  //  } else if (currentMillis > startTime) {
  //    counter = (currentMillis - startTime) / MILLIS_PER_INCREMENT;
  //  }
  //  return counter;
}

bool SevenSegmentArrayDisplay::update(unsigned long startTime)
{
  unsigned long currentMillis = millis();
  unsigned long endTime = startTime + (maxValue * (long)MILLIS_PER_INCREMENT);

  if ((currentMillis - lastUpdate) > UPDATE_INTERVAL) // time to update
  {
    lastUpdate = currentMillis;

    int displayIndex = lastDisplayIndex - 1;
    if (displayIndex < 0) {
      displayIndex = 2;
    }

    //calculate counter
    int counter = calcCounter(startTime, currentMillis, endTime);

    //calculate digit to print
    bool doPrint = true;
    int digit;
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
      if (counter < 100) {
        doPrint = false;
      } else {
        digit = counter / 100;
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
  return (currentMillis >= startTime) && (currentMillis <= endTime);
}

