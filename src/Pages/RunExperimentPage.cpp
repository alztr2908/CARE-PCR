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
        // ProgName
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(4, 0);
        lcd.printWord(String(currentArrayIndex));

        // clock
        lcd.setCursor(15, 0);
        lcd.printWord("11:59");

        // Step Type >> time set countdown
        pageManager.currentMillis = millis();
        currentStepType = currentStep.getStepType();
        currentStepTypeString = currentThermocycler.getStepTypeString(currentStepType);
        lcd.setCursor(0, 1);
        lcd.printWord(currentStepTypeString);
        lcd.setCursor(13, 1);
        lcd.printWord(">>  ");

        if (currentThermocycler.getNumCycles() > 0)
        {
            // Update the stepTime countdown
            pageManager.currentStepTime = currentStep.getStepTime(); // GLOBAL
            if (pageManager.currentMillis - pageManager.previousMillis >= 1000)
            {
                pageManager.previousMillis = pageManager.currentMillis;
                pageManager.timeElapsedinS++;

                // Decrement the step time holder if it's greater than 0
                if (pageManager.currentStepTime > 1)
                {
                    pageManager.currentStepTime--;
                    currentStep.setStepTime(pageManager.currentStepTime);

                    // Reflect the changes at thermocyclerArray (reverse initialization)
                    currentThermocycler.setStep(pageManager.stepArrayIndex, currentStepType, currentStep.getStepTemperature(), currentStep.getStepTime());

                    thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                }
                else
                {
                    // Move to the next step if the current step time has elapsed
                    pageManager.stepArrayIndex++;
                    if (pageManager.stepArrayIndex < 5)
                    {
                        currentStep = currentThermocycler.getStep(pageManager.stepArrayIndex);
                        pageManager.currentStepTime = currentStep.getStepTime();

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
                        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);

                        // reset to the first step
                        pageManager.stepArrayIndex = 0;

                        // lcd.clear();
                    }
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

        // Display the remaining step time
        if (pageManager.currentStepTime < 10)
        {
            lcd.printWord("0");
        }
        lcd.printWord(String(pageManager.currentStepTime));
        lcd.printWord("s");

        // Current block temp
        lcd.setCursor(6, 2);
        lcd.printWord("BLOCK: ");
        lcd.printWord(String(currentStep.getStepTemperature()));
        lcd.printWord(" C");

        // Cycle and elapsed time -> ProgType
        switch (currentThermocycler.getProgType())
        {
        case Thermocycler::ERunning:
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
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(0, 1);
        lcd.printWord("SUCCESSFUL!!");
        lcd.setCursor(0, 2);
        lcd.printWord(parseTimeElapse(pageManager.timeElapsedinS));
        lcd.setCursor(0, 3);
        lcd.printWord("A-Save B-Home");

        currentThermocycler.setProgType(Thermocycler::ERunning);
        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler); // Make sure to save the state
        break;
    case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(0, 1);
        lcd.printWord("NOT SUCCESSFUL!!");
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
