#include "utils.h"
#include <avr/pgmspace.h>

char *rps(const char *progString)
{
    static char buf[21];
    strcpy_P(buf, progString);
    return buf;
}