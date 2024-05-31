#ifndef _THERMOCYCLER_H
#define _THERMOCYCLER_H

#include "Step.h"
#include <Arduino.h> // Use Arduino String class

class Thermocycler
{
private:
    String progName;
    double heatedLid;
    Step steps[6]; // Fixed array of 6 steps
    float finalHoldTemp;
    int numCycles;

public:
    Thermocycler();

    // Functions used for setting the Step Parameters
    void setStep(int index, Step::StepType type, float temp, int time);
    void modifyStep(int index, Step::StepType type, float temp, int time);

    // Getters
    String getProgName() { return progName; }
    double getHeatedLid() { return heatedLid; }
    // const Step *getSteps() const { return steps; }
    float getFinalHoldTemp() { return finalHoldTemp; }
    int getNumCycles() { return numCycles; }

    // Setters
    void setProgName(String name);
    void setHeatedLid(double lid) { heatedLid = lid; }
    void setFinalHoldTemp(float temp) { finalHoldTemp = temp; }
    void setNumCycles(int cycles) { numCycles = cycles; }
};

#endif
