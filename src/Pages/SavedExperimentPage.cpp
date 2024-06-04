#include "SavedExperimentPage.h"
#include "../GlobalDeclarations.h"
#include "utils.h"

const char choiceLetterList[3][4] PROGMEM = {"A- ", "B- ", "C- "};
const char choiceOperationList[3][7] PROGMEM = {"Run", "Edit", "Delete"};

void displaySavedExperiment(char key)
{
    Thermocycler currentThermocycler;
    int currentScreenIndex = pageManager.getCurrentSubpage();

    lcd.clear();
    lcd.setCursor(0, 0);

    switch (currentScreenIndex)
    {
    case 0:
        lcd.printWord("Saved experiments");
        for (int i = 0; i < 3; i++)
        {
            currentThermocycler = thermocyclerArray.getElement(i);
            lcd.setCursor(2, i + 1);
            lcd.printWord(rps(choiceLetterList[i]));
            lcd.printWord(currentThermocycler.getProgName());
        }
        break;

    case 1:
        lcd.printWord(pageManager.currentProgName);
        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(rps(choiceLetterList[i]));
            lcd.printWord(rps(choiceOperationList[i]));
        }
        lcd.setCursor(19, 0);
        lcd.printWord(String(pageManager.currentThermocyclerArrayIndex));
        break;
    }
}
