#ifndef _STEP_H
#define _STEP_H

class Step
{
public:
    enum StepType
    {
        DEFAULT,
        INITIAL,
        DENATURATION,
        ANNEALING,
        EXTENDING,
        FINAL,
        HOLD
    };

private:
    StepType type;
    float temperature;
    int time;

public:
    Step() : type(DEFAULT), temperature(0.0), time(0) {}
    Step(StepType t, float temp, int tm) : type(t), temperature(temp), time(tm) {}

    StepType getType() const { return type; }
    float getTemperature() const { return temperature; }
    int getTime() const { return time; }

    void setType(StepType t) { type = t; }
    void setTemperature(float temp) { temperature = temp; }
    void setTime(int tm) { time = tm; }
};

#endif
