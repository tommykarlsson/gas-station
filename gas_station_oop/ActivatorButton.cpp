#include <Arduino.h>
#include "ActivatorButton.h"

int buttonPin;
volatile bool activated = false;
volatile unsigned long activationTime = 0;

//pin must be 2 or 3 on arduino uno
ActivatorButton::ActivatorButton(int pin) {
  buttonPin = pin;
}

void onPinChange() {
  if (millis() > 100) { //seems like we get interrupts randomly during startup, so wait a tiny bit before we act on interrupts
    if (!activated) {
      activationTime = millis();
    }
    activated = true;
  }
}

void ActivatorButton::setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), onPinChange, CHANGE);
  activated = false;
}

bool ActivatorButton::isActivated() {
  return activated;
}

unsigned long ActivatorButton::getActivationTime() {
  return activationTime;
}



