#pragma once
#include <Arduino.h>
#include "BreadboardGamepad.h"

#define PIN_COMMON 0
#define PIN_LED 22

#define LED_OFF 1
#define LED_ON 0

#define PRESSED 0

class Board
{
  public:
  int counter = 0;
  BluetoothGamepad* gamepad;

  Board(BluetoothGamepad* _gamepad)
  {
    gamepad = _gamepad;
  }

  /// @brief Called on startup to configure the LED, Serial port & BLE game controller interface
  void init()
  {
    // LED pin mode to output
    pinMode(PIN_LED, OUTPUT);

    // Common pin acts as ground
    pinMode(PIN_COMMON, OUTPUT);
    digitalWrite(PIN_COMMON, 0);

    // Configure the serial port so we can print debug messages
    Serial.begin(115200);
    Serial.println("Hello!");

    // Use chip's unique ID to set the bluetooth device name
    char deviceName[32] = {0};
    sprintf(deviceName, "Gamepad %08X", ESP.getEfuseMac());
    Serial.printf("Starting %s\n", deviceName);

    std::string nameString(deviceName);
    gamepad->begin(nameString);

    // Flash on startup
    for (int i=0; i<10; i++)
    {
      digitalWrite(PIN_LED, LED_OFF);
      delay(100);
      digitalWrite(PIN_LED, LED_ON);
      delay(100);
    }
  }

  /// @brief Check if a button is pressed
  /// @param pin Pin GPIO to check
  /// @return True if pressed
  bool read(int pin)
  {
    return digitalRead(pin) == PRESSED;
  }

  /// @brief Update the LED based on current system state, add a 10ms delay
  void updateLed()
  {
    // Turn on LED when button is pressed
    if (gamepad->getAnyPressed())
    {
      digitalWrite(PIN_LED, LED_ON);
    }
    else
    {
      digitalWrite(PIN_LED, LED_OFF);
    }
    delay(9);

    // Flash led when connected
    counter = counter + 1;
    if (counter > 50)
    {
      counter = 0;
      if (gamepad->isConnected())
      {
        digitalWrite(PIN_LED, LED_ON);
      }
    }
    delay(1);
  }
};
