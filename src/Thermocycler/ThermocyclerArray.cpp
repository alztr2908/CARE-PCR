#include "ThermocyclerArray.h"
#include "GlobalDeclarations.h"

// Define the extern instance
ThermocyclerArray thermocyclerArray;

ThermocyclerArray::ThermocyclerArray() {}

void ThermocyclerArray::addElement(int index, Thermocycler thermocycler)
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

void ThermocyclerArray::modifyElement(int index, Thermocycler thermocycler)
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
