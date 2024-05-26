#include "LCDManager.h"

// Define the extern instance
LCDManager lcd(0x27, 20, 4); // Change the address and size to match your LCD

LCDManager::LCDManager(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : lcd(lcd_addr, lcd_cols, lcd_rows), cols(lcd_cols), rows(lcd_rows) {}

void LCDManager::begin()
{
    lcd.begin(cols, rows);
    lcd.init();
    lcd.backlight();
}

void LCDManager::printWord(const String &word)
{
    lcd.print(word);
}

void LCDManager::printLetter(const char &letter)
{
    lcd.print(letter);
}

void LCDManager::clear()
{
    lcd.clear();
}

void LCDManager::setCursor(int col, int row)
{
    lcd.setCursor(col, row);
}