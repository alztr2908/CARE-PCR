#ifndef EDITEXPERIMENTPAGE_H
#define EDITEXPERIMENTPAGE_H

#include <Arduino.h>

void displayEditExperiment(char key = '\0');
bool parseStringFloat(String num);
void changeOption(int index, char key);

#endif