#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <LiquidCrystal_I2C.h>
#include "../Utils/PageManager.h"

class PageManager;

void displayMenuPage(LiquidCrystal_I2C &lcd, PageManager &pageManager, int subpage, char key);
#endif
