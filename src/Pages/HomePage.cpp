#include "HomePage.h"

void displayHomePage(LiquidCrystal_I2C &lcd, int subpage)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    if (subpage == 0)
    {
        lcd.print("Home Page");
        lcd.setCursor(0, 1);
        lcd.print("Welcome Home!");
    }
    else if (subpage == 1)
    {
        lcd.print("Home Subpage 1");
    }
    else if (subpage == 2)
    {
        lcd.print("Home Subpage 2");
    }
}
