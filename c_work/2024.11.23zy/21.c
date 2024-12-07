#include <stdio.h>
int is_leap_year(int year);
static char day_tab[2][13] = {
{0,31,28,31,30,31,30,31,31,30,31,30,31},
{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = is_leap_year(year);
    for (i = 1; i < month; i++)
        day += day_tab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    leap = is_leap_year(year);
    for (i = 1; yearday > day_tab[leap][i]; i++)
        yearday -= day_tab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

int is_leap_year(int year)
{
    int leap;
    leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)? 1 : 0;
    return leap;
}
