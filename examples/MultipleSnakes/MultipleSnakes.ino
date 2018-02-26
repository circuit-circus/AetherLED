#include "AetherLED.h"

#define DATA_PIN_ONE 5
#define NUM_LEDS_ONE 61

#define DATA_PIN_TWO 6
#define NUM_LEDS_TWO 61

AetherLED ringOne;
AetherLED ringTwo;

CHSV ledColorOne = CHSV(0, 220, 255);
CHSV ledColorTwo = CHSV(95, 220, 255);

void setup() {
  // Sanity check, to protect LEDs and Arduino
  delay(2000);
  Serial.begin(9600);

  ringOne.attach<DATA_PIN_ONE>(NUM_LEDS_ONE);
  ringOne.setSnakeSpeed(30);
  ringOne.setSnakeIndex(30);
  ringOne.setSnakeDirection(+1);

  ringTwo.attach<DATA_PIN_TWO>(NUM_LEDS_TWO);
  ringOne.setSnakeSpeed(15);
  ringOne.setSnakeIndex(0);
  ringOne.setSnakeDirection(-1);
}

void loop() {
  ringOne.runSnakeAnimation(ledColorOne, true, false, true);
  ringTwo.runSnakeAnimation(ledColorTwo, true, true, false);
  FastLED.show();
}