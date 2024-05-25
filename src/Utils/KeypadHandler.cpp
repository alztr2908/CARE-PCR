#include "KeypadHandler.h"

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
        if (key == '>')
        {
            pageManager.nextSubpage();
        }
        else if (key == '<')
        {
            pageManager.previousSubpage();
        }
        else
        {
            switch (key)
            {
            case 'A':
                pageManager.setPage("home");
                break;
            case 'B':
                pageManager.setPage("settings");
                break;
            case 'C':
                pageManager.setPage("info");
                break;
            }
        }
        pageManager.displayCurrentPage(lcdManager.getLCD());
    }
}
