#include "MenuPage.h"
#include "../Utils/PageManager.h"

// Declare the extern variable to access the existing instance
extern PageManager pageManager;

void displayMenuPage(LiquidCrystal_I2C &lcd, int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu Page");

    lcd.setCursor(0, 1);
    lcd.print("A: Home");

    lcd.setCursor(0, 2);
    lcd.print("B: Settings");

    lcd.setCursor(0, 3);
    lcd.print("C: Info");

    // if (key == 'A')
    // {
    //     pageManager.setPage(PageManager::HOME_PAGE);
    // }
    // else
    if (key == 'B')
    {
        pageManager.setPage(PageManager::SETTINGS_PAGE);
    }
    else if (key == 'C')
    {
        pageManager.setPage(PageManager::INFO_PAGE);
    }
}
