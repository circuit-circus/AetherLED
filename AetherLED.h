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

class AetherLED {
  private:
    int _PIN;
    int _NUM_LEDS;

    // To use HSV in FastLED, it seems you have to maintain two arrays:
    // one for the HSV colors and one for the LEDS themselves
    // It also seems idiotic, but hey, it works! ¯\_(ツ)_/¯
    CRGB* _leds;
    CHSV* _ledsHSV;

    CHSV _bgColor = CHSV(160, 255, 255);

    // Snake settings
    unsigned int _snakeIndex = 0;
    int _snakeDirection = +1;
    long _snakeTimer;
    long _snakeTimerLength = 50;

    // Helper methods
    void drawBackground();

    // Snake methods
    void determineNextIndex(bool shouldLoop);

  public:
    // Constructor
    AetherLED();

    // Helper methods
    template<int DATA_PIN = 5>
    void attach(int numLeds) {
        _NUM_LEDS = numLeds;
        FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(_leds, _NUM_LEDS);
    };
    void setSingleHSV(int ledIndex, CHSV color);
    void turnOffLeds();
    void setBackgroundColor(CHSV bgColor);

    // Snake methods
    void setSnakeSpeed(int newSpeed);
    void setSnakeIndex(int newIndex);
    int getSnakeIndex();
    void setSnakeDirection(int newDirection);
    void runSnakeAnimation(CHSV color, bool shouldLoop, bool shouldFill, bool shouldDrawBg);
};

#endif