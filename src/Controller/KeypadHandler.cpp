#include "KeypadHandler.h"
#include "../GlobalDeclarations.h"

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'.', '0', '<', '>'}};
byte rowPins[KEYPAD_ROWS] = {9, 8, 7, 6};
byte colPins[KEYPAD_COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

void handleKeypad()
{
    char key = customKeypad.getKey();
    if (key)
    {
        switch (pageManager.getPageState())
        {
        case PageManager::MENU:
            pageManager.handleMenuSelection(key);
            break;
        case PageManager::NEW_EXPERIMENT:
            pageManager.handleNewExperimentSelection(key);
            break;
        case PageManager::SAVED_EXPERIMENT:
            pageManager.handleSavedExperimentSelection(key);
            break;
        case PageManager::RUN_EXPERIMENT_NOTRUN:
            pageManager.handleRunExperimentSelection(key);
            break;
        case PageManager::EDIT_EXPERIMENT:
            pageManager.handleEditExperimentSelection(key);
            break;
        case PageManager::DEL_EXPERIMENT:
            pageManager.handleDelExperimentSelection(key);
            break;
        }
    }
}
