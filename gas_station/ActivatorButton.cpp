#include <Arduino.h>
#include "ActivatorButton.h"

int buttonPin;
volatile boolean activated = false;
PumpCoordinator *coord;

//pin must be 2 or 3 on arduino uno
ActivatorButton::ActivatorButton(PumpCoordinator *coordinator, int pin) {
  buttonPin = pin;
  coord = coordinator;
  activated = false;
}

void onPinChange() {
  if (millis() > 100) { //seems like we get interrupts randomly during startup, so wait a tiny bit before we act on interrupts
    if (!activated) {
      coord->activate();
    }
    activated = true;
  }
}

void ActivatorButton::setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), onPinChange, CHANGE);
  activated = false;
}




