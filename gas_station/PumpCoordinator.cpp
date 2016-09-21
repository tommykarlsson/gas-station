#include <Arduino.h>
#include "PumpCoordinator.h"

PumpCoordinator::PumpCoordinator()
{
  maxPumpVolume = 0;
  pumpStartTime = 0;
  pumpStopTime = 0;
  isActive = false;
}

void PumpCoordinator::activate() {
  long currentMillis = millis();
  maxPumpVolume = random(50, 251);
  pumpStartTime = currentMillis + 1000;
  pumpStopTime = pumpStartTime + (maxPumpVolume * 100);
  isActive = true;
}

boolean PumpCoordinator::isActivated() {
  return isActive;
}

boolean PumpCoordinator::isRunning() {
  if (!isActive) {
    return false; //not activated yet
  }
  long currentMillis = millis();
  if (currentMillis >= pumpStartTime && currentMillis <= pumpStopTime) {
    return true;
  }
  else {
    return false;
  }
}

int PumpCoordinator::getPumpedVolume() {
  if (!isActive) {
    return 0;
  }
  long currentMillis = millis();
  if (currentMillis <= pumpStartTime) {
    return 0;
  }
  else if (currentMillis >= pumpStopTime) {
    return maxPumpVolume;
  }
  else {
    return (currentMillis - pumpStartTime) / 100;
  }
}

