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
            .day = 15,
            .hour = 12,
            .minute = 51,
            .second = 02,
            .dow = Ds1302::DOW_SAT,
        };

        rtc.setDateTime(&dt);
    }
}

// Set the time on the RTC
// void RTCManager::setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t dow)
// {
//     Ds1302::DateTime dt = {year, month, day, hour, minute, second, dow};
//     rtc.setDateTime(&dt);
// }

// Update the current time from the RTC
void RTCManager::updateTime()
{
    rtc.getDateTime(&now);
}

// Print current time as file name for microSD
char *RTCManager::displayDateFilename()
{
    static uint8_t last_second = 0;
    char timeFilename[30];

    if (last_second != now.second)
    {
        last_second = now.second;

        /* "templog_YYYY-DD-MM_HHMMSS.csv" */
        sprintf(timeFilename, "templog_20%02d-%02d-%02d_%02d%02d%02d.csv", now.year, now.day, now.month, now.hour, now.minute, now.second);
    }

    return timeFilename;
}

char *RTCManager::displayClockTime()
{
    static uint8_t last_second = 0;
    char clockTime[6];

    if (last_second != now.second)
    {
        last_second = now.second;

        /* "templog_YYYY-DD-MM_HHMMSS.csv" */
        sprintf(clockTime, "%02d:%02d", now.hour, now.minute);
    }

    return clockTime;
}
