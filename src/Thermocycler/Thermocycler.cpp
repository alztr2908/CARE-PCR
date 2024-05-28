#include "Thermocycler.h"

Thermocycler::Thermocycler() : progName(""), heatedLid(0.0), finalHoldTemp(0.0), numCycles(0)
{
    // Initialize steps array to default values
    Step defaultStep;
    for (int i = 0; i < 6; ++i)
    {
        steps[i] = defaultStep;
    }
}

void Thermocycler::SetStep(int index, Step::StepType type, float temp, int time)
{
    if (index >= 0 && index < 6)
    {
        steps[index] = Step(type, temp, time);
    }
}

void Thermocycler::ModifyStep(int index, Step::StepType type, float temp, int time)
{
    if (index >= 0 && index < 6)
    {
        steps[index].setType(type);
        steps[index].setTemperature(temp);
        steps[index].setTime(time);
    }
}
