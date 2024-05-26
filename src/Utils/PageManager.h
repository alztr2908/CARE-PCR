#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <LiquidCrystal_I2C.h>
#include "../Pages/MenuPage.h"
#include "../Pages/NewExperimentPage.h"
#include "../Pages/SavedExperimentPage.h"

class PageManager
{
public:
    enum PageState
    {
        MENU,
        NEW_EXPERIMENT,
        SAVED_EXPERIMENT,
    };

    PageManager();

    void setPageState(PageState page);
    PageState getPageState() const;
    // void displayCurrentPage(LiquidCrystal_I2C &lcd, char key = '\0');
    void nextSubpage();
    void previousSubpage();
    void resetSubpage();
    void handleMenuSelection(char key = '\0');
    void handleSavedExperimentSelection(char key = '\0');
    void handleReturnMenuSelection();
    int getCurrentSubpage() const;

private:
    PageState currentState;
    int currentSubpage;
    bool editing;
};

// Declare the extern instance
extern PageManager pageManager;

#endif
