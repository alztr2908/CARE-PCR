#ifndef GLOBALDECLARATIONS_H
#define GLOBALDECLARATIONS_H

#include "./Controller/LCDManager.h"
#include "./Controller/PageManager.h"
#include "./Controller/RTCManager.h"
#include "./Thermocycler/ThermocyclerArray.h"

extern LCDManager lcd;
extern PageManager pageManager;
extern ThermocyclerArray thermocyclerArray;
extern RTCManager rtc;

#endif
