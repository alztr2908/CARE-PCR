#include "RunExperimentPage.h"
#include "GlobalDeclarations.h"
#include "../Thermocycler/ThermocyclerOperation.h"
#include <Arduino.h>
#include "utils.h"

/*
Global
int stepArrayIndex = 0;
int currentStepTime;

const long interval = 1000;
unsigned long previousMillis;
unsigned long currentMillis;
unsigned long timeElapsedinS; // Add this if it is not declared
*/

const char currentStepTypeList[6][13] PROGMEM = {"INITIAL", "DENATURATION", "ANNEALING", "EXTENDING", "FINAL", "HOLD"};

const char TEMP_FORM_STR[] PROGMEM = "%4f C";

void displayRunExperiment(char key)
{
    // Strings
    char setPointTempStr[16];
    char blkTempStr[16];

    // lcd.printWord(String(pageManager.currentBlockTempReading));
    // lcd.delay(1000);
    int currentArrayIndex = pageManager.currentThermocyclerArrayIndex;
    // int currentArrayIndex = 0;
    Thermocycler currentThermocycler = thermocyclerArray.getElement(currentArrayIndex);
    Step currentStep = currentThermocycler.getStep(pageManager.stepArrayIndex);
    Step::StepType currentStepType;

    float finalTempReading;

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        /* LOGIC */

        // Update the stepTime countdown to do Thermocycler Operation
        pageManager.currentMillis = millis();
        pageManager.currentStepTime = currentStep.getStepTime();

        if (pageManager.currentMillis - pageManager.previousMillis >= 1000)
        {
            pageManager.previousMillis = pageManager.currentMillis;
            pageManager.timeElapsedinS++;

            if (pageManager.stepArrayIndex < 4)
            {
                PCR_PID(pageManager.currentBlockTempReading, currentStep.getStepTemperature());
            }
            else
            {
                PCR_PID(pageManager.currentBlockTempReading, currentThermocycler.getFinalHoldTemp());
            }

            // Put block temp reading into PID

            // Cycle Decrement
            if (currentThermocycler.getNumCycles() > 0)
            {
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
                        // until 4 only so that final step won't be included
                        if (pageManager.stepArrayIndex < 4)
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

                            // If final temp == current blk temp
                            if (currentThermocycler.getStep(4).getStepTemperature() == pageManager.blockPWMInput)
                            {
                                currentThermocycler.setProgType(Thermocycler::ERunning);
                            }
                            else
                            {
                                currentThermocycler.setProgType(Thermocycler::ERamp);
                            }
                            lcd.clear();

                            // reset to the first step which is 1st index (not initial idx = 0)
                            // 0th cycle proceed to final step
                            if (currentThermocycler.getNumCycles() < 1)
                            {
                                pageManager.stepArrayIndex = 4;
                            }
                            else
                            {
                                pageManager.stepArrayIndex = 1;
                            }

                            thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                        }
                    }
                    break;
                // ERamp: inc/dec curentBlockTempReading depends on target temp
                case Thermocycler::ERamp:
                    if (absf(pageManager.blockPWMInput) > currentStep.getStepTemperature())
                    {
                        pageManager.currentRampDirection = false;
                    }
                    else if (absf(pageManager.blockPWMInput) < currentStep.getStepTemperature())
                    {
                        pageManager.currentRampDirection = true;
                    }
                    else if (absf(pageManager.blockPWMInput) == currentStep.getStepTemperature())
                    {
                        currentThermocycler.setProgType(Thermocycler::ERunning);

                        // Reduce counter for accurate reading
                        pageManager.timeElapsedinS--;
                        lcd.clear();
                    }

                    thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                    break;

                case Thermocycler::EComplete:
                    break;
                }
            }
            else
            {
                switch (currentThermocycler.getProgType())
                {
                case Thermocycler::ERunning:
                    // For Final Step Time
                    if (pageManager.currentStepTime > 1)
                    {
                        pageManager.currentStepTime--;
                        currentStep.setStepTime(pageManager.currentStepTime);

                        currentThermocycler.setStep(pageManager.stepArrayIndex, currentStepType, currentStep.getStepTemperature(), currentStep.getStepTime());

                        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                    }
                    else
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            currentStep = currentThermocycler.getStep(i);
                            currentStep.setStepTemperature(pageManager.stepTempHolder[i]);
                            currentStep.setStepTime(pageManager.stepTimeHolder[i]);
                            currentThermocycler.setStepParams(i, currentStep);
                        }

                        pageManager.stepArrayIndex = 0;

                        // At final step, compare to final temp.. if equal to hold then EComplete. ERamp if not
                        if (currentThermocycler.getFinalHoldTemp() == pageManager.blockPWMInput)
                        {
                            currentThermocycler.setProgType(Thermocycler::EComplete);
                        }
                        else
                        {
                            currentThermocycler.setProgType(Thermocycler::ERamp);
                        }
                        // Reduce counter for correct timing
                        pageManager.timeElapsedinS--;
                        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                        lcd.clear();
                    }
                    break;
                case Thermocycler::ERamp:
                    if (pageManager.stepArrayIndex == 4)
                    {
                        finalTempReading = currentStep.getStepTemperature();
                    }
                    else
                    {
                        finalTempReading = currentThermocycler.getFinalHoldTemp();
                    }

                    if (absf(pageManager.blockPWMInput) > finalTempReading)
                    {
                        pageManager.currentRampDirection = false;
                    }
                    else if (absf(pageManager.blockPWMInput < finalTempReading))
                    {
                        pageManager.currentRampDirection = true;
                    }
                    else if (absf(pageManager.blockPWMInput == finalTempReading))
                    {
                        // Final step transition or final hold
                        if (pageManager.stepArrayIndex == 4)
                        {
                            currentThermocycler.setProgType(Thermocycler::ERunning);
                        }
                        else
                        {
                            currentThermocycler.setProgType(Thermocycler::EComplete);
                        }
                        // Reduce counter for correct timing
                        pageManager.timeElapsedinS--;
                        thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);
                        lcd.clear();
                    }

                    break;
                case Thermocycler::EComplete:
                    currentThermocycler.setNumCycles(pageManager.currentCycleNo);
                    pageManager.setPageState(PageManager::RUN_EXPERIMENT_NOTRUN);

                    for (int i = 0; i < 5; i++)
                    {
                        currentStep = currentThermocycler.getStep(i);
                        currentStep.setStepTemperature(pageManager.stepTempHolder[i]);
                        currentStep.setStepTime(pageManager.stepTimeHolder[i]);
                        currentThermocycler.setStepParams(i, currentStep);
                    }
                    thermocyclerArray.modifyElement(currentArrayIndex, currentThermocycler);

                    // Turn off peltier and heater
                    analogWrite(9, 0);
                    analogWrite(10, 0);
                    analogWrite(11, 0);

                    // reset to the first step
                    pageManager.stepArrayIndex = 0;
                    break;
                }
            }
        }

        /**************************************************/
        /* DISPLAY */

        /* FIRST ROW */
        // ProgName
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(4, 0);
        lcd.printWord(String(currentArrayIndex));
        // Setpoint
        lcd.setCursor(15, 0);
        if (pageManager.stepArrayIndex < 4)
        {
            lcd.printWord(String(currentStep.getStepTemperature()));
        }
        else
        {
            if (Thermocycler::EComplete)
            {
                lcd.printWord(rps(currentStepTypeList[5]));
            }
            else
            {
                lcd.printWord(String(currentThermocycler.getFinalHoldTemp()));
            }
        }
        // lcd.printWord("11:59");

        /* SECOND ROW*/
        switch (currentThermocycler.getProgType())
        {
        case Thermocycler::ERunning:
            // Step Type >> time set countdown
            lcd.setCursor(0, 1);
            lcd.printWord(rps(currentStepTypeList[pageManager.stepArrayIndex]));
            lcd.setCursor(13, 1);
            lcd.printWord(F(">>  "));
            // Display the remaining step time
            if (pageManager.currentStepTime < 10)
            {
                lcd.printWord(F("0"));
            }
            lcd.printWord(String(pageManager.currentStepTime));
            lcd.printWord(F("s"));
            break;
        case Thermocycler::EComplete:
            lcd.setCursor(0, 1);
            lcd.printWord(F("FINAL HOLD: "));
            lcd.printWord(String(currentThermocycler.getFinalHoldTemp()));
            lcd.printWord(F(" C"));
            break;
        case Thermocycler::ERamp:
            lcd.setCursor(0, 1);
            lcd.printWord(F("RAMP"));
            if (pageManager.currentRampDirection)
            {
                lcd.printWord(F("++ "));
            }
            else
            {
                lcd.printWord(F("-- "));
            }
            if (currentThermocycler.getNumCycles() > 0)
            {
                lcd.printWord(rps(currentStepTypeList[pageManager.stepArrayIndex]));
            }
            else
            {
                if (pageManager.stepArrayIndex != 4)
                {
                    lcd.printWord(F("TO "));
                    lcd.printWord(String(currentThermocycler.getFinalHoldTemp()));
                    lcd.printWord(F(" C"));
                }
                else
                {

                    lcd.printWord(rps(currentStepTypeList[4]));
                }
            }
            break;
        }

        /* THIRD ROW */
        // Current block temp
        lcd.setCursor(6, 2);
        lcd.printWord(F("BLOCK: "));
        // lcd.printWord(String(pageManager.currentBlockTempReading));
        lcd.printWord(String(absf(pageManager.blockPWMInput)));
        // lcd.printWord(F(" C"));

        /* FOURTH ROW */
        // Cycle and elapsed time -> ProgType
        switch (currentThermocycler.getProgType())
        {
        case Thermocycler::ERunning:
        case Thermocycler::ERamp:
            // lcd.setCursor(0, 3);
            // lcd.printWord("In:");
            // lcd.printWord(String(pageManager.blockPWMInput));

            // lcd.setCursor(10, 3);
            // lcd.printWord("Out:");
            // lcd.printWord(String(pageManager.blockPWMOutput));
            lcd.setCursor(0, 3);
            lcd.printWord(String(currentThermocycler.getNumCycles()));
            lcd.printWord(" of ");
            lcd.printWord(String(pageManager.currentCycleNo));
            lcd.setCursor(12, 3);
            lcd.printWord(parseTimeElapse(pageManager.timeElapsedinS));
            break;
        case Thermocycler::EComplete:
            lcd.setCursor(0, 3);
            lcd.printWord(F("*** Run Complete ***"));
            break;
        }
        break;

    case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printWord(currentThermocycler.getProgName());
        lcd.setCursor(0, 1);

        lcd.printWord(F("DATA SAVED"));

        lcd.setCursor(0, 2);
        lcd.printWord(parseTimeElapse(pageManager.timeElapsedinS));
        lcd.setCursor(0, 3);

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