#include "NewExperimentPage.h"
#include "../Utils/PageManager.h"
#include "../Utils/LCDManager.h"

// Declare the extern variable to access the existing instance
extern PageManager pageManager;

void displayNewExperiment(int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("New Experiment");
    lcd.setCursor(2, 2);
    lcd.printWord("Name: ");
}