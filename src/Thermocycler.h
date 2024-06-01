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
    };

    Thermocycler();

    // Getters
    String getProgName() { return progName; }
    double getHeatedLid() { return heatedLid; }
    // const Step *getSteps() const { return steps; }
    float getFinalHoldTemp() { return finalHoldTemp; }
    int getNumCycles() { return numCycles; }
    Step getStep(int index);
    String getStepTypeString(Step::StepType stepType);
    ProgramType getProgType() { return ThermocyclingType; }

    // Setters
    void setProgName(String name);
    void setHeatedLid(double lid) { heatedLid = lid; }
    void setFinalHoldTemp(float temp) { finalHoldTemp = temp; }
    void setNumCycles(int cycles) { numCycles = cycles; }
    void setStep(int index, Step::StepType type, float temp, int time);
    void setStepParams(int index, Step step);
    void setProgType(ProgramType type) { ThermocyclingType = type; }

private:
    String progName;
    ProgramType ThermocyclingType;
    double heatedLid;
    Step steps[5]; // Fixed array of 6 steps
    float finalHoldTemp;
    int numCycles;
};

#endif
