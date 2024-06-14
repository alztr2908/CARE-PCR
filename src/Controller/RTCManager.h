#ifndef RTCMANAGER_H
#define RTCMANAGER_H

#include <Ds1302.h>

class RTCManager
{
public:
    RTCManager(int pinEna, int pinClk, int pinDat);
    void begin();
    void updateTime();
    char *displayDateFilename();

private:
    Ds1302 rtc;
    Ds1302::DateTime now;
};

#endif // RTCMANAGER_H
