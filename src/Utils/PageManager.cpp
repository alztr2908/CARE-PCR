#include "PageManager.h"

PageManager::PageManager() : currentState(MENU_PAGE), currentSubpage(0), editing(false)
{
    // Initialize subpages if needed
}

void PageManager::setPage(PageState page)
{
    currentState = page;
    resetSubpage();
}

PageManager::PageState PageManager::getPageState() const
{
    return currentState;
}

void PageManager::displayCurrentPage(LiquidCrystal_I2C &lcd, char key)
{
    switch (currentState)
    {
    // case MENU_PAGE:
    //     displayMenuPage(lcd, *this, currentSubpage, key);
    //     break;
    // case HOME_PAGE:
    //     // Implement home page display
    //     break;
    // case SETTINGS_PAGE:
    //     displaySettingsPage(lcd, *this, currentSubpage, key);
    //     break;
    case INFO_PAGE:
        displayInfoPage(lcd, currentSubpage, key);
        break;
    }
}

void PageManager::nextSubpage()
{
    currentSubpage++;
    // You may want to add checks to cycle through subpages or limit the number
}

void PageManager::previousSubpage()
{
    if (currentSubpage > 0)
    {
        currentSubpage--;
    }
}

void PageManager::resetSubpage()
{
    currentSubpage = 0;
}

int PageManager::getCurrentSubpage() const
{
    return currentSubpage;
}