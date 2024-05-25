#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <LiquidCrystal_I2C.h>
#include "../Pages/MenuPage.h"
#include "../Pages/HomePage.h"
#include "../Pages/SettingsPage.h"
#include "../Pages/InfoPage.h"

class PageManager
{
public:
    enum PageState
    {
        MENU_PAGE,
        HOME_PAGE,
        SETTINGS_PAGE,
        INFO_PAGE
    };

    PageManager();

    void setPage(PageState page);
    PageState getPageState() const;
    // void displayCurrentPage(LiquidCrystal_I2C &lcd, char key = '\0');
    void nextSubpage();
    void previousSubpage();
    void resetSubpage();
    void handleMenuSelection(LiquidCrystal_I2C &lcd, char key = '\0');
    // int getCurrentSubpage() const;

    // Declare pageManager as extern
    static PageManager pageManager; // Declaration

private:
    PageState currentState;
    int currentSubpage;
    bool editing;
};

#endif
