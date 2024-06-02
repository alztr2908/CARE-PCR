#include "Thermocycler.h"

Thermocycler::Thermocycler() : progName(""), heatedLid(0.0), finalHoldTemp(0.0), numCycles(0), ThermocyclingType(ERunning)
{
    // Initialize steps array to default values
    for (int i = 0; i < 5; ++i)
    {
        steps[i] = Step();
    }
}

Step Thermocycler::getStep(int index)
{
    return steps[index];
}

void Thermocycler::setStep(int index, Step::StepType type, float temp, int time)
{
    Step currentStep;
    // Step::StepType currentStepType = type;
    // float currentStepTemp = temp;
    // int currentStepTime = time;

    if (index >= 0 && index < 5)
    {
        // currentStep = steps[index];
        steps[index].setStepType(type);
        steps[index].setStepTemperature(temp);
        steps[index].setStepTime(time);

        // steps[index] = Step(type, temp, time);
    }
}

void Thermocycler::setStepParams(int index, Step step)
{
    steps[index] = step;
}

String Thermocycler::getStepTypeString(Step::StepType stepType)
{
    switch (stepType)
    {
    case Step::INITIAL:
        return "INITIAL";
    case Step::DENATURATION:
        return "DENATURATION";
    case Step::ANNEALING:
        return "ANNEALING";
    case Step::EXTENDING:
        return "EXTENDING";
    case Step::FINAL:
        return "FINAL";
    case Step::HOLD:
        return "HOLD";
    default:
        return "NONVAL";
    }
}

void Thermocycler::setProgName(String name)
{
    progName = name;
}
