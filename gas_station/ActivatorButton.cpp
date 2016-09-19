#include <Arduino.h>
#include "ActivatorButton.h"

static int buttonPin;
static volatile bool activated = false;
static volatile unsigned long activationTime = 0UL;

//pin must be 2 or 3 on arduino uno
ActivatorButton::ActivatorButton(int pin) {
  buttonPin = pin;
  activated = false;
  activationTime = 0UL;
}

static void onPinChange() {
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
  activationTime = 0UL;
}

bool ActivatorButton::isActivated() {
  return activated;
}

unsigned long ActivatorButton::getActivationTime() {
  return activationTime;
}



