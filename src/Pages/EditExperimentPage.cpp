#include "EditExperimentPage.h"
#include "GlobalDeclarations.h"

void displayEditExperiment(char key)
{
    const String editOperationList[6] = {"Heated Lid", "Initial Step", "Cycles", "Step 1", "Step 2", "Step 3"};
    const String editOperationParams[2] = {"C-XXX", "T-XXX"};
    int numEditOperationList = sizeof(editOperationList) / sizeof(editOperationList[0]);
    int numEditOperationParams = sizeof(editOperationParams) / sizeof(editOperationParams[0]);

    int currentScreenIndex = pageManager.getCurrentSubpage();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("AAA");
    lcd.printWord(" (C-TEMP T-TIME)");
    lcd.setCursor(2, 1);
    lcd.printWord(editOperationList[currentScreenIndex]);

    for (int j = 0; j < numEditOperationParams; j++)
    {
        lcd.setCursor(4, j + 2);
        lcd.printWord(editOperationParams[j]);
    }
}