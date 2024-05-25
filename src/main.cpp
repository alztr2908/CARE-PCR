#include <Arduino.h>
#include "./Utils/LCDManager.h"
#include "./Utils/PageManager.h"
#include "./Utils/KeypadHandler.h"

LCDManager lcdManager;   // Direct instantiation of LCDManager
PageManager pageManager; // Direct instantiation of PageManager

void setup()
{
  lcdManager.init();
  pageManager.setPage(PageManager::INFO_PAGE);
}

void loop()
{
  handleKeypad(lcdManager, pageManager);
}