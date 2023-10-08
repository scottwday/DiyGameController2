#include <Arduino.h>
#include "BreadboardGamepad.h"
#include "Board.h"

BluetoothGamepad gamepad;
Board board(&gamepad);

#define PIN_COMMON 0
#define PIN_LEFT 13
#define PIN_RIGHT 18
#define PIN_UP 16
#define PIN_DOWN 17
#define PIN_A 19
#define PIN_B 23
#define PIN_SELECT 15
#define PIN_START 4


void setup() {
  // Runs once at startup to configure the board

  board.init("Who am I?");

  // Configure GPIO pin inputs
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_SELECT, INPUT_PULLUP);
  pinMode(PIN_START, INPUT_PULLUP);
}

void loop() {
  // put your main code here to run repeatedly about 100 times per second

  gamepad.set_up(board.read(PIN_UP));
  gamepad.set_down(board.read(PIN_DOWN));
  gamepad.set_left(board.read(PIN_LEFT));
  gamepad.set_right(board.read(PIN_RIGHT));

  gamepad.set_a(board.read(PIN_A));
  gamepad.set_b(board.read(PIN_B));

  gamepad.set_select(board.read(PIN_SELECT));
  gamepad.set_start(board.read(PIN_START));

  board.updateLed();
}
