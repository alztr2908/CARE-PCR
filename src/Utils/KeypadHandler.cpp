#include "KeypadHandler.h"
#include "PageManager.h"

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'.', '0', '<', '>'}};
byte rowPins[KEYPAD_ROWS] = {11, 10, 9, 8};
byte colPins[KEYPAD_COLS] = {7, 6, 5, 4};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

void handleKeypad(LCDManager &lcdManager, PageManager &pageManager)
{
    char key = customKeypad.getKey();
    if (key)
    {
        pageManager.displayCurrentPage(lcdManager.getLCD(), key);
    }
}
