#include "InfoPage.h"
#include "../Utils/PageManager.h"

PageManager pageManager;

void displayInfoPage(LiquidCrystal_I2C &lcd, int subpage, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);

    if (subpage == 0)
    {
        lcd.print("Info Page");
    }
    else if (subpage == 1)
    {
        lcd.print("Info Subpage 1");
    }
    else if (subpage == 2)
    {
        lcd.print("Info Subpage 2");
    }

    if (key == '<')
    {
        pageManager.previousSubpage();
    }
    else if (key == '>')
    {
        pageManager.nextSubpage();
    }
}
