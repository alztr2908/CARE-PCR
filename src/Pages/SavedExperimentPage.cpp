#include "SavedExperimentPage.h"
#include "GlobalDeclarations.h"

void displaySavedExperiment(char key)
{
    const String choiceLetterList[3] = {"A-", "B-", "C-"};
    const String choiceOperationList[3] = {"Run", "Edit", "Delete"};
    const String savedExperimentList[3] = {"AAA", "BAC", "CCC"};
    int numSavedExperiment = sizeof(savedExperimentList) / sizeof(savedExperimentList[0]);

    lcd.clear();
    lcd.setCursor(0, 0);

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        lcd.printWord("Saved experiments");
        for (int i = 0; i < numSavedExperiment; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(choiceLetterList[i]);
            lcd.printWord(savedExperimentList[i]);
        }
        break;

    case 1:
        lcd.printWord(savedExperimentList[0]);
        for (int i = 0; i < 3; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(choiceLetterList[i]);
            lcd.printWord(choiceOperationList[i]);
        }
        break;
    }
}
