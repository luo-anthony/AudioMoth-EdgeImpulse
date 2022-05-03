#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Time constants */

#define SECONDS_IN_DAY                  (1440 * 60)

#define MONTH_JAN                       1
#define MONTH_FEB                       2
#define MONTH_DEC                       12

#define DAYS_IN_YEAR                    365
#define UNIX_EPOCH_START                1970

/* Custom time functions */

static uint32_t timestamp;

static const uint32_t daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static inline bool isLeapYear(uint16_t year) {

    return (year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0);

}

static inline bool checkDate(uint32_t day, uint32_t month, uint32_t year) {

    timestamp = 0;

    if (month < MONTH_JAN || month > MONTH_DEC) return false;

    uint32_t dayInCurrentMonth =  daysInMonth[month - 1] + (month == MONTH_FEB && isLeapYear(year) ? 1 : 0);

    if (day == 0 || day > dayInCurrentMonth) return false;

    for (uint32_t y = UNIX_EPOCH_START; y < year; y += 1) timestamp += SECONDS_IN_DAY * (isLeapYear(y) ? DAYS_IN_YEAR + 1 : DAYS_IN_YEAR);

    for (uint32_t m = 0; m < month - 1; m += 1) timestamp += SECONDS_IN_DAY * daysInMonth[m];

    if (isLeapYear(year) && month > MONTH_FEB) timestamp += SECONDS_IN_DAY;

    timestamp += SECONDS_IN_DAY * (day - 1);

    return true;

}

/* Reference function from Eric S Raymond */

time_t my_timegm(register struct tm * t) {
    register long year;
    register time_t result;
    #define MONTHSPERYEAR   12      /* months per calendar year */
    static const int cumdays[MONTHSPERYEAR] =
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

    /*@ +matchanyintegral @*/
    year = 1900 + t->tm_year + t->tm_mon / MONTHSPERYEAR;
    result = (year - 1970) * 365 + cumdays[t->tm_mon % MONTHSPERYEAR];
    result += (year - 1968) / 4;
    result -= (year - 1900) / 100;
    result += (year - 1600) / 400;
    if ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0) &&
        (t->tm_mon % MONTHSPERYEAR) < 2)
        result--;
    result += t->tm_mday - 1;
    result *= 24;
    result += t->tm_hour;
    result *= 60;
    result += t->tm_min;
    result *= 60;
    result += t->tm_sec;
    if (t->tm_isdst == 1)
        result -= 3600;
    /*@ -matchanyintegral @*/
    return (result);
}

int main() {

    struct tm temp;

    for (int year = 2022; year < 2025; year += 1) {

        for (int month = 1; month < 13; month += 1) {

            uint32_t limit = daysInMonth[month - 1] + (isLeapYear(year) && month == 2 ? 1 : 0);

            for (int day = 1; day <= limit; day += 1) {

                bool okay = checkDate(day, month, year);

                temp.tm_year = year - 1900;
                temp.tm_mon = month - 1;
                temp.tm_mday = day;

                temp.tm_hour = 0;
                temp.tm_min = 0;
                temp.tm_sec = 0;

                uint32_t unix = (uint32_t)my_timegm(&temp);

                printf("%02d/%02d/%04d - %s - %u - %u - %s\n", day, month, year, okay ? "OK" : "ERROR", timestamp, unix, timestamp == unix ? "MATCH" : "DO NOT MATCH");

            }

        }

    }

}
