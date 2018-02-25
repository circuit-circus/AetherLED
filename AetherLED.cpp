#include "AetherLED.h"

#define CHIPSET WS2812B
#define COLOR_ORDER GRB

AetherLED::AetherLED(int pin, int numLeds) {
  FastLED.addLeds<CHIPSET, 5, COLOR_ORDER>(_leds, 61);
  _snakeTimerLength = 50;
}

// Helper functions
void AetherLED::setLEDHSV(int ledIndex, CHSV color) {
  _ledsHSV[ledIndex] = color;
  _leds[ledIndex] = _ledsHSV[ledIndex];
}

void AetherLED::turnOffLeds() {
  // Turn off all leds
  for(int i = 0; i < _NUM_LEDS; i++) {
    _ledsHSV[i].value = 0;
    _leds[i] = _ledsHSV[i];
  }
}

// Snake functions
void AetherLED::setSnakeSpeed(int timerSpeed) {
  _snakeTimerLength = timerSpeed;
}

void AetherLED::runSnakeAnimation(bool shouldLoop) {
  if(millis() > _snakeTimer + _snakeTimerLength) {
    _snakeTimer = millis();

    if(_snakeIndex <= 0) {
      _snakeIndex = 0;
      _shouldCountUp = true;
    }
    if(_snakeIndex >= _NUM_LEDS) {
      if(shouldLoop == true) {
        _snakeIndex = 0;
      }
      else {
        _snakeIndex = _NUM_LEDS;
        _shouldCountUp = false;
      }
    }

    if(_shouldCountUp == true) {
      _snakeIndex++;
    }
    else {
      _snakeIndex--;
    }

    turnOffLeds();
    setLEDHSV(_snakeIndex, CHSV(120, 255, 255));
  }
}