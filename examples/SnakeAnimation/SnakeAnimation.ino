#include <AetherLED.h>

#define NUM_LEDS 61
#define DATA_PIN 5
#define CHIPSET WS2812B
#define COLOR_ORDER GRB

AetherLED ringOne(DATA_PIN, NUM_LEDS);

void setup() {
  // Sanity check, to protect LEDs and Arduino
  delay(2000);
  Serial.begin(9600);
  ringOne.setSnakeSpeed(500);
  ringOne.setSnakeIndex(55);
  ringOne.setSnakeDirection(+1);
}

void loop() {
  ringOne.runSnakeAnimation(CHSV(120, 255, 255), false, false);
  FastLED.show();
}