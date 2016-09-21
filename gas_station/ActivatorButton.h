#include "PumpCoordinator.h"

class ActivatorButton {

  public:
    ActivatorButton(PumpCoordinator *coordinator, int pin);
    void setup();
    boolean isActivated();
    long getActivationTime();
    long getPumpStartTime();
};
