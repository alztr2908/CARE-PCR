#include <Arduino.h>
#include "Utils/LCDManager.h"
#include "Utils/PageManager.h"
#include "Utils/KeypadHandler.h"
#include "Pages/HomePage.h"

// LCD and Page Manager Setup
LCDManager lcdManager;
PageManager pageManager;

void setup()
{
  lcdManager.init();
  pageManager.setPage("menu");
  pageManager.displayCurrentPage(lcdManager.getLCD());
}

void loop()
{
  handleKeypad(lcdManager, pageManager);
}
