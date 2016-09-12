#include "SevenSegmentArrayDisplay.h"
#include "ActivatorButton.h"
#include <avr/sleep.h>

class Speaker {
  const int SPEAKER_OUT = 3;
  const int FREQUENCY_HZ = 300;
  bool isRunning = false;

  public:
    Speaker() {}

    void setup()
    {
      pinMode(SPEAKER_OUT, OUTPUT);
    }

    void start()
    {
      if(!isRunning) {
        tone(SPEAKER_OUT, FREQUENCY_HZ);
        isRunning = true;
      }
    }

    void stop() {
      if(isRunning) {
        noTone(SPEAKER_OUT);
        isRunning = false;
      }
    }

};

SevenSegmentArrayDisplay disp;
Speaker speaker;
ActivatorButton button(2);
bool donePumping = false;

void setup() {
  randomSeed(analogRead(0));
  disp.setup(random(50,251));
  speaker.setup();
  button.setup();
}

void loop() {
  if (button.isActivated()) {
    long pumpStartTime = button.getActivationTime() + 1000;
    if (!donePumping && millis() > pumpStartTime) {
      //first update 1 second after button activated
      speaker.start();
    }
    donePumping = disp.update(pumpStartTime);
    if(donePumping) {
      speaker.stop();
    }
    if(millis() > pumpStartTime + 300000) { // shutdown 5 minutes after pump starts
      shutdown();
    }
  }
}

//emulate shutdown by going into an eternal extreme power saving mode
void shutdown() {
  cli(); // disable global interrupts
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_bod_disable();
  sleep_mode();
}

