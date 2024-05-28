#include "PageManager.h"
#include "GlobalDeclarations.h"

// Define the extern instance
PageManager pageManager;

PageManager::PageManager() {}

/* UTILS */
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
}

void PageManager::previousSubpage()
{
    currentSubpage--;
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

/* MAIN LOGIC */
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
        if (getCurrentSubpage() == 0)
        {
            // Handle New Experiment Name Parsing
            currentProgName = newProgName;

            if (thermocyclerArray.isThermocyclerArrayFull())
            {
                // Clear and update
                newProgName = "";
                currentThermocyclerArrayIndex = thermocyclerArray.emptyElementIndex();

                setPageState(PageManager::EDIT_EXPERIMENT);
                resetSubpage();
                displayEditExperiment();
            }
            else
            {
                // If thermocyclerArray experiments is full, proceed to next page
                nextSubpage();
                displayNewExperiment();
            }
        }
        else
        {
            // Clear
            newProgName = "";
            // Go Home
            handleReturnMenuSelection();
        }
    }
    else if (key == '<')
    {
        if (getCurrentSubpage() == 0)
        {
            // Handle New Experiment Name Parsing
            if (newProgName != "")
            {
                String slicedString = newProgName.substring(0, newProgName.length() - 1);
                newProgName = slicedString;
                displayNewExperiment();
            }
            else
            {
                handleReturnMenuSelection();
            }
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

            if (key == 'A')
            {
                currentProgName = thermocyclerArray.getElement(0).getProgName();
                currentThermocyclerArrayIndex = 0;
            }
            else if (key == 'B')
            {
                currentProgName = thermocyclerArray.getElement(1).getProgName();
                currentThermocyclerArrayIndex = 1;
            }
            else if (key == 'C')
            {
                currentProgName = thermocyclerArray.getElement(2).getProgName();
                currentThermocyclerArrayIndex = 2;
            }
            nextSubpage();
            displaySavedExperiment();
        }
        else if (getCurrentSubpage() == 1)
        {
            if (key == 'A')
            {
                // Implement Run logic here
                setPageState(PageManager::RUN_EXPERIMENT);
                resetSubpage();
                displayRunExperiment();
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

void PageManager::handleRunExperimentSelection(char key)
{
    if (key == '>' && getCurrentSubpage() == 0)
    {
        nextSubpage();
        displayRunExperiment();
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
            displayRunExperiment();
        }
    }
    else
    {
        if (getCurrentSubpage() == 1 || getCurrentSubpage() == 2)
        {
            if (key == 'A')
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.printWord("AAA");
                lcd.setCursor(0, 1);
                lcd.printWord("Data saved");
                lcd.setCursor(0, 2);
                lcd.printWord("successfully");
                lcd.delay(2000);
                handleReturnMenuSelection();
            }
            else if (key == 'B')
            {
                handleReturnMenuSelection();
            }
        }
        else
        {
            displayRunExperiment(key);
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