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
  ringOne.setSnakeSpeed(30);
  ringOne.setSnakeIndex(30);
}

void loop() {
  ringOne.runSnakeAnimation(CHSV(120, 255, 255), true, true);
  FastLED.show();
}