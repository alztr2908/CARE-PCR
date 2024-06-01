#include "RunExperimentPage.h"
#include "GlobalDeclarations.h"
#include <Arduino.h>

void displayRunExperiment(char key)
{
    int currentArrayIndex = pageManager.currentThermocyclerArrayIndex;
    Thermocycler currentThermocycler = thermocyclerArray.getElement(currentArrayIndex);

    Step::StepType currentStepType;
    String currentStepTypeString;

    lcd.clear();

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
        currentStepType = currentThermocycler.getStep(0).getStepType();
        currentStepTypeString = currentThermocycler.getStepTypeString(currentStepType);
        lcd.setCursor(0, 1);
        lcd.printWord(currentStepTypeString);
        lcd.setCursor(13, 1);
        lcd.printWord(">>  ");
        lcd.printWord(String(currentThermocycler.getStep(0).getStepTime()));
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
        lcd.setCursor(0, 1);
        lcd.printWord("SUCCESSFUL!!");
        lcd.setCursor(0, 2);
        lcd.printWord("hh:mm:ss");
        lcd.setCursor(0, 3);
        lcd.printWord("A-Save B-Home");
        break;
    case 2:
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