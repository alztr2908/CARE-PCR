#ifndef _THERMOCYCLER_H
#define _THERMOCYCLER_H

#include "Step.h"
#include <Arduino.h> // Use Arduino String class

class Thermocycler
{
public:
    enum ProgramType
    {
        ERunning,
        EComplete,
        ERamp,
    };

    Thermocycler();

    // Getters
    String getProgName() { return progName; }
    float getFinalHoldTemp() { return finalHoldTemp; }
    int getNumCycles() { return numCycles; }
    Step getStep(int index);
    String getStepTypeString(Step::StepType stepType);
    ProgramType getProgType() { return ThermocyclingType; }

    // Setters
    void setProgName(String name);
    void setFinalHoldTemp(float temp) { finalHoldTemp = temp; }
    void setNumCycles(int cycles) { numCycles = cycles; }
    void setStep(int index, Step::StepType type, float temp, int time);
    void setStepParams(int index, Step step);
    void setProgType(ProgramType type) { ThermocyclingType = type; }

    // EEPROM
    void saveToEEPROM(int baseAddr);
    Thermocycler loadFromEEPROM(int baseAddr);

private:
    String progName;
    ProgramType ThermocyclingType;
    Step steps[5]; // Fixed array of 6 steps
    float finalHoldTemp;
    int numCycles;
};

#endif
