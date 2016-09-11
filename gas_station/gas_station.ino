#include "SevenSegmentArrayDisplay.h"
#include "ActivatorButton.h"

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
    long pumpStartTime = button.getActivationTime() + 1000;
    if (millis() > pumpStartTime) {
      //first update 1 second after button activated
      speaker.start();
    }
    disp.update(pumpStartTime);
  }
}
