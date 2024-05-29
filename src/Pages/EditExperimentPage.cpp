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
        changeOption(currentAnswerField, key);
        break;
    // Initial - Temp Time
    case 1:
        for (int i = 0; i < 2; i++)
        {
            lcd.setCursor(4, i + 2);
            lcd.printWord(editOperationParams[i]);
        }
        switch (currentAnswerField)
        {
        case 0:
            changeOption(0, key);
            break;
        case 1:
            changeOption(1, key);
            break;
        }

        // Answer fields logic
        break;

        // case 2:
    }
}

void changeOption(int index, char key)
{
    const int MAX_DIGIT_LENGTH = 5; // Define the maximum length for the digits

    lcd.setCursor(7, index + 2);

    if (key != '\0' && key != '<' && key != '>' && key != 'A' && key != 'B' && key != 'C')
    {
        if (pageManager.currentStringVal.length() < MAX_DIGIT_LENGTH)
        {
            // Ensure a single '.' at the digit
            if (key != '.' || parseStringFloat(pageManager.currentStringVal))
            {
                pageManager.currentStringVal += key;
            }
        }
    }
    lcd.printWord(pageManager.currentStringVal);
}

// Ensure that user can't input two '.'
bool parseStringFloat(String num)
{
    return num.indexOf('.') == -1;
}