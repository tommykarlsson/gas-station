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

void setup() {
  randomSeed(analogRead(0));
  disp.setup(random(50,251));
  speaker.setup();
  button.setup();
}

void loop() {
  if (button.isActivated()) {
    unsigned long pumpStartTime = button.getActivationTime() + 1000UL;
	  bool isPumping = disp.update(pumpStartTime);
    if (isPumping) {
      speaker.start();
    } else {
      speaker.stop();
    }
    if(millis() > pumpStartTime + 60000UL) { // shutdown 1 minute after pump starts
      //shutdown();
    }
  }
}

//emulate shutdown by going into an eternal extreme power saving mode
void shutdown() {
  disp.shutdown();
  speaker.stop();
  cli(); // disable global interrupts
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_bod_disable();
  sleep_mode();
}

