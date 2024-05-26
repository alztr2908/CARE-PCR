#include "MenuPage.h"
#include "../Utils/PageManager.h"
#include "../Utils/LCDManager.h"

void displayMenuPage(int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("CARE-PCR");
    lcd.setCursor(15, 0);
    lcd.printWord("11:59");
    lcd.setCursor(0, 2);
    lcd.printWord("A-Add new experiment");
    lcd.setCursor(0, 3);
    lcd.printWord("B-Saved experiment");

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
