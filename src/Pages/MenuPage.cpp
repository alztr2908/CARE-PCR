#include "MenuPage.h"
#include "../Utils/PageManager.h"
#include "../Utils/LCDManager.h"

// Declare the extern variable to access the existing instance
extern PageManager pageManager;

LiquidCrystal_I2C lcd = lcdManager.getLCD();

void displayMenuPage(int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CARE-PCR");
    lcd.setCursor(15, 0);
    lcd.print("11:59");
    lcd.setCursor(0, 2);
    lcd.print("A-Add new experiment");
    lcd.setCursor(0, 3);
    lcd.print("B-Saved experiment");

    // if (key == 'A')
    // {
    //     pageManager.setPage(PageManager::HOME_PAGE);
    // }
    // else
    // if (key == 'B')
    // {
    //     pageManager.setPage(PageManager::SETTINGS_PAGE);
    //     displaySettingsPage(lcd, 0, '\0');
    // }
    // else if (key == 'C')
    // {
    //     pageManager.setPage(PageManager::INFO_PAGE);
    // }
}
