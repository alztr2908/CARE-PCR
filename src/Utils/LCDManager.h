#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <LiquidCrystal_I2C.h>

class LCDManager
{
public:
    LCDManager();
    void init();
    LiquidCrystal_I2C &getLCD();

private:
    LiquidCrystal_I2C lcd;
};

#endif
