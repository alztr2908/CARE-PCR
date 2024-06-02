#include "DelExperimentPage.h"
#include "../GlobalDeclarations.h"

void displayDelExperiment(char key)
{
    const String choiceLetterList[2] = {"A- ", "B- "};
    const String choiceOperationList[2] = {"Yes", "No"};

    lcd.clear();
    lcd.setCursor(0, 0);

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        lcd.printWord("Delete ");
        lcd.printWord(pageManager.currentProgName);
        lcd.printWord("?");
        lcd.setCursor(19, 0);
        lcd.printWord(String(pageManager.currentThermocyclerArrayIndex));

        for (int i = 0; i < 2; i++)
        {
            lcd.setCursor(2, i + 1);
            lcd.printWord(choiceLetterList[i]);
            lcd.printWord(choiceOperationList[i]);
        }
        break;
    case 1:
        lcd.printWord(pageManager.currentProgName);
        lcd.setCursor(2, 1);
        lcd.printWord("*** DELETED");
        lcd.setCursor(2, 2);
        lcd.printWord("SUCCESSFULLY ***");
        lcd.setCursor(5, 3);
        lcd.printWord(">> press any...");
        break;
    }
}