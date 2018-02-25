#include "AetherLED.h"

#define DATA_PIN_ONE 5
#define NUM_LEDS_ONE 61

AetherLED ringOne(DATA_PIN_ONE, NUM_LEDS_ONE);

CHSV ledColor = CHSV(0, 180, 255);

void setup() {
  // Sanity check, to protect LEDs and Arduino
  delay(2000);
  Serial.begin(9600);

  ringOne.setSnakeSpeed(30);
  ringOne.setSnakeIndex(55);
  ringOne.setSnakeDirection(-1);
}

void loop() {
  //ringOne.setBackgroundColor(CHSV(96, 255, 120));
  ringOne.runSnakeAnimation(ledColor, true, false, true);
  FastLED.show();
}