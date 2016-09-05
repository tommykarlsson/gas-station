//pins for segments on the 7 segment displays

// - A -
// F   B
// | G |
// E   C
// - D -


// pin numbers correspoing to segments A,B,C,D,E,F,G
const int SEVEN_SEG_PINS[] = {1, 2, 3, 4, 5, 6, 7};

const int SEVEN_SEG_PIN_STATES[][7] = {
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

const int DISPLAY_DELAY = 500;
const int DISPLAY_COUNT = 3;
const int SEVEN_SEG_CATHODES[] = {11, 12, 13};

const int SPEAKER_OUT = 9;


void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(SEVEN_SEG_PINS[i], OUTPUT);
    digitalWrite(SEVEN_SEG_PINS[i], LOW);
  }
  for (int i = 0; i < DISPLAY_COUNT; i++) {
    pinMode(SEVEN_SEG_CATHODES[i], OUTPUT);
    digitalWrite(SEVEN_SEG_CATHODES[i], LOW);
  }

  pinMode(SPEAKER_OUT, OUTPUT);
}

void loop() {
  
  long counter = min(999, millis()/100);
  int hundreds = counter / 100;
  int tens = (counter / 10) % 10;
  int ones = counter % 10;
  
    
  outputNumber(1, ones);
  //playTone(DISPLAY_DELAY);
  if(hundreds > 0 || tens > 0) {
    outputNumber(2, tens);  
  }
  //playTone(DISPLAY_DELAY);
  if(hundreds > 0) {
    outputNumber(3, hundreds);  
  }
  //playTone(DISPLAY_DELAY);
}

void playTone(int duration) {
  int endtime = millis() + duration;
  while(millis() < endtime) {
    digitalWrite(SPEAKER_OUT,HIGH);
    delay(10);
    digitalWrite(SPEAKER_OUT,LOW);
    delay(10);
  }
}

/// number - number (0-9) to show on display
/// displayIndex - index (1-DISPLAY_COUNT) of 7-segment display to use
void outputNumber(int displayIndex, int number) {
  //disable all cathodes
  for (int i = 0; i < DISPLAY_COUNT; i++) {
    digitalWrite(SEVEN_SEG_CATHODES[i], HIGH);
  }

  //set states of each segment pin
  for (int i = 0; i < 7; i++) {
    digitalWrite(SEVEN_SEG_PINS[i], SEVEN_SEG_PIN_STATES[number][i]);
  }

  //enable correct cathode
  digitalWrite(SEVEN_SEG_CATHODES[displayIndex-1], LOW);
}


