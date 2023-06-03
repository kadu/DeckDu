#pragma once

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setupKeyboard() {
  bleKeyboard.setName("DeckDU v0.1");
  bleKeyboard.set_version(1);
  bleKeyboard.begin();
  bleKeyboard.setBatteryLevel(100);
}

bool isKeyBoardConnected() {
  return bleKeyboard.isConnected();
}