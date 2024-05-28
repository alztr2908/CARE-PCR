#include "ThermocyclerArray.h"

ThermocyclerArray::ThermocyclerArray() {}

void ThermocyclerArray::addElement(int index, const Thermocycler &thermocycler)
{
    if (index >= 0 && index < 3)
    {
        thermocyclerArray[index] = thermocycler;
    }
}

void ThermocyclerArray::deleteElement(int index)
{
    if (index >= 0 && index < 3)
    {
        thermocyclerArray[index] = Thermocycler(); // Reset to a default thermocycler
    }
}

void ThermocyclerArray::modifyElement(int index, const Thermocycler &thermocycler)
{
    if (index >= 0 && index < 3)
    {
        thermocyclerArray[index] = thermocycler;
    }
}

Thermocycler ThermocyclerArray::getElement(int index)
{
    if (index >= 0 && index < 3)
    {
        return thermocyclerArray[index];
    }
}
