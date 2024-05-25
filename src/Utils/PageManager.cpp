#include "PageManager.h"
#include "Pages/HomePage.h"
#include "Pages/SettingsPage.h"
#include "Pages/InfoPage.h"

void PageManager::setPage(const char *page)
{
    currentPage = page;
    currentSubpage = 0;
}

void PageManager::nextSubpage()
{
    currentSubpage++;
}

void PageManager::previousSubpage()
{
    if (currentSubpage > 0)
    {
        currentSubpage--;
    }
}

void PageManager::displayCurrentPage(LiquidCrystal_I2C &lcd)
{
    if (strcmp(currentPage, "home") == 0)
    {
        displayHomePage(lcd, currentSubpage);
    }
    else if (strcmp(currentPage, "settings") == 0)
    {
        displaySettingsPage(lcd, currentSubpage);
    }
    else if (strcmp(currentPage, "info") == 0)
    {
        displayInfoPage(lcd, currentSubpage);
    }
}
