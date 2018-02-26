#include "AetherLED.h"

// Constructor
// For more info on this constructor, see: https://stackoverflow.com/questions/1423696/how-to-initialize-a-const-field-in-constructor
AetherLED::AetherLED() {}

// Helper methods
void AetherLED::setSingleHSV(int ledIndex, CHSV color) {
  _ledsHSV[ledIndex] = color;
  _leds[ledIndex] = _ledsHSV[ledIndex];
}

void AetherLED::turnOffLeds() {
  for(int i = 0; i < _NUM_LEDS; i++) {
    _ledsHSV[i].value = 0;
    _leds[i] = _ledsHSV[i];
  }
}

void AetherLED::setBackgroundColor(CHSV bgColor) {
  _bgColor = bgColor;
}

void AetherLED::drawBackground() {
  for(int i = 0; i < _NUM_LEDS; i++) {
    _ledsHSV[i] = _bgColor;
    _leds[i] = _ledsHSV[i];
  }
}

// Snake methods
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

int AetherLED::getSnakeIndex() {
  return _snakeIndex;
}

void AetherLED::setSnakeDirection(int newDirection) {
  // Set newDirection to 0 to stop the snake
  if(newDirection < 2 && newDirection > -2) {
    _snakeDirection = newDirection;
  }
}

void AetherLED::determineNextIndex(bool shouldLoop) {
  // Figure out what the index should be 
    if(_snakeIndex <= 0) {
      _snakeIndex = 0;
      _snakeDirection = +1;
    }

    if(_snakeIndex >= _NUM_LEDS) {
      if(shouldLoop == true) {
        _snakeIndex = 0;
        _snakeDirection = +1;
      }
      else {
        _snakeIndex = _NUM_LEDS;
        _snakeDirection = -1;
      }
    }
    _snakeIndex += _snakeDirection;
}

void AetherLED::runSnakeAnimation(CHSV color, bool shouldLoop, bool shouldFill, bool shouldDrawBg) {
  if(millis() > _snakeTimer + _snakeTimerLength) {
    _snakeTimer = millis();
    CHSV _thisColor = color;

    determineNextIndex(shouldLoop);

    if(shouldFill == false) {
      turnOffLeds();
      if(shouldDrawBg) {
        drawBackground();
      }
    }
    else {
      // Should we clear this pixel? If not, then we just rely on the provided color.value
      if(_ledsHSV[_snakeIndex].value > 0) {
        _thisColor.value = 0;
      }
    }

    setSingleHSV(_snakeIndex, _thisColor);
  }
}