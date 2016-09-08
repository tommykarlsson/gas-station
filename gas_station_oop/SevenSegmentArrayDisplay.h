class SevenSegmentArrayDisplay {

  public:
    void setup();
    void update(unsigned long startTime);
  private:
    //pins for segments on the 7 segment displays

    // - A -
    // F   B
    // | G |
    // E   C
    // - D -


    // pin numbers correspoing to segments A,B,C,D,E,F,G
    const int SEVEN_SEG_PINS[7] = {3, 4, 5, 6, 7, 8, 9};

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

    const unsigned long updateInterval = 1;
    unsigned long lastUpdate;         // last time of update

    int lastDigit = 0;
    int lastDisplayIndex = 0;         // current enabled display
};
