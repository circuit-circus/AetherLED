#include "AetherLED.h"

#define DATA_PIN_ONE 5
#define NUM_LEDS_ONE 61

AetherLED ringOne;

CHSV ledColor = CHSV(0, 220, 255);

void setup() {
  // Sanity check, to protect LEDs and Arduino
  delay(2000);
  Serial.begin(9600);

  ringOne.attach<DATA_PIN_ONE>(NUM_LEDS_ONE);
  ringOne.setSnakeSpeed(30);
  ringOne.setSnakeIndex(30);
  ringOne.setSnakeDirection(+1);
}

void loop() {
  ringOne.runSnakeAnimation(ledColor, true, true, false);
  FastLED.show();
}