#include "NewExperimentPage.h"
#include "../Utils/PageManager.h"

// Declare the extern variable to access the existing instance
extern PageManager pageManager;

void displayNewExperiment(LiquidCrystal_I2C &lcd, int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("New Experiment");
    lcd.setCursor(2, 2);
    lcd.print("Name: ");
}