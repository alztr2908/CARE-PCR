#include "RTCManager.h"
#include <Arduino.h>

// Define the extern instance
RTCManager rtc(2, 4, 3);

// Constructor
RTCManager::RTCManager(int pinEna, int pinClk, int pinDat) : rtc(pinEna, pinClk, pinDat) {}

// Initialize the RTC
void RTCManager::begin()
{
    rtc.init();

    // Test if clock is halted and set a date-time to start it
    if (rtc.isHalted())
    {
        Ds1302::DateTime dt = {
            .year = 24,
            .month = Ds1302::MONTH_JUN,
            .day = 17,
            .hour = 00,
            .minute = 38,
            .second = 30,
            .dow = Ds1302::DOW_MON,
        };
        rtc.setDateTime(&dt);
    }
}

// Update the current time from the RTC
void RTCManager::updateTime()
{
    rtc.getDateTime(&now);
}

// Print current time as file name for microSD
char *RTCManager::displayDateFilename()
{
    static uint8_t last_second = 0;
    static char timeFilename[10];

    if (last_second != now.second)
    {
        last_second = now.second;
        sprintf(timeFilename, "%02d%02d%02d.csv", now.hour, now.minute, now.second);
    }

    /* "HHMMSS.csv" */
    return timeFilename;
}