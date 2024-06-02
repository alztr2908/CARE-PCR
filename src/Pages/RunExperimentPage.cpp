#include "RunExperimentPage.h"
#include "GlobalDeclarations.h"

/*
Global
int stepArrayIndex = 0;
int currentStepTime;

const long interval = 1000;
unsigned long previousMillis;
unsigned long currentMillis;
unsigned long timeElapsedinS; // Add this if it is not declared
*/

void displayRunExperiment(char key)
{
    int currentArrayIndex = pageManager.currentThermocyclerArrayIndex;
    Thermocycler currentThermocycler = thermocyclerArray.getElement(currentArrayIndex);
    Step currentStep = currentThermocycler.getStep(pageManager.stepArrayIndex);

    Step::StepType currentStepType;
    String currentStepTypeString;

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        /* LOGIC */
        pageManager.currentMillis = millis();
        currentStepType = currentStep.getStepType();
        currentStepTypeString = currentThermocycler.getStepTypeString(currentStepType);

        if (currentThermocycler.getNumCycles() > 0)
        {
            // Update the stepTime countdown
            pageManager.currentStepTime = currentStep.getStepTime();
            if (pageManager.currentMillis - pageManager.previousMillis >= 1000)
            {
                pageManager.previousMillis = pageManager.currentMillis;
                pageManager.timeElapsedinS++;

                // Operation
                switch (currentThermocycler.getProgType())
                {
                // ERunning: Decrement the step time holder if it's greater than 0
                case Thermocycler::ERunning:
                    // Reflect the changes at thermocyclerArray (reverse initialization)
                    if (pageManager.currentStepTime > 1)
                    {
                        pageManager.currentStepTime--;
                        currentStep.setStepTime(pageManager.currentStepTime);

                        currentThermocycler.setStep(pageManager.stepArrayIndex, currentStepType, currentStep.getStepTemperature(), currentStep.getStepTime());

                        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                    }
                    else
                    {
                        pageManager.stepArrayIndex++;

                        // Move to the next step if the current step time has elapsed
                        if (pageManager.stepArrayIndex < 5)
                        {
                            currentStep = currentThermocycler.getStep(pageManager.stepArrayIndex);
                            pageManager.currentStepTime = currentStep.getStepTime();

                            // New temp <- Ramp again
                            currentThermocycler.setProgType(Thermocycler::ERamp);
                            thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                            lcd.clear();
                        }

                        // One cycle down
                        else
                        {
                            // Reset values at Step then reflect it on thermocyclerArray
                            currentThermocycler.setNumCycles(currentThermocycler.getNumCycles() - 1);
                            for (int i = 0; i < 5; i++)
                            {
                                currentStep = currentThermocycler.getStep(i);
                                currentStep.setStepTemperature(pageManager.stepTempHolder[i]);
                                currentStep.setStepTime(pageManager.stepTimeHolder[i]);
                                currentThermocycler.setStepParams(i, currentStep);
                            }

                            // New temp <- Ramp/Run again
                            if (currentThermocycler.getStep(0).getStepTemperature() == pageManager.currentBlockTempReading)
                            {
                                currentThermocycler.setProgType(Thermocycler::ERunning);
                            }
                            else
                            {
                                currentThermocycler.setProgType(Thermocycler::ERamp);
                                lcd.clear();
                            }

                            thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);

                            // reset to the first step
                            pageManager.stepArrayIndex = 0;
                        }
                    }
                    break;
                // ERamp: inc/dec curentBlockTempReading depends on target temp
                case Thermocycler::ERamp:
                    if (pageManager.currentBlockTempReading > currentStep.getStepTemperature())
                    {
                        pageManager.currentRampDirection = false;
                        pageManager.currentBlockTempReading--;
                    }
                    else if (pageManager.currentBlockTempReading < currentStep.getStepTemperature())
                    {
                        pageManager.currentRampDirection = true;
                        pageManager.currentBlockTempReading++;
                    }
                    else
                    {
                        currentThermocycler.setProgType(Thermocycler::ERunning);

                        // Reduce counter for accurate reading
                        pageManager.timeElapsedinS--;
                        lcd.clear();
                    }

                    thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                    break;
                }
            }
        }
        else
        {
            currentThermocycler.setNumCycles(pageManager.currentCycleNo);
            currentThermocycler.setProgType(Thermocycler::EComplete);
            pageManager.setPageState(PageManager::RUN_EXPERIMENT_NOTRUN);

            for (int i = 0; i < 5; i++)
            {
                currentStep = currentThermocycler.getStep(i);
                currentStep.setStepTemperature(pageManager.stepTempHolder[i]);
                currentStep.setStepTime(pageManager.stepTimeHolder[i]);
                currentThermocycler.setStepParams(i, currentStep);
            }
            thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);

            // reset to the first step
            pageManager.stepArrayIndex = 0;
        }

        /**************************************************/
        /* DISPLAY */

        /* FIRST ROW */
        // ProgName
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(4, 0);
        lcd.printWord(String(currentArrayIndex));
        // clock
        lcd.setCursor(15, 0);
        lcd.printWord("11:59");

        /* SECOND ROW*/
        switch (currentThermocycler.getProgType())
        {
        case Thermocycler::ERunning:
            // Step Type >> time set countdown
            lcd.setCursor(0, 1);
            lcd.printWord(currentStepTypeString);
            lcd.setCursor(13, 1);
            lcd.printWord(">>  ");
            // Display the remaining step time
            if (pageManager.currentStepTime < 10)
            {
                lcd.printWord("0");
            }
            lcd.printWord(String(pageManager.currentStepTime));
            lcd.printWord("s");
            break;
        case Thermocycler::EComplete:
            lcd.setCursor(0, 1);
            lcd.printWord("Final Hold");
            break;
        case Thermocycler::ERamp:
            lcd.setCursor(0, 1);
            lcd.printWord("RAMP");
            if (pageManager.currentRampDirection)
            {
                lcd.printWord("++ ");
            }
            else
            {
                lcd.printWord("-- ");
            }
            lcd.printWord(String(pageManager.stepArrayIndex));
            break;
        }

        /* THIRD ROW */
        // Current block temp
        lcd.setCursor(6, 2);
        lcd.printWord("BLOCK: ");
        lcd.printWord(String(pageManager.currentBlockTempReading));
        lcd.printWord(" C");

        /* FOURTH ROW */
        // Cycle and elapsed time -> ProgType
        switch (currentThermocycler.getProgType())
        {
        case Thermocycler::ERunning:
        case Thermocycler::ERamp:
            lcd.setCursor(0, 3);
            lcd.printWord(String(currentThermocycler.getNumCycles()));
            lcd.printWord(" of ");
            lcd.printWord(String(pageManager.currentCycleNo));
            lcd.setCursor(12, 3);
            lcd.printWord(parseTimeElapse(pageManager.timeElapsedinS));
            break;
        case Thermocycler::EComplete:
            lcd.setCursor(0, 3);
            lcd.printWord("*** Run Complete ***");
            break;
        }
        break;

    case 1:
    case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(0, 1);

        if (pageManager.getCurrentSubpage() == 1)
        {
            lcd.printWord("SUCCESSFUL!!");
        }
        else
        {
            lcd.printWord("NOT SUCCESSFUL!!");
        }
        lcd.setCursor(0, 2);
        lcd.printWord(parseTimeElapse(pageManager.timeElapsedinS));
        lcd.setCursor(0, 3);
        lcd.printWord("A-Save B-Home");

        currentThermocycler.setProgType(Thermocycler::ERunning);
        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler); // Make sure to save the state
        break;
    }
}

String parseTimeElapse(int time)
{
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;
    int seconds = time % 60;

    char buffer[9]; // HH:MM:SS format needs 9 characters (including null terminator)
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);

    return String(buffer);
}