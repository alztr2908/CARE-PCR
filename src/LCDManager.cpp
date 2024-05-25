#include "LCDManager.h"

LCDManager::LCDManager() : lcd(0x27, 16, 2) {}

void LCDManager::init()
{
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
}

LiquidCrystal_I2C &LCDManager::getLCD()
{
    return lcd;
}
