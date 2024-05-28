#include "DelExperimentPage.h"
#include "GlobalDeclarations.h"

void displayDelExperiment(char key)
{
    const String choiceLetterList[2] = {"A-", "B-"};
    const String choiceOperationList[2] = {"Yes", "No"};

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("Delete experiment?");

    for (int i = 0; i < 2; i++)
    {
        lcd.setCursor(2, i + 1);
        lcd.printWord(choiceLetterList[i]);
        lcd.printWord(choiceOperationList[i]);
    }
}