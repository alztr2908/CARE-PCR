#include "EditExperimentPage.h"
#include "../GlobalDeclarations.h"
#include "utils.h"

const char editOperationList[8][14] PROGMEM = {
    "Cycles",
    "Initial Step",
    "Denaturation",
    "Annealing",
    "Extending",
    "Final Step",
    "Final Hold",
};

const char editOperationParams[2][4] PROGMEM = {"C- ", "T- "};

const char choiceLetterList[3][4] PROGMEM = {"A- ", "B- ", "C- "};
const char choiceOperationList[3][7] PROGMEM = {"Save", "Edit", "Cancel"};

void displayEditExperiment(char key)
{
    int currentScreenIndex = pageManager.getCurrentSubpage();
    int currentAnswerField = pageManager.getCurrentAnswerField();

    if (currentScreenIndex < 8)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(pageManager.currentProgName);
        lcd.printWord(F("(C-Temp T-Time)"));

        lcd.setCursor(19, 0);
        lcd.printWord(String(pageManager.currentThermocyclerArrayIndex));

        lcd.setCursor(2, 1);
        lcd.printWord(rps(editOperationList[currentScreenIndex]));
    }

    switch (currentScreenIndex)
    {
    // # of cycles - whole number
    case 0:
        lcd.setCursor(4, 2);
        lcd.printWord(F("# cycles- "));
        optionIntNum(key, pageManager.currentStringFirstVal);
        lcd.printWord(pageManager.currentStringFirstVal);
        break;

    // 1. Initial step (float | whole)
    // 2. Step 1 - Denaturation (float | whole)
    // 3. Step 2 - Annealing (float | whole)
    // 4. Step 3 - Extension (float | whole)
    // 5. Final step (float | whole)
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        for (int i = 0; i < 2; i++)
        {
            lcd.setCursor(4, i + 2);
            lcd.printWord(rps(editOperationParams[i]));
        }
        switch (currentAnswerField)
        {
        case 0:
            optionFloatNum(key, pageManager.currentStringFirstVal);
            break;
        case 1:
            optionIntNum(key, pageManager.currentStringSecondVal);
            break;
        }
        lcd.setCursor(7, 2);
        lcd.printWord(pageManager.currentStringFirstVal);
        lcd.setCursor(7, 3);
        lcd.printWord(pageManager.currentStringSecondVal);
        break;

    // Final Hold - float
    case 6:
        lcd.setCursor(4, 2);
        lcd.printWord(rps(editOperationParams[0]));
        lcd.setCursor(7, 2);
        optionFloatNum(key, pageManager.currentStringFirstVal);
        lcd.printWord(pageManager.currentStringFirstVal);
        break;

    case 7:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(pageManager.currentProgName);
        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(rps(choiceLetterList[i]));
            lcd.printWord(rps(choiceOperationList[i]));
        }
        break;
    }
}

void optionFloatNum(char key, String &currentVal)
{
    const int MAX_DIGIT_LENGTH = 4;

    if (key != '\0' && key != '<' && key != '>' && key != 'A' && key != 'B' && key != 'C')
    {
        if (currentVal.length() < MAX_DIGIT_LENGTH)
        {
            if (key != '.' || parseStringFloat(currentVal))
            {
                currentVal += key;
            }
        }
    }
}

void optionIntNum(char key, String &currentVal)
{
    const int MAX_DIGIT_LENGTH = 3;

    if (key != '\0' && key != '<' && key != '>' && key != 'A' && key != 'B' && key != 'C' && key != '.')
    {
        if (currentVal.length() < MAX_DIGIT_LENGTH)
        {
            currentVal += key;
        }
    }
}

bool parseStringFloat(String num)
{
    return num.indexOf('.') == -1;
}
