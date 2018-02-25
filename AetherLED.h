/*
  AetherLED.h - Library for running FastLED code Circuit Circus' aether installation
  Created by Jesper H. Fogh, February 25th 2018
*/

#ifndef AetherLED_h
#define AetherLED_h

#include "Arduino.h"
#include "FastLED.h"

class AetherLED {
  public:
    AetherLED(int pin, int numLeds);
    void turnOffLeds();
    void setLEDHSV(int ledIndex, CHSV color);
    void setSnakeSpeed(int newSpeed);
    void setSnakeIndex(int newIndex);
    void setSnakeDirection(int newDirection);
    void runSnakeAnimation(CHSV color, bool shouldLoop, bool shouldFill);
   
  private:
  	static const int _NUM_LEDS = 61;
  	CRGB _leds[_NUM_LEDS];
	CHSV _ledsHSV[_NUM_LEDS];

	// Snake settings
	unsigned int _snakeIndex = 0;
	int _snakeDirection = +1;
    long _snakeTimer;
    long _snakeTimerLength;
};

#endif