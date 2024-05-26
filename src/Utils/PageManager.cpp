#include "PageManager.h"
#include "LCDManager.h"

// Define the extern instance
PageManager pageManager;

PageManager::PageManager() : currentState(MENU), currentSubpage(0), editing(false)
{
    // Initialize subpages if needed
}

void PageManager::setPageState(PageState page)
{
    currentState = page;
    // resetSubpage();
}

PageManager::PageState PageManager::getPageState() const
{
    return currentState;
}

void PageManager::nextSubpage()
{
    currentSubpage++;
    // You may want to add checks to cycle through subpages or limit the number
}

void PageManager::previousSubpage()
{
    currentSubpage--;
    // if (currentSubpage == 0){
    //     handleReturnMenuSelection();
    // } else {
    //     currentSubpage--;

    // }
}

void PageManager::resetSubpage()
{
    currentSubpage = 0;
}

int PageManager::getCurrentSubpage() const
{
    return currentSubpage;
}

void PageManager::handleReturnMenuSelection()
{
    setPageState(PageManager::MENU);
    resetSubpage();
    lcd.clear();
    lcd.delay(500);
    displayMenuPage(0, '\0');
}

void PageManager::handleMenuSelection(char key)
{
    switch (key)
    {
    case 'A':
        setPageState(PageManager::NEW_EXPERIMENT);
        displayNewExperiment(0, '\0');
        break;
    case 'B':
        setPageState(PageManager::SAVED_EXPERIMENT);
        displaySavedExperiment('\0');
        break;
    }
}

void PageManager::handleSavedExperimentSelection(char key)
{
    if (key == '<')
    {
        if (getCurrentSubpage() == 0)
        {
            handleReturnMenuSelection();
        }
        else
        {
            previousSubpage();
            displaySavedExperiment('\0');
        }
    }
    else
    {
        if (getCurrentSubpage() == 0)
        {
            if (key == 'A' || key == 'B' || key == 'C')
            {
                nextSubpage();
                displaySavedExperiment(key);
            }
        }
        else if (getCurrentSubpage() == 1)
        {
            if (key == 'A')
            {
                // currentState = RUN_EXPERIMENT;
                // currentScreenIndex = 0;
                handleReturnMenuSelection();
            }
            // else if (key == 'B')
            // {
            //     currentState = EDIT_EXPERIMENT;
            //     currentScreenIndex = 0;
            //     displayEditExperiment('\0');
            //     // Implement Edit logic here
            // }
            // else if (key == 'C')
            // {
            //     // Implement Delete logic here
            //     currentState = DEL_EXPERIMENT;
            //     currentScreenIndex = 0;
            //     displayDelExperiment('\0');
            // }
        }
    }
}
