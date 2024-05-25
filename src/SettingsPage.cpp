#include "SettingsPage.h"

void displaySettingsPage(LiquidCrystal_I2C &lcd, int subpage)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    if (subpage == 0)
    {
        lcd.print("Settings Page");
        lcd.setCursor(0, 1);
        lcd.print("Adjust Settings");
    }
    else if (subpage == 1)
    {
        lcd.print("Settings Subpage 1");
    }
    else if (subpage == 2)
    {
        lcd.print("Settings Subpage 2");
    }
}
