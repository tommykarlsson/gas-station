class SevenSegmentArrayDisplay {

    //pins for segments on the 7 segment displays

    // - A -
    // F   B
    // | G |
    // E   C
    // - D -


    // pin numbers correspoing to segments A,B,C,D,E,F,G
    const int SEVEN_SEG_PINS[7] = {1, 2, 3, 4, 5, 6, 7};

    const int SEVEN_SEG_PIN_STATES[10][7] = {
      //A    B     C     D     E     F     G
      {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW }, // 0
      {LOW,  HIGH, HIGH, LOW,  LOW,  LOW,  LOW }, // 1
      {HIGH, HIGH, LOW,  HIGH, HIGH, LOW,  HIGH}, // 2
      {HIGH, HIGH, HIGH, HIGH, LOW,  LOW,  HIGH}, // 3
      {LOW , HIGH, HIGH, LOW , LOW,  HIGH, HIGH}, // 4
      {HIGH, LOW,  HIGH, HIGH, LOW,  HIGH, HIGH}, // 5
      {HIGH, LOW,  HIGH, HIGH, HIGH, HIGH, HIGH}, // 6
      {HIGH, HIGH, HIGH, LOW,  LOW,  LOW,  LOW }, // 7
      {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, // 8
      {HIGH, HIGH, HIGH, HIGH, LOW,  HIGH, HIGH}, // 9
    };

    const int DISPLAY_COUNT = 3;
    const int SEVEN_SEG_CATHODES[3] = {11, 12, 13};

    int lastNumber = 0;
    int lastDisplayIndex = 0;      // current enabled display
    unsigned long updateInterval = 5;       // interval between updates
    unsigned long lastUpdate; // last update of position

  public:
    SevenSegmentArrayDisplay() {}

    void setup()
    {
      for (int i = 0; i < 7; i++) {
        pinMode(SEVEN_SEG_PINS[i], OUTPUT);
        digitalWrite(SEVEN_SEG_PINS[i], LOW);
      }
      for (int i = 0; i < DISPLAY_COUNT; i++) {
        pinMode(SEVEN_SEG_CATHODES[i], OUTPUT);
        digitalWrite(SEVEN_SEG_CATHODES[i], HIGH);
      }
      lastUpdate = millis();
    }

    void update()
    {
      unsigned long currentMillis = millis();
      if ((currentMillis - lastUpdate) > updateInterval) // time to update
      {
        lastUpdate = currentMillis;

        int displayIndex = lastDisplayIndex - 1;
        if (displayIndex < 0) {
          displayIndex = 2;
        }

        //calc number to print
        bool doPrint = true;
        int number;
        long counter = min(999, currentMillis / 100);
        if (displayIndex == 0) {
          number = counter % 10;
        }
        else if (displayIndex == 1) {
          number = (counter / 10) % 10;
          if (lastNumber == 0 && number == 0) {
            doPrint = false;
          }
        }
        else if (displayIndex == 2) {
          number =  counter / 100;
          if (number == 0) {
            doPrint = false;
          }
        }

        //disable previous cathode
        digitalWrite(SEVEN_SEG_CATHODES[lastDisplayIndex], HIGH);

        lastNumber = number;
        lastDisplayIndex = displayIndex;

        if (doPrint) {
          //set states of each segment pin
          for (int i = 0; i < 7; i++) {
            digitalWrite(SEVEN_SEG_PINS[i], SEVEN_SEG_PIN_STATES[number][i]);
          }

          //enable current cathode
          digitalWrite(SEVEN_SEG_CATHODES[displayIndex], LOW);
        }
      }
    }
};

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
