#include "HomePage.h"
#include "../Utils/PageManager.h"

// Declare the extern variable to access the existing instance
extern PageManager pageManager;

void displayHomePage(LiquidCrystal_I2C &lcd, int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("A: Run B: Edit");
    lcd.setCursor(0, 3);
    lcd.print("C: Delete");
}