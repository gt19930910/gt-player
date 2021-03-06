#include "util_time.h"

#ifdef WIN32
#include <winsock2.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

/**
 * @brief get_millisecond
 * @return ���غ���
 */
int64_t get_current_time_msec()
{
#ifdef _WIN32
    struct timeval tv;
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;

    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tv.tv_sec = clock;
    tv.tv_usec = wtm.wMilliseconds * 1000;
    return ((int64_t)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#else
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return ((int64_t)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#endif
}
