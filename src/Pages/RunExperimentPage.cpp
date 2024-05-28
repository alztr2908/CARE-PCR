#include "RunExperimentPage.h"
#include "../Utils/PageManager.h"
#include "../Utils/LCDManager.h"

void displayRunExperiment(char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("AAA");

    switch (pageManager.getCurrentSubpage())
    {
    case 0:
        lcd.setCursor(12, 0);
        lcd.printWord("hh:mm:ss");
        lcd.setCursor(0, 1);
        lcd.printWord("Temp:95degC");
        lcd.setCursor(0, 2);
        lcd.printWord("Rem cycle:28");
        lcd.setCursor(0, 3);
        lcd.printWord("STEP: 1 >> 30s");
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