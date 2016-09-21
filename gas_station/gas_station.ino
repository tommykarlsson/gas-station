#include "SevenSegmentArrayDisplay.h"
#include "ActivatorButton.h"
#include <avr/sleep.h>

class Speaker {
    const int SPEAKER_OUT = 3;
    const int FREQUENCY_HZ = 300;
    boolean isRunning;
    PumpCoordinator *coord;

  public:
    Speaker(PumpCoordinator *coordinator) {
      isRunning = false;
      coord = coordinator;
    }

    void setup()
    {
      pinMode(SPEAKER_OUT, OUTPUT);
    }

    void update() {
      if (coord->isRunning()) {
        start();
      }
      else {
        stop();
      }
    }

    void start()
    {
      if (!isRunning) {
        tone(SPEAKER_OUT, FREQUENCY_HZ);
        isRunning = true;
      }
    }

    void stop() {
      if (isRunning) {
        noTone(SPEAKER_OUT);
        isRunning = false;
      }
    }

};

PumpCoordinator coordinator;
SevenSegmentArrayDisplay disp(&coordinator);
Speaker speaker(&coordinator);
ActivatorButton button(&coordinator, 2);
boolean donePumping = false;

void setup() {
  randomSeed(analogRead(0));
  disp.setup();
  speaker.setup();
  button.setup();
}

void loop() {

  if (coordinator.isActivated()) {
    disp.update();
    speaker.update();

    if (millis() > 60000) { // shutdown 1 minute after system starts
      shutdown();
    }
  }
}

//emulate shutdown by going into an eternal extreme power saving mode
void shutdown() {
  speaker.stop();
  disp.stop();
  cli(); // disable global interrupts
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_bod_disable();
  sleep_mode();
}

