#include "SavedExperimentPage.h"
#include "../Utils/PageManager.h"
#include "../Utils/LCDManager.h"

// Declare the extern variable to access the existing instance
extern PageManager pageManager;

void displaySavedExperiment(int subpage, char key)
{
    const String choiceLetterList[3] = {"A-", "B-", "C-"};
    const String choiceOperationList[3] = {"Run", "Edit", "Delete"};
    const String savedExperimentList[3] = {"AAA", "BAC", "CCC"};
    int numSavedExperiment = sizeof(savedExperimentList) / sizeof(savedExperimentList[0]);

    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.printWord("Saved experiments");
    for (int i = 0; i < numSavedExperiment; i++)
    {
        lcd.setCursor(2, i + 1);
        lcd.printWord(choiceLetterList[i]);
        lcd.printWord(savedExperimentList[i]);
    }

    // if (key == 'A')
    // {
    //     // Implement volume down functionality here
    // }
    // else if (key == 'B')
    // {
    //     // Implement volume up functionality here
    // }
    // else if (key == '<')
    // {
    //     pageManager.previousSubpage();
    // }
    // else if (key == '>')
    // {
    //     pageManager.nextSubpage();
    // }
}
