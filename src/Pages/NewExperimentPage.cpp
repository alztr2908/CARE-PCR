#include "NewExperimentPage.h"
#include "GlobalDeclarations.h"

void displayNewExperiment(char key)
{
    String name = "";

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("New Experiment");

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        lcd.setCursor(2, 2);
        lcd.printWord("Name: ");
        if (key != '\0' && key != '<' && key != '>')
        {
            pageManager.inProgressProgName += key;
        }
        lcd.setCursor(8, 2);
        lcd.printWord(pageManager.inProgressProgName);
        break;
    case 1:
        lcd.setCursor(2, 2);
        lcd.printWord("Saved experiments");
        lcd.setCursor(4, 3);
        lcd.printWord("are full");
        break;
    }
}