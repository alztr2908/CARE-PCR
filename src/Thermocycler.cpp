#include "Thermocycler.h"

Thermocycler::Thermocycler() : progName(""), heatedLid(0.0), finalHoldTemp(0.0), numCycles(0)
{
    // Initialize steps array to default values
    for (int i = 0; i < 6; ++i)
    {
        steps[i] = Step();
    }
}

void Thermocycler::setStep(int index, Step::StepType type, float temp, int time)
{
    Step currentStep;
    // Step::StepType currentStepType = type;
    // float currentStepTemp = temp;
    // int currentStepTime = time;

    if (index >= 0 && index < 6)
    {
        currentStep = steps[index];
        currentStep.setStepType(type);
        currentStep.setStepTemperature(temp);
        currentStep.setStepTime(time);

        // steps[index] = Step(type, temp, time);
    }
}

void Thermocycler::setProgName(String name)
{
    progName = name;
}

void Thermocycler::modifyStep(int index, Step::StepType type, float temp, int time)
{
    if (index >= 0 && index < 6)
    {
        steps[index].setStepType(type);
        steps[index].setStepTemperature(temp);
        steps[index].setStepTime(time);
    }
}
