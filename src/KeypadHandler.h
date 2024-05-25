#ifndef KEYPADHANDLER_H
#define KEYPADHANDLER_H

#include <Keypad.h>
#include "PageManager.h"
#include "LCDManager.h"

// Keypad Setup
extern const byte KEYPAD_ROWS;
extern const byte KEYPAD_COLS;
extern char keys[4][4];
extern byte rowPins[4];
extern byte colPins[4];
extern Keypad customKeypad;

void handleKeypad(LCDManager &lcdManager, PageManager &pageManager);

#endif
