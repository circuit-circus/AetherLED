#include <AetherLED.h>

#define DATA_PIN_ONE 6
#define NUM_LEDS_ONE 59

AetherLED<DATA_PIN_ONE, NUM_LEDS_ONE> ringOne;

CHSV ledColor = CHSV(20, 220, 255);

void setup() {
  // Sanity check, to protect LEDs and Arduino
  delay(2000);

  ringOne.attach();
  ringOne.setSnakeSpeed(30);
  ringOne.setSnakeIndex(0);
  ringOne.setSnakeDirection(-1);
}

void loop() {
  ringOne.runSnakeAnimation(ledColor, true, true, false);
  FastLED.show();
}