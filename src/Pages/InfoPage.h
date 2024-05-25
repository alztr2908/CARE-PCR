#ifndef INFOPAGE_H
#define INFOPAGE_H

#include <LiquidCrystal_I2C.h>
#include "../Utils/PageManager.h"

class PageManager;

void displayInfoPage(LiquidCrystal_I2C &lcd, int subpage, char key);
#endif