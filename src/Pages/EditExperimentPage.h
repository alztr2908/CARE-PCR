#ifndef EDITEXPERIMENTPAGE_H
#define EDITEXPERIMENTPAGE_H

#include <Arduino.h>

void displayEditExperiment(char key = '\0');
bool parseStringFloat(String num);
void changeOption(char key, String &currentVal);
const char *readProgmemString(const char *str);

#endif