#include "PumpCoordinator.h"

class SevenSegmentArrayDisplay {

  public:
    SevenSegmentArrayDisplay(PumpCoordinator *coordinator);
    void setup();
    void update();
  private:
    //pins for segments on the 7 segment displays

    // - A -
    // F   B
    // | G |
    // E   C
    // - D -


    // pin numbers correspoing to segments A,B,C,D,E,F,G
    const int SEVEN_SEG_PINS[7] = {6, 5, 11, 10, 9, 7, 8};


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
    const int SEVEN_SEG_CATHODES[3] = {4, 12, 13};

    const long updateInterval = 3;
    long lastUpdate;         // last time of update

    int lastDisplayIndex = 0;         // current enabled display

    PumpCoordinator *coord;
};
