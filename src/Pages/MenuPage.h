#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <LiquidCrystal_I2C.h>
#include "../Utils/PageManager.h"
#include "../Pages/MenuPage.h"
#include "../Pages/SavedExperimentPage.h"
class PageManager;

void displayMenuPage(LiquidCrystal_I2C &lcd, int subpage, char key);
#endif
