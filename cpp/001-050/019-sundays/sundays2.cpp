#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

http://www.bbc.co.uk/dna/h2g2/A22548314

*/

const char *DAYS_OF_WEEK[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//#define ENDYEAR 1905
#define ENDYEAR 2000

int getDayOfWeekOld(int year, int month, int day) {
    const int M_ARRAY[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    int century = year / 100;
    int y = year % 100;
    int m = M_ARRAY[month];
    int c, l;
    l = y / 4;
    switch(century) {
        case 19:
            c = 0;
            break;
        case 20:
            c = 5;
            l++;
            break;
        default: fprintf(stderr, "Bad century\n"); return -1;
    }
    if (month <= 2)
        l--;
    return (c+y+l+m+day) % 7;
}

int getDayOfWeek(int year, int m, int d) {
    int c, y, result;
    //printf("For %04d-%02d-%02d:\n", year, m, d);
    // Translate to "March Years"
    if (m <= 2) {
        year--;
        m += 12;
    }
    c = year / 100;
    y = year % 100;
    //printf(" d=%d, m=%d, y=%d, c=%d\n", d, m, y, c);
    result = c / 4 - 2 * c - 1;
    result += 5 * y / 4;
    result += 26 * (m + 1) / 10;
    result += d;
    result %= 7;
    if (result < 0)
        result += 7;
    //printf(" result=%d\n", result);
    return result;
}

int main(int argc, char *argv) {
    unsigned int sundayCount = 0;
    int day;
    for (int year = 1901; year <= ENDYEAR; year++)
    {
        for (int month = 1; month <= 12; month++)
        {
            day = getDayOfWeek(year, month, 1);
            printf("%d-%02d-01 : %s\n", year, month, DAYS_OF_WEEK[day]);
            if (day == 0)
                sundayCount++;
        }
    }
    printf("Total Sundays on the first of the month==%d\n", sundayCount);
    return 0;
}

int mainold(int argc, char *argv) {
    unsigned int sundayCount = 0;
    struct tm timestruct, *newtimestruct;
    time_t timestamp;
    for (int year = 1901; year <= ENDYEAR; year++)
    {
        for (int month = 0; month < 12; month++)
        {
            memset(&timestruct, 0, sizeof(timestruct));
            timestruct.tm_hour = 0; // Let's make it noon in case any unwanted localtime adjustments don't push us into the next/previous day
            timestruct.tm_mday = 1;
            timestruct.tm_mon = month;
            timestruct.tm_year = year - 1900;
            timestamp = timegm(&timestruct);
            //newtimestruct = gmtime(&timestamp);
            printf("%d-%02d-01 : %s\n", year, month + 1, DAYS_OF_WEEK[timestruct.tm_wday]);
            if (timestruct.tm_wday == 0)
                sundayCount++;
        }
    }
    printf("Total Sundays on the first of the month==%d\n", sundayCount);
    return 0;
}
