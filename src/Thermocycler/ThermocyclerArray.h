#ifndef THERMOCYCLERARRAY_H
#define THERMOCYCLERARRAY_H

#include "Thermocycler.h"

class ThermocyclerArray
{
private:
    Thermocycler thermocyclerArray[3]; // Fixed array of 3 thermocyclers

public:
    ThermocyclerArray();

    // Helper Functions
    bool isThermocyclerArrayFull();
    bool checkThermocyclerArrayName(String name);
    int emptyElementIndex();

    // Operation Functions
    void addElement(int index, Thermocycler thermocycler);
    void deleteElement(int index);
    void modifyElement(int index, Thermocycler thermocycler);
    Thermocycler getElement(int index);
};

#endif
