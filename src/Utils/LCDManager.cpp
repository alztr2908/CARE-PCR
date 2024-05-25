#include "LCDManager.h"

LCDManager::LCDManager() : lcd(0x27, 20, 4)
{
}

void LCDManager::init()
{
    lcd.begin(20, 4);
    lcd.init();
    lcd.backlight();
}

LiquidCrystal_I2C &LCDManager::getLCD()
{
    return lcd;
}
