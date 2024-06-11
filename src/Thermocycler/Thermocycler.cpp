#include "Thermocycler.h"

Thermocycler::Thermocycler() : progName(""), finalHoldTemp(0.0), numCycles(0), ThermocyclingType(ERunning)
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

// EEPROM
// void Thermocycler::saveToEEPROM(int baseAddr)
// {
//     int addr = baseAddr;
//     EEPROM.put(addr, progName);
//     addr += sizeof(progName);
//     EEPROM.put(addr, finalHoldTemp);
//     addr += sizeof(finalHoldTemp);
//     EEPROM.put(addr, numCycles);
//     addr += sizeof(numCycles);
//     for (int i = 0; i < 5; i++)
//     {
//         EEPROM.put(addr, steps[i].getStepType());
//         addr += sizeof(steps[i].getStepType());
//         EEPROM.put(addr, steps[i].getStepTemperature());
//         addr += sizeof(steps[i].getStepTemperature());
//         EEPROM.put(addr, steps[i].getStepTime());
//         addr += sizeof(steps[i].getStepTime());
//     }
// }

// Thermocycler Thermocycler::loadFromEEPROM(int baseAddr)
// {
//     Thermocycler loadedTc;
//     int addr = baseAddr;

//     // Check if data exists at the base address
//     int dataCheck;
//     EEPROM.get(addr, dataCheck);

//     // If dataCheck is empty, initialize a default Thermocycler object
//     if (dataCheck == 0)
//     {
//         return loadedTc; // Return the default Thermocycler object
//     }

//     // Load data from EEPROM
//     EEPROM.get(addr, loadedTc.progName);
//     addr += sizeof(loadedTc.progName);
//     EEPROM.get(addr, loadedTc.finalHoldTemp);
//     addr += sizeof(loadedTc.finalHoldTemp);
//     EEPROM.get(addr, loadedTc.numCycles);
//     addr += sizeof(loadedTc.numCycles);

//     Step::StepType type;
//     float temp;
//     int time;
//     for (int i = 0; i < 5; i++)
//     {
//         EEPROM.get(addr, type);
//         addr += sizeof(type);
//         EEPROM.get(addr, temp);
//         addr += sizeof(temp);
//         EEPROM.get(addr, time);
//         addr += sizeof(time);
//         loadedTc.setStep(i, type, temp, time);
//     }

//     return loadedTc;
// }
