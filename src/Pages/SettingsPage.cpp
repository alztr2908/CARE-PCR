#include "SettingsPage.h"
#include "../Utils/PageManager.h"

void displaySettingsPage(LiquidCrystal_I2C &lcd, PageManager &pageManager, int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);

    if (subpage == 0)
    {
        lcd.print("Settings Page");
        lcd.setCursor(0, 1);
        lcd.print("A: Volume Down");
        lcd.setCursor(0, 2);
        lcd.print("B: Volume Up");
    }
    else if (subpage == 1)
    {
        lcd.print("Settings Subpage 1");
    }
    else if (subpage == 2)
    {
        lcd.print("Settings Subpage 2");
    }

    if (key == 'A')
    {
        // Implement volume down functionality here
    }
    else if (key == 'B')
    {
        // Implement volume up functionality here
    }
    else if (key == '<')
    {
        pageManager.previousSubpage();
    }
    else if (key == '>')
    {
        pageManager.nextSubpage();
    }
}
