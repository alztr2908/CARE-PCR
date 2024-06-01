#include "RunExperimentPage.h"
#include "GlobalDeclarations.h"
#include <Arduino.h>

/*
Global
int stepArrayIndex = 0;
int currentStepTime;

const long interval = 1000;
unsigned long previousMillis;
unsigned long currentMillis;

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

        // Update the stepTime countdown
        pageManager.currentStepTime = currentStep.getStepTime(); // GLOBAL
        if (pageManager.currentMillis - pageManager.previousMillis >= 1000)
        {
            pageManager.previousMillis = pageManager.currentMillis;

            // Decrement the step time holder if it's greater than 0
            if (pageManager.currentStepTime > 0)
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
                    lcd.clear();
                    currentStep = currentThermocycler.getStep(pageManager.stepArrayIndex);
                    pageManager.currentStepTime = currentStep.getStepTime();
                }
                else
                {
                    // Handle end of all steps (reset or other logic)
                    pageManager.stepArrayIndex = 0; // For example, reset to the first step

                    // currentStep.setStepTime()

                    currentStep = currentThermocycler.getStep(pageManager.stepArrayIndex);
                    pageManager.currentStepTime = currentStep.getStepTime();
                }
            }
        }

        // Display the remaining step time
        if (pageManager.currentStepTime < 10)
        {
            lcd.printWord("0");
        }
        lcd.printWord(String(pageManager.currentStepTime));
        lcd.printWord("s");

        // Current block temp
        lcd.setCursor(9, 2);
        lcd.printWord("BLOCK: 95 C");

        // Cycle and elapsed time -> ProgType
        lcd.setCursor(0, 3);
        lcd.printWord(String(currentThermocycler.getNumCycles()));
        lcd.printWord(" of ");
        lcd.printWord(String(currentThermocycler.getNumCycles()));
        lcd.setCursor(12, 3);
        lcd.printWord("hh:mm:ss");
        break;
    case 1:
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.printWord("SUCCESSFUL!!");
        lcd.setCursor(0, 2);
        lcd.printWord("hh:mm:ss");
        lcd.setCursor(0, 3);
        lcd.printWord("A-Save B-Home");
        break;
    case 2:
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.printWord("NOT SUCCESSFUL!!");
        lcd.setCursor(0, 2);
        lcd.printWord("hh:mm:ss");
        lcd.setCursor(0, 3);
        lcd.printWord("A-Save B-Home");
        break;
    }
}

/******

case loop:
    CurrentStep = StepArray[index]
    currentTime = 0;

    if (currentTime <= (CurrentStep.time*1000)){
        PID();
        if (Plate.temp >= CurrentStep.temp) {
            currentTime = millis();
        }
    }

    if (index > 4){
        iCycle++;
        index = 0;
    } else {
        index++
    }

    if (iCycle >= TotalCycle) {
        STATE = final
        iCycle = 0
    }

case final:
    CurrentStep = StepArray[Final]
    currentTime = 0;

    if (currentTime <= (CurrentStep.time*1000)){
        PID();
        if (Plate.temp >= CurrentStep.temp) {
            currentTime = millis();
        }
    }
******/