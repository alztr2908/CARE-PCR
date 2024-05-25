#include "InfoPage.h"

void displayInfoPage(LiquidCrystal_I2C &lcd, int subpage)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    if (subpage == 0)
    {
        lcd.print("Info Page");
        lcd.setCursor(0, 1);
        lcd.print("Some Information");
    }
    else if (subpage == 1)
    {
        lcd.print("Info Subpage 1");
    }
    else if (subpage == 2)
    {
        lcd.print("Info Subpage 2");
    }
}
