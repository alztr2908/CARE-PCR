#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <LiquidCrystal_I2C.h>
#include "MenuPage.h"
#include "NewExperimentPage.h"
#include "SavedExperimentPage.h"
#include "RunExperimentPage.h"
#include "EditExperimentPage.h"
#include "DelExperimentPage.h"

#define MAX_STEPS 5

class PageManager
{
public:
    enum PageState
    {
        MENU,
        NEW_EXPERIMENT,
        SAVED_EXPERIMENT,
        RUN_EXPERIMENT_RUN,
        RUN_EXPERIMENT_NOTRUN,
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

    // Placeholder of values at EDIT_EXPERIMENT and RUN_EXPERIMENT
    String currentStringFirstVal;
    String currentStringSecondVal;

    // ThermocyclerArray parameters
    int currentThermocyclerArrayIndex;

    // Thermocycling parameters
    float currentHeatedLid;
    int currentCycleNo;
    float currentFinalHoldTemp;

    // Steps
    float stepTempHolder[MAX_STEPS];
    int stepTimeHolder[MAX_STEPS];

    // Enabling countdown functionality
    int stepArrayIndex;
    int currentStepTime;
    unsigned long previousMillis;
    unsigned long currentMillis;
    unsigned long timeElapsedinS;

private:
    // Accesory methods
    void resetSubpage();
    void setCurrentSubPage(int subpage);
    void clearIntArray(int *array, int size);
    void clearFloatArray(float *array, int size);

    PageState currentState;
    int currentAnswerField;
    int currentSubpage;
};

// Declare the extern instance
// extern PageManager pageManager;

#endif
