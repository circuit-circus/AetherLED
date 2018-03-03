#include <AetherLED.h>

#define DATA_PIN_ONE 6
#define NUM_LEDS_ONE 90

#define DATA_PIN_TWO 7
#define NUM_LEDS_TWO 90

AetherLED<DATA_PIN_ONE, NUM_LEDS_ONE> ringOne;
AetherLED<DATA_PIN_TWO, NUM_LEDS_TWO> ringTwo;

CHSV ledColorOne = CHSV(0, 220, 255);
CHSV ledColorTwo = CHSV(95, 220, 255);

void setup() {
  // Sanity check, to protect LEDs and Arduino
  delay(2000);

  ringOne.attach();
  ringOne.setSnakeSpeed(30);
  ringOne.setSnakeIndex(30);
  ringOne.setSnakeDirection(+1);

  ringTwo.attach();
  ringOne.setSnakeSpeed(15);
  ringOne.setSnakeIndex(0);
  ringOne.setSnakeDirection(-1);
}

void loop() {
  ringOne.runSnakeAnimation(ledColorOne, true, false, true);
  ringTwo.runSnakeAnimation(ledColorTwo, true, true, false);
  FastLED.show();
}