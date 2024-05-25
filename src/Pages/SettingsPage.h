#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <LiquidCrystal_I2C.h>

void displaySettingsPage(LiquidCrystal_I2C &lcd, PageManager &pageManager, int subpage, char key);

#endif
