#include "SevenSegmentArrayDisplay.h"

class Speaker {
    const int SPEAKER_OUT = 3;

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

SevenSegmentArrayDisplay disp;
Speaker speaker;

void setup() {
  disp.setup();
  speaker.setup();
}

void loop() {
  disp.update();
  //speaker.update();
}
