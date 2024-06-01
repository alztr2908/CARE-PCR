#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <LiquidCrystal_I2C.h>
#include "MenuPage.h"
#include "NewExperimentPage.h"
#include "SavedExperimentPage.h"
#include "RunExperimentPage.h"
#include "EditExperimentPage.h"
#include "DelExperimentPage.h"

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

    // Utils
    void setPageState(PageState page);
    PageState getPageState() const;
    void nextSubpage();
    void previousSubpage();
    int getCurrentSubpage() const;
    int getCurrentAnswerField() const;

    // Main Logic
    void handleReturnMenuSelection();
    void handleMenuSelection(char key = '\0');
    void handleNewExperimentSelection(char key = '\0');
    void handleSavedExperimentSelection(char key = '\0');
    void handleDelExperimentSelection(char key = '\0');
    void handleRunExperimentSelection(char key = '\0');
    void handleEditExperimentSelection(char key = '\0');

    // For global variable purposes only..
    String newProgName;
    String currentProgName;

    // Enabling countdown functionality
    int stepArrayIndex;
    int stepTimeHolder;
    unsigned long previousMillis;
    unsigned long currentMillis;

    // Placeholder of values at EDIT_EXPERIMENT
    String currentStringFirstVal;
    String currentStringSecondVal;

    int currentThermocyclerArrayIndex;

    float currentHeatedLid;

    float currentInitStepTemp;
    int currentInitStepTime;

    int currentCycleNo;

    float currentFirstStepTemp;
    int currentFirstStepTime;

    float currentSecondStepTemp;
    int currentSecondStepTime;

    float currentThirdStepTemp;
    int currentThirdStepTime;

    float currentFinalStepTemp;
    int currentFinalStepTime;

    float currentFinalHoldTemp;

private:
    // Accesory methods
    void resetSubpage();
    void setCurrentSubPage(int subpage);

    PageState currentState;
    int currentAnswerField;
    int currentSubpage;
};

// Declare the extern instance
// extern PageManager pageManager;

#endif
