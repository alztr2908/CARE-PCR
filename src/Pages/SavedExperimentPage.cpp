#include "SavedExperimentPage.h"
#include "../GlobalDeclarations.h"
// #include "./Thermocycler/Thermocycler.h"

void displaySavedExperiment(char key)
{
    const String choiceLetterList[3] = {"A- ", "B- ", "C- "};
    const String choiceOperationList[3] = {"Run", "Edit", "Delete"};
    // const String savedExperimentList[3] = {"AAA", "BAC", "CCC"};
    // int numSavedExperiment = sizeof(savedExperimentList) / sizeof(savedExperimentList[0]);
    int numSavedExperiment = 3;

    Thermocycler currentThermocycler;

    lcd.clear();
    lcd.setCursor(0, 0);

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        lcd.printWord("Saved experiments");
        for (int i = 0; i < numSavedExperiment; i++)
        {
            currentThermocycler = thermocyclerArray.getElement(i);
            lcd.setCursor(2, i + 1);
            lcd.printWord(choiceLetterList[i]);
            lcd.printWord(currentThermocycler.getProgName());
        }
        break;

    case 1:
        lcd.printWord(pageManager.currentProgName);
        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(choiceLetterList[i]);
            lcd.printWord(choiceOperationList[i]);
        }
        break;
    }
}
