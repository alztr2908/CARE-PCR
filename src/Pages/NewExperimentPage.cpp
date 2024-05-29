#include "NewExperimentPage.h"
#include "GlobalDeclarations.h"

void displayNewExperiment(char key)
{
    const int MAX_NAME_LENGTH = 3; // Define the maximum length for the name

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("New Experiment");

    int currentScreenIndex = pageManager.getCurrentSubpage();

    switch (currentScreenIndex)
    {
    case 0:
        lcd.setCursor(2, 2);
        lcd.printWord("Name: ");
        if (key != '\0' && key != '<' && key != '>' && (key == 'A' || key == 'B' || key == 'C'))
        {
            if (pageManager.newProgName.length() < MAX_NAME_LENGTH)
            {
                pageManager.newProgName += key;
            }
        }
        lcd.setCursor(8, 2);
        lcd.printWord(pageManager.newProgName);
        break;
    case 1:
        lcd.setCursor(2, 2);
        lcd.printWord("Saved experiments");
        lcd.setCursor(4, 3);
        lcd.printWord("are full");
        break;
    }
}