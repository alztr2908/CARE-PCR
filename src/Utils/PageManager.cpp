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

int PageManager::getCurrentAnswerField() const
{
    return currentAnswerField;
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
        /* CAN'T BE SWITCH STATEMENT DUE TO DIFF ATTR*/
        // Heated Lid
        if (getCurrentSubpage() == 0)
        {
            currentHeatedLid = currentStringFirstVal.toFloat();
            currentStringFirstVal = "";
            nextSubpage();
            displayEditExperiment();
        }
        // Initial Step
        else if (getCurrentSubpage() == 1)
        {
            // Change Answer fields
            if (getCurrentAnswerField() == 1)
            {
                currentInitStepTime = currentStringSecondVal.toInt();

                currentStringFirstVal = "";
                currentStringSecondVal = "";
                currentAnswerField = 0;
                nextSubpage();
                displayEditExperiment();
            }
            else
            {
                currentInitStepTemp = currentStringFirstVal.toFloat();
                currentAnswerField++;
            }
        }
        // Cycle No.
        else if (getCurrentSubpage() == 2)
        {
            currentCycleNo = currentStringFirstVal.toInt();
            currentStringFirstVal = "";
            nextSubpage();
            displayEditExperiment();
        }
        // Step 1 - Denaturation
        else if (getCurrentSubpage() == 3)
        {
            // Change Answer fields
            if (getCurrentAnswerField() == 1)
            {
                currentFirstStepTime = currentStringSecondVal.toInt();

                currentStringFirstVal = "";
                currentStringSecondVal = "";
                currentAnswerField = 0;
                nextSubpage();
                displayEditExperiment();
            }
            else
            {
                currentFirstStepTemp = currentStringFirstVal.toFloat();
                currentAnswerField++;
            }
        }
        // Step 1 - Annealing
        else if (getCurrentSubpage() == 4)
        {
            // Change Answer fields
            if (getCurrentAnswerField() == 1)
            {
                currentSecondStepTime = currentStringSecondVal.toInt();

                currentStringFirstVal = "";
                currentStringSecondVal = "";
                currentAnswerField = 0;
                nextSubpage();
                displayEditExperiment();
            }
            else
            {
                currentSecondStepTemp = currentStringFirstVal.toFloat();
                currentAnswerField++;
            }
        }
        // Step 1 - Extension
        else if (getCurrentSubpage() == 5)
        {
            // Change Answer fields
            if (getCurrentAnswerField() == 1)
            {
                currentThirdStepTime = currentStringSecondVal.toInt();

                currentStringFirstVal = "";
                currentStringSecondVal = "";
                currentAnswerField = 0;
                nextSubpage();
                displayEditExperiment();
            }
            else
            {
                currentThirdStepTemp = currentStringFirstVal.toFloat();
                currentAnswerField++;
            }
        }
        // Final Step
        else if (getCurrentSubpage() == 6)
        {
            // Change Answer fields
            if (getCurrentAnswerField() == 1)
            {
                currentFinalStepTime = currentStringSecondVal.toInt();

                currentStringFirstVal = "";
                currentStringSecondVal = "";
                currentAnswerField = 0;
                nextSubpage();
                displayEditExperiment();
            }
            else
            {
                currentFinalStepTemp = currentStringFirstVal.toFloat();
                currentAnswerField++;
            }
        }
        // Final Hold
        else if (getCurrentSubpage() == 7)
        {
            currentFinalHoldTemp = currentStringFirstVal.toFloat();
            currentStringFirstVal = "";
            nextSubpage();
            displayEditExperiment();
        }
        // Saving
        else if (getCurrentSubpage() == 8)
        {
            // Initialize and add the new/modified thermocycler
            Thermocycler currTc = thermocyclerArray.getElement(currentThermocyclerArrayIndex);
            currTc.setProgName(currentProgName);
            currTc.setHeatedLid(currentHeatedLid);
            currTc.setStep(0, Step::INITIAL, currentInitStepTemp, currentInitStepTime);
            currTc.setNumCycles(currentCycleNo);
            currTc.setStep(1, Step::DENATURATION, currentFirstStepTemp, currentFirstStepTime);
            currTc.setStep(2, Step::ANNEALING, currentSecondStepTemp, currentSecondStepTime);
            currTc.setStep(3, Step::EXTENDING, currentThirdStepTemp, currentThirdStepTime);
            currTc.setStep(4, Step::FINAL, currentFinalStepTemp, currentFinalStepTime);
            currTc.setFinalHoldTemp(currentFinalHoldTemp);
            thermocyclerArray.modifyElement(currentThermocyclerArrayIndex, currTc);

            // Go back to saved experiment to see if new thermocycler has been saved
            setPageState(PageManager::SAVED_EXPERIMENT);
            resetSubpage();
            displaySavedExperiment();
        }
    }
    else if (key == '<')
    {
        switch (getCurrentSubpage())
        {
        case 0:
            handleReturnMenuSelection();
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            if (getCurrentAnswerField() == 1)
            {
                currentAnswerField--;
            }
            else
            {
                currentStringFirstVal = "";
                currentStringSecondVal = "";
                previousSubpage();
                displayEditExperiment();
            }
            break;
        default:
            previousSubpage();
            displayEditExperiment();
            break;
        }
    }
    else
    {
        if (getCurrentSubpage() == 8)
        {
            if (key == 'A')
            {
                // Initialize and add the new/modified thermocycler
                Thermocycler currTc = thermocyclerArray.getElement(currentThermocyclerArrayIndex);
                currTc.setProgName(currentProgName);
                currTc.setHeatedLid(currentHeatedLid);
                currTc.setStep(0, Step::INITIAL, currentInitStepTemp, currentInitStepTime);
                currTc.setNumCycles(currentCycleNo);
                currTc.setStep(1, Step::DENATURATION, currentFirstStepTemp, currentFirstStepTime);
                currTc.setStep(2, Step::ANNEALING, currentSecondStepTemp, currentSecondStepTime);
                currTc.setStep(3, Step::EXTENDING, currentThirdStepTemp, currentThirdStepTime);
                currTc.setStep(4, Step::FINAL, currentFinalStepTemp, currentFinalStepTime);
                currTc.setFinalHoldTemp(currentFinalHoldTemp);
                thermocyclerArray.modifyElement(currentThermocyclerArrayIndex, currTc);

                // Go back to saved experiment to see if new thermocycler has been saved
                setPageState(PageManager::SAVED_EXPERIMENT);
                resetSubpage();
                displaySavedExperiment();
            }
            else if (key == 'B')
            {
                resetSubpage();
                displayEditExperiment();
            }
            else if (key == 'C')
            {
                handleReturnMenuSelection();
            }
        }
        else
        {
            displayEditExperiment(key);
        }
    }
}

void PageManager::handleDelExperimentSelection(char key)
{
    if (key == '>' || key == 'A')
    {
        switch (getCurrentSubpage())
        {
        case 0:
            // Delete thermocyclerArray element
            thermocyclerArray.deleteElement(currentThermocyclerArrayIndex);
            nextSubpage();
            displayDelExperiment();
            break;
        default:
            handleReturnMenuSelection();
            break;
        }
    }
    else if (key == '<')
    {
        switch (getCurrentSubpage())
        {
        case 0:
            // Go back to saved experiment option
            currentState = SAVED_EXPERIMENT;
            setPageState(PageManager::SAVED_EXPERIMENT);
            setCurrentSubPage(1);
            displaySavedExperiment();
            break;
        default:
            handleReturnMenuSelection();
            break;
        }
    }
    else
    {
        switch (getCurrentSubpage())
        {
        case 0:
            if (key == 'B')
            {
                // Go back to saved experiment list
                currentState = SAVED_EXPERIMENT;
                setCurrentSubPage(0);
                displaySavedExperiment();
            }
            break;
        default:
            handleReturnMenuSelection();
            break;
        }
    }
}