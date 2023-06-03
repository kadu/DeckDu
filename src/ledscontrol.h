#pragma once

#include <FastLED.h>

#define NUM_LEDS 2
#define DATA_PIN 4

// Define the array of leds
CRGB leds[NUM_LEDS];

void setupLeds() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(10);

  leds[0] = CRGB::Red;
  leds[1] = CRGB::Blue;
  FastLED.show();
}

void setLed(int ledNum, CRGB color) {
  leds[ledNum] = color;
  FastLED.show();
}