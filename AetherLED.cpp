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
void AetherLED::setSnakeSpeed(int newSpeed) {
  _snakeTimerLength = newSpeed;
}

void AetherLED::setSnakeIndex(int newIndex) {
  if(newIndex > _NUM_LEDS) {
    _snakeIndex = _NUM_LEDS;
  }
  else if(newIndex <= 0) {
    _snakeIndex = 0;
  }
  else {
    _snakeIndex = newIndex;
  }
}

void AetherLED::runSnakeAnimation(CHSV color, bool shouldLoop, bool shouldFill) {
  if(millis() > _snakeTimer + _snakeTimerLength) {
    _snakeTimer = millis();
    CHSV _thisColor = color;

    if(_snakeIndex <= 0) {
      _snakeIndex = 0;
      _snakeDirection = +1;
    }
    if(_snakeIndex >= _NUM_LEDS) {
      if(shouldLoop == true) {
        _snakeIndex = 0;
      }
      else {
        _snakeIndex = _NUM_LEDS;
        _snakeDirection = -1;
      }
    }
    _snakeIndex = _snakeIndex + _snakeDirection;

    if(shouldFill == false) {
      turnOffLeds();
    }
    else {
      // Should we clear this pixel? If not, then we just rely on the provided color.value
      if(_ledsHSV[_snakeIndex].value > 0) {
        _thisColor.value = 0;
      }
    }

    setLEDHSV(_snakeIndex, _thisColor);
  }
}