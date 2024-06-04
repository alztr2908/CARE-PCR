#ifndef THERMOCYCLEROPERATION_h
#define THERMOCYCLEROPERATION_h

void PCR_PID(double actualTemp);
float ReadTemp();
float ConvertToTemp(float r_ntc);

#endif