#ifndef RTCMANAGER_H
#define RTCMANAGER_H

#include <Ds1302.h>

class RTCManager
{
public:
    RTCManager(int pinEna, int pinClk, int pinDat);
    void begin();
    // void setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t dow);
    void updateTime();
    char *displayDateFilename();

private:
    Ds1302 rtc;
    Ds1302::DateTime now;
    // const static char *WeekDays[7];
};

#endif // RTCMANAGER_H
