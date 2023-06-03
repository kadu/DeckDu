#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <BleKeyboard.h>
#include <FastLED.h>
#include "webserver.h"
#include "secrets.h"
#include "wificonnection.h"
#include "deckdukeyboard.h"
#include "ledscontrol.h"

void setup()
{
  Serial.begin(115200);

  setupLeds();
  setupWifi();
  setupWeb();
  setupKeyboard();
}

void loop()
{
  if (isKeyBoardConnected())
  {
    setLed(0, CRGB::Green);
  }
  else
  {
    setLed(0, CRGB::Yellow);
  }
}