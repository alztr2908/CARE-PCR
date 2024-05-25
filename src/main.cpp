#include <Arduino.h>
#include "LCDManager.h"
#include "PageManager.h"
#include "KeypadHandler.h"
#include "HomePage.h"
#include "SettingsPage.h"
#include "InfoPage.h"

// LCD and Page Manager Setup
LCDManager lcdManager;
PageManager pageManager;

void setup()
{
  lcdManager.init();
  pageManager.setPage("home");
  pageManager.displayCurrentPage(lcdManager.getLCD());
}

void loop()
{
  handleKeypad(lcdManager, pageManager);
}
