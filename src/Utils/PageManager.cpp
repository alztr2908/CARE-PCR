#include "PageManager.h"
#include "LCDManager.h"

// Define the extern instance
PageManager pageManager;

PageManager::PageManager() : currentState(MENU), currentSubpage(0), editing(false), name("")
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

void PageManager::setCurrentSubPage(int subpage)
{
    currentSubpage = subpage;
}

void PageManager::handleReturnMenuSelection()
{
    setPageState(PageManager::MENU);
    resetSubpage();
    lcd.clear();
    lcd.delay(500);
    displayMenuPage();
}

void PageManager::handleMenuSelection(char key)
{
    switch (key)
    {
    case 'A':
        setPageState(PageManager::NEW_EXPERIMENT);
        displayNewExperiment();
        break;
    case 'B':
        setPageState(PageManager::SAVED_EXPERIMENT);
        displaySavedExperiment();
        break;
    }
}

void PageManager::handleNewExperimentSelection(char key)
{
    if (key == '>')
    {
        nextSubpage();
        if (getCurrentSubpage() > 1)
        {
            resetSubpage();
        }
        displayNewExperiment();
    }
    else if (key == '<')
    {
        if (getCurrentSubpage() == 0)
        {
            handleReturnMenuSelection();
        }
        else
        {
            previousSubpage();
            displayNewExperiment();
        }
    }
    else
    {
        displayNewExperiment(key);
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
            displaySavedExperiment();
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
            else if (key == 'B')
            {
                // Implement Edit logic here
                setPageState(PageManager::EDIT_EXPERIMENT);
                resetSubpage();
                displayEditExperiment();
            }
            else if (key == 'C')
            {
                // Implement Delete logic here
                setPageState(PageManager::DEL_EXPERIMENT);
                resetSubpage();
                displayDelExperiment();
            }
        }
    }
}

void PageManager::handleEditExperimentSelection(char key)
{
    if (key == '>')
    {
        if (getCurrentSubpage() == 5)
        {
            handleReturnMenuSelection();
        }
        else
        {
            nextSubpage();
            displayEditExperiment();
        }
    }
    else if (key == '<')
    {
        if (getCurrentSubpage() == 0)
        {
            handleReturnMenuSelection();
        }
        else
        {
            previousSubpage();
            displayEditExperiment();
        }
    }
}

void PageManager::handleDelExperimentSelection(char key)
{
    if (key == '>' || key == 'A')
    {
        // Add delete function in saved experiment list
        handleReturnMenuSelection();
    }
    else if (key == '<')
    {
        // Go back to saved experiment option
        currentState = SAVED_EXPERIMENT;
        setPageState(PageManager::SAVED_EXPERIMENT);
        setCurrentSubPage(1);
        displaySavedExperiment();
    }
    else
    {
        if (key == 'B')
        {
            // Go back to saved experiment list
            currentState = SAVED_EXPERIMENT;
            setCurrentSubPage(0);
            displaySavedExperiment();
        }
    }
}