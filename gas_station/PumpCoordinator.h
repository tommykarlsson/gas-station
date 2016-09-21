#ifndef PUMPCOORDINATOR
#define PUMPCOORDINATOR

class PumpCoordinator {

  public:
    PumpCoordinator();
    void activate();
    boolean isActivated();
    boolean isRunning();
    int getPumpedVolume();

  private:
    volatile long pumpStartTime;
    volatile long pumpStopTime;
    volatile int maxPumpVolume;
    volatile boolean isActive;
};

#endif

