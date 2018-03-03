/*
  AetherLED.h - Library for running FastLED code Circuit Circus' aether installation
  Created by Jesper H. Fogh, February 25th 2018
*/

#ifndef AetherLED_h
#define AetherLED_h

#include "Arduino.h"
#include "FastLED.h"

#define CHIPSET WS2812B
#define COLOR_ORDER GRB

template<int DATA_PIN, int NUM_LEDS>
class AetherLED {
  private:
    int _PIN = DATA_PIN;
    int _NUM_LEDS = NUM_LEDS;

    // To use HSV in FastLED, it seems you have to maintain two arrays:
    // one for the HSV colors and one for the LEDS themselves
    // It also seems idiotic, but hey, it works! ¯\_(ツ)_/¯
    CRGB _leds[NUM_LEDS];
    CHSV _ledsHSV[NUM_LEDS];

    CHSV _bgColor = CHSV(160, 255, 255);

    // Snake settings
    unsigned int _snakeIndex = 0;
    int _snakeDirection = +1;
    long _snakeTimer;
    long _snakeTimerLength = 50;

    // Helper methods
    void drawBackground() {
      for(int i = 0; i < _NUM_LEDS; i++) {
        _ledsHSV[i] = _bgColor;
        _leds[i] = _ledsHSV[i];
      }
    }

    // Snake methods
    void determineNextIndex(bool shouldLoop) {
      // Figure out what the index should be 
        if(_snakeIndex <= 0) {
          if(_snakeDirection == -1) {
            if(shouldLoop == true) {
              _snakeIndex = _NUM_LEDS;
            }
            else {
              _snakeDirection = +1;
              _snakeIndex = 0;
            }
          }
        }
        if(_snakeIndex >= _NUM_LEDS) {
          if(_snakeDirection == +1) {
            if(shouldLoop == true) {
              _snakeIndex = 0;
            }
            else {
              _snakeDirection = -1;
              _snakeIndex = _NUM_LEDS;
            }
          }
        }
        _snakeIndex += _snakeDirection;
    }

  public:
    // Helper methods
    void attach() {
        FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
    };

    void setSingleHSV(int ledIndex, CHSV color) {
      _ledsHSV[ledIndex] = color;
      _leds[ledIndex] = _ledsHSV[ledIndex];
    }

    void turnOffLeds() {
      for(int i = 0; i < _NUM_LEDS; i++) {
        _ledsHSV[i].value = 0;
        _leds[i] = _ledsHSV[i];
      }
    }

    void setBackgroundColor(CHSV bgColor) {
      _bgColor = bgColor;
    }

    // Snake methods
    void setSnakeSpeed(int newSpeed) {
      _snakeTimerLength = newSpeed;
    }

    void setSnakeIndex(int newIndex) {
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

    int getSnakeIndex() {
      return _snakeIndex;
    }

    void setSnakeDirection(int newDirection) {
      // Set newDirection to 0 to stop the snake
      if(newDirection < 2 && newDirection > -2) {
        _snakeDirection = newDirection;
      }
    }

    void runSnakeAnimation(CHSV color, bool shouldLoop, bool shouldFill, bool shouldDrawBg) {
      if(millis() > _snakeTimer + _snakeTimerLength && _snakeDirection != 0) {
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
};

#endif