#include "EditExperimentPage.h"
#include "../GlobalDeclarations.h"

const char editOperationList[8][14] PROGMEM = {
    "Heated Lid",
    "Initial Step",
    "Cycles",
    "Denaturation",
    "Annealing",
    "Extending",
    "Final Step",
    "Final Hold"};

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
        lcd.printWord(readProgmemString(editOperationList[currentScreenIndex]));
    }

    switch (currentScreenIndex)
    {
    case 0:
        lcd.setCursor(4, 2);
        lcd.printWord(readProgmemString(editOperationParams[0]));
        lcd.setCursor(7, 2);
        changeOption(key, pageManager.currentStringFirstVal);
        lcd.printWord(pageManager.currentStringFirstVal);
        break;

    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
        for (int i = 0; i < 2; i++)
        {
            lcd.setCursor(4, i + 2);
            lcd.printWord(readProgmemString(editOperationParams[i]));
        }
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

    case 2:
        lcd.setCursor(4, 2);
        lcd.printWord(F("# cycles- "));
        changeOption(key, pageManager.currentStringFirstVal);
        lcd.printWord(pageManager.currentStringFirstVal);
        break;

    case 7:
        lcd.setCursor(4, 2);
        lcd.printWord(readProgmemString(editOperationParams[0]));
        lcd.setCursor(7, 2);
        changeOption(key, pageManager.currentStringFirstVal);
        lcd.printWord(pageManager.currentStringFirstVal);
        break;

    case 8:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(pageManager.currentProgName);
        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(readProgmemString(choiceLetterList[i]));
            lcd.printWord(readProgmemString(choiceOperationList[i]));
        }
        break;
    }
}

void changeOption(char key, String &currentVal)
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

bool parseStringFloat(String num)
{
    return num.indexOf('.') == -1;
}

// Function to read a string from PROGMEM
const char *readProgmemString(const char *str)
{
    static char buffer[64]; // Adjust the buffer size as per your needs
    strcpy_P(buffer, (char *)str);
    return buffer;
}