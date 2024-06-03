#include "PageManager.h"
#include "../GlobalDeclarations.h"

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

void PageManager::clearIntArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = 0; // Reset each element to 0
    }
}

void PageManager::clearFloatArray(float *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = 0.0; // Reset each element to 0
    }
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

            if ((thermocyclerArray.isThermocyclerArrayFull()) && (!thermocyclerArray.checkThermocyclerArrayName(currentProgName)) && (currentProgName != ""))
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
                newProgName = "";
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
            int index = -1;

            if (key == 'A')
            {
                index = 0;
            }
            else if (key == 'B')
            {
                index = 1;
            }
            else if (key == 'C')
            {
                index = 2;
            }

            if (index != -1)
            {
                currentProgName = thermocyclerArray.getElement(index).getProgName();
                currentThermocyclerArrayIndex = index;

                if (currentProgName == "")
                {
                    setPageState(PageManager::NEW_EXPERIMENT);
                    resetSubpage();
                    displayNewExperiment();
                }
                else
                {
                    nextSubpage();
                    displaySavedExperiment();
                }
            }
        }

        else if (getCurrentSubpage() == 1)
        {
            if (key == 'A')
            {
                // Implement Run logic here
                setPageState(PageManager::RUN_EXPERIMENT_RUN);
                resetSubpage();

                // Put thermocycling step params at placeholder to call at reset
                Thermocycler currentThermocycler = thermocyclerArray.getElement(currentThermocyclerArrayIndex);
                currentCycleNo = currentThermocycler.getNumCycles();

                Step currentStep;
                for (int i = 0; i < 5; i++)
                {
                    currentStep = currentThermocycler.getStep(i);
                    stepTempHolder[i] = currentStep.getStepTemperature();
                    stepTimeHolder[i] = currentStep.getStepTime();
                }

                // Init time
                timeElapsedinS = 0;

                // Init block temperature.
                // Block temp reading simulation temp and will  setProgState (ERunning or ERamp)
                currentBlockTempReading = ThermocyclerInitialTemp;
                if (currentThermocycler.getStep(0).getStepTemperature() == currentBlockTempReading)
                {
                    currentThermocycler.setProgType(Thermocycler::ERunning);
                }
                else
                {
                    currentThermocycler.setProgType(Thermocycler::ERamp);
                }
                thermocyclerArray.modifyElement(currentThermocyclerArrayIndex, currentThermocycler);

                // Start the program
                lcd.clear();
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
    if (key == '>')
    {
        if (getCurrentSubpage() > 0)
        {
            // Reset
            timeElapsedinS = 0;

            handleReturnMenuSelection();
        }
        else
        {
            nextSubpage();
            displayRunExperiment();
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
            displayRunExperiment();
        }
    }
    else
    {
        displayRunExperiment(key);
    }
}

void PageManager::handleEditExperimentSelection(char key)
{
    if (key == '>')
    {
        switch (getCurrentSubpage())
        {

        // Heated Lid
        case 0:
            currentHeatedLid = currentStringFirstVal.toFloat();
            currentStringFirstVal = "";
            nextSubpage();
            displayEditExperiment();
            break;

        // Initial Step
        // Step 1 - Denaturation
        // Step 2 - Annealing
        // Step 3 - Extension
        // Final Step
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            // Change Answer fields
            if (getCurrentAnswerField() == 1)
            {
                stepTimeHolder[stepArrayIndex] = currentStringSecondVal.toInt();

                currentStringFirstVal = "";
                currentStringSecondVal = "";
                stepArrayIndex++;
                currentAnswerField = 0;
                nextSubpage();
                displayEditExperiment();
            }
            else
            {
                stepTempHolder[stepArrayIndex] = atof(currentStringFirstVal.c_str()); // Convert string to float
                currentAnswerField++;
            }
            break;

        // Cycle No.
        case 2:
            currentCycleNo = currentStringFirstVal.toInt();
            currentStringFirstVal = "";
            nextSubpage();
            displayEditExperiment();
            break;

        // Final Hold
        case 7:
            currentFinalHoldTemp = currentStringFirstVal.toFloat();
            currentStringFirstVal = "";
            nextSubpage();
            displayEditExperiment();
            break;

        // Saving
        case 8:
            // Initialize and add the new/modified thermocycler
            Thermocycler currTc = thermocyclerArray.getElement(currentThermocyclerArrayIndex);
            currTc.setProgName(currentProgName);
            currTc.setHeatedLid(currentHeatedLid);
            currTc.setNumCycles(currentCycleNo);
            currTc.setFinalHoldTemp(currentFinalHoldTemp);

            currTc.setStep(0, Step::INITIAL, stepTempHolder[0], stepTimeHolder[0]);
            currTc.setStep(1, Step::DENATURATION, stepTempHolder[1], stepTimeHolder[1]);
            currTc.setStep(2, Step::ANNEALING, stepTempHolder[2], stepTimeHolder[2]);
            currTc.setStep(3, Step::EXTENDING, stepTempHolder[3], stepTimeHolder[3]);
            currTc.setStep(4, Step::FINAL, stepTempHolder[4], stepTimeHolder[4]);

            Serial.println("New Line");
            Serial.println(String(currTc.getStep(0).getStepTemperature()));
            Serial.println(String(currTc.getStep(1).getStepTemperature()));
            Serial.println(String(currTc.getStep(2).getStepTemperature()));
            Serial.println(String(currTc.getStep(3).getStepTemperature()));
            Serial.println(String(currTc.getStep(4).getStepTemperature()));
            thermocyclerArray.modifyElement(currentThermocyclerArrayIndex, currTc);

            // Clear and reset values
            clearFloatArray(stepTempHolder, 5);
            clearIntArray(stepTimeHolder, 5);
            stepArrayIndex = 0;
            currentCycleNo = 0;

            // Go back to saved experiment to see if new thermocycler has been saved
            setPageState(PageManager::SAVED_EXPERIMENT);
            resetSubpage();
            displaySavedExperiment();
            break;
        }
    }
    else if (key == '<')
    {
        switch (getCurrentSubpage())
        {
        case 0:
            // Clear and reset values
            clearFloatArray(stepTempHolder, 5);
            clearIntArray(stepTimeHolder, 5);
            stepArrayIndex = 0;
            currentCycleNo = 0;

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
                currTc.setNumCycles(currentCycleNo);
                currTc.setFinalHoldTemp(currentFinalHoldTemp);

                currTc.setStep(0, Step::INITIAL, stepTempHolder[0], stepTimeHolder[0]);
                currTc.setStep(1, Step::DENATURATION, stepTempHolder[1], stepTimeHolder[1]);
                currTc.setStep(2, Step::ANNEALING, stepTempHolder[2], stepTimeHolder[2]);
                currTc.setStep(3, Step::EXTENDING, stepTempHolder[3], stepTimeHolder[3]);
                currTc.setStep(4, Step::FINAL, stepTempHolder[4], stepTimeHolder[4]);

                thermocyclerArray.modifyElement(currentThermocyclerArrayIndex, currTc);

                // Clear and reset values
                clearFloatArray(stepTempHolder, 5);
                clearIntArray(stepTimeHolder, 5);
                stepArrayIndex = 0;
                currentCycleNo = 0;

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
                // Clear and reset values
                clearFloatArray(stepTempHolder, 5);
                clearIntArray(stepTimeHolder, 5);
                stepArrayIndex = 0;

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