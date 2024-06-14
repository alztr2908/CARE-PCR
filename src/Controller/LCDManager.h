#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDManager
{
public:
    LCDManager(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);

    void begin();
    void printWord(const String &message);
    void printLetter(const char &letter);
    void clear();
    void setCursor(int col, int row);
    void delay(unsigned long ms);

private:
    LiquidCrystal_I2C lcd;
    uint8_t cols;
    uint8_t rows;
};

#endif