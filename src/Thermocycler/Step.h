#ifndef _STEP_H
#define _STEP_H

class Step
{
public:
    enum StepType
    {
        NONVAL,
        INITIAL,
        DENATURATION,
        ANNEALING,
        EXTENDING,
        FINAL,
        HOLD,
    };

    Step();

    StepType getStepType();
    float getStepTemperature();
    int getStepTime();

    void setStepType(StepType t);
    void setStepTemperature(float temp);
    void setStepTime(int tm);

private:
    StepType type;
    float stepTemperature;
    int stepTime;
};

#endif // _STEP_H
