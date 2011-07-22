#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
You are given the following information, but you may prefer to do some 
research for yourself.

    * 1 Jan 1900 was a Monday.
    * Thirty days has September,
      April, June and November.
      All the rest have thirty-one,
      Saving February alone,
      Which has twenty-eight, rain or shine.
      And on leap years, twenty-nine.
    * A leap year occurs on any year evenly divisible by 4, but not on a 
      century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth 
century (1 Jan 1901 to 31 Dec 2000)?

year - first day - last day - # of Sundays
1900 - Monday    - Monday   - 52
1901 - Tuesday   - Tuesday  - 52
1902 - Wednesday - Wednesday- 52
1903 - Thursday  - Thursday - 52
1904 - Friday    - Saturday - 52
1905 - Sunday    - Sunday   - 53 

http://www.timeanddate.com/calendar/index.html?year=1900&country=1
*/

#define SUNDAY      0
#define MONDAY      1
#define TUESDAY     2
#define WEDNESDAY   3
#define THURSDAY    4
#define FRIDAY      5
#define SATURDAY    6

const char *dayOfWeekToString(int dow)
{
    const char *daysOfWeek[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    if ((dow >= SUNDAY) && (dow <= SATURDAY))
        return daysOfWeek[dow];
    return "Unknown";
}

int isLeapYear(int year)
{
    if ((year % 4) == 0)
    {
        if ((year % 100) != 0)
            return 1;
        if ((year % 400) == 0)
            return 1;
    }
    return 0;
}

unsigned int sundaysInYear(int firstDay, int leapYear, int *firstDayOfFollowingYear)
{
    int result;
    int daysInYear = leapYear ? 366 : 365;
    result = (daysInYear - firstDay) / 7;
    if (((daysInYear + firstDay) % 7) > firstDay)
        result++;
    *firstDayOfFollowingYear = (daysInYear + firstDay) % 7;
    return result;
}

int main(int argc, char **argv)
{
    unsigned int sundays = 0;
    int firstDay = MONDAY;
    int firstDayOfNextYear;
    for (int year = 1900; year <= 1905; year++)
    {
        int thisSundays;
        if (year == 1901)
            sundays = 0;
        thisSundays = sundaysInYear(firstDay, isLeapYear(year), &firstDayOfNextYear);
        sundays += thisSundays;
        printf("%d%c %9s %9s %d %d\n", year, isLeapYear(year) ? 'L' : ' ', dayOfWeekToString(firstDay), dayOfWeekToString(firstDayOfNextYear), thisSundays, sundays);
        firstDay = firstDayOfNextYear;
    }
    printf("%d\n", sundays);
    return 0;
}
