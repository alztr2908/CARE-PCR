#include "Step.h"

Step::Step() : type(NONVAL), stepTemperature(0.0), stepTime(0) {}

Step::StepType Step::getStepType()
{
    return type;
}

float Step::getStepTemperature()
{
    return stepTemperature;
}

int Step::getStepTime()
{
    return stepTime;
}

void Step::setStepType(StepType t)
{
    type = t;
}

void Step::setStepTemperature(float temp)
{
    stepTemperature = temp;
}

void Step::setStepTime(int tm)
{
    stepTime = tm;
}
