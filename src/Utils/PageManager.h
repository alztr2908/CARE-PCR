#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <LiquidCrystal_I2C.h>
#include "../Pages/MenuPage.h"
#include "../Pages/NewExperimentPage.h"
#include "../Pages/SavedExperimentPage.h"
#include "../Pages/RunExperimentPage.h"
#include "../Pages/EditExperimentPage.h"
#include "../Pages/DelExperimentPage.h"

class PageManager
{
public:
    enum PageState
    {
        MENU,
        NEW_EXPERIMENT,
        SAVED_EXPERIMENT,
        RUN_EXPERIMENT,
        DEL_EXPERIMENT,
        EDIT_EXPERIMENT,
    };

    PageManager();

    void setPageState(PageState page);
    PageState getPageState() const;
    // void displayCurrentPage(LiquidCrystal_I2C &lcd, char key = '\0');
    void nextSubpage();
    void previousSubpage();
    void handleMenuSelection(char key = '\0');
    void handleNewExperimentSelection(char key = '\0');
    void handleSavedExperimentSelection(char key = '\0');
    void handleDelExperimentSelection(char key = '\0');
    void handleRunExperimentSelection(char key = '\0');
    void handleEditExperimentSelection(char key = '\0');
    void handleReturnMenuSelection();
    int getCurrentSubpage() const;

    // For global variable purposes only.. delete if thermocycler is added
    String name;

private:
    void resetSubpage();
    void setCurrentSubPage(int subpage);
    PageState currentState;
    int currentSubpage;
    bool editing;
};

// Declare the extern instance
// extern PageManager pageManager;

#endif
