#include "MenuPage.h"

void displayMenuPage(LiquidCrystal_I2C &lcd, int subpage)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("A: Home");
    lcd.setCursor(0, 1);
    lcd.print("B: Settings");
    lcd.setCursor(0, 2);
    lcd.print("C: Info");
}
