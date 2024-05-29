#include "EditExperimentPage.h"
#include "GlobalDeclarations.h"

void displayEditExperiment(char key)
{
    const String editOperationList[6] = {"Heated Lid", "Initial Step", "Cycles", "Step 1", "Step 2", "Step 3"};
    const String editOperationParams[2] = {"C- ", "T- "};

    int currentScreenIndex = pageManager.getCurrentSubpage();
    int currentAnswerField = pageManager.getCurrentAnswerField();

    /* Start here */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord(pageManager.currentProgName);
    lcd.printWord("(C-Temp T-Time)");

    // Track thermocyclerArray Index
    lcd.setCursor(19, 0);
    lcd.printWord(String(pageManager.currentThermocyclerArrayIndex));

    lcd.setCursor(2, 1);
    lcd.printWord(editOperationList[currentScreenIndex]);

    switch (currentScreenIndex)
    {
    // Heated Lid - Temp
    case 0:
        lcd.setCursor(4, 2);
        lcd.printWord(editOperationParams[0]);
        lcd.setCursor(7, 2);
        changeOption(key, pageManager.currentStringFirstVal);
        lcd.printWord(pageManager.currentStringFirstVal);
        break;
    // Initial - Temp Time
    case 1:
        for (int i = 0; i < 2; i++)
        {
            lcd.setCursor(4, i + 2);
            lcd.printWord(editOperationParams[i]);
        }
        // Answer fields logic
        switch (currentAnswerField)
        {
        case 0:
            changeOption(key, pageManager.currentStringFirstVal);
            break;
        case 1:
            changeOption(key, pageManager.currentStringSecondVal);
            break;
        }

        lcd.setCursor(7, 2);
        lcd.printWord(pageManager.currentStringFirstVal);
        lcd.setCursor(7, 3);
        lcd.printWord(pageManager.currentStringSecondVal);
        break;

        // case 2:
    }
}

void changeOption(char key, String &currentVal)
{
    const int MAX_DIGIT_LENGTH = 4; // Define the maximum length for the digits

    if (key != '\0' && key != '<' && key != '>' && key != 'A' && key != 'B' && key != 'C')
    {
        if (currentVal.length() < MAX_DIGIT_LENGTH)
        {
            // Ensure a single '.' at the digit
            if (key != '.' || parseStringFloat(currentVal))
            {
                currentVal += key;
            }
        }
    }
}

// Ensure that user can't input two '.'
bool parseStringFloat(String num)
{
    return num.indexOf('.') == -1;
}
