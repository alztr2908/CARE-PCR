#include "DelExperimentPage.h"
#include "../GlobalDeclarations.h"

const char choiceLetterList[2][4] PROGMEM = {"A- ", "B- "};
const char choiceOperationList[2][4] PROGMEM = {"Yes", "No"};

void displayDelExperiment(char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        lcd.printWord(F("Delete "));
        lcd.printWord(pageManager.currentProgName);
        lcd.printWord(F("?"));
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
        lcd.printWord(F("*** DELETED"));
        lcd.setCursor(2, 2);
        lcd.printWord(F("SUCCESSFULLY ***"));
        lcd.setCursor(5, 3);
        lcd.printWord(F(">> press any..."));
        break;
    }
}