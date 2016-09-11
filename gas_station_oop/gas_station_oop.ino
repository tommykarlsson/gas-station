#include "SevenSegmentArrayDisplay.h"
#include "ActivatorButton.h"

class Speaker {
  const int SPEAKER_OUT = 9;

  public:
    Speaker() {}

    void setup()
    {
      pinMode(SPEAKER_OUT, OUTPUT);
    }

    void start()
    {
      tone(SPEAKER_OUT, 150);
    }

    void stop() {
      noTone(SPEAKER_OUT);
    }

};

bool isRunning = false;
SevenSegmentArrayDisplay disp;
Speaker speaker;
ActivatorButton button(2);

void setup() {
  disp.setup();
  speaker.setup();
  button.setup();
}

void loop() {
  if (button.isActivated()) {
    if (!isRunning) {
      //first update after button activated
      //speaker.start();
      isRunning = true;
    }
    disp.update(button.getActivationTime());
  }
}
