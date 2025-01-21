#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "julianday.h"

/**
 * @fn
 * Calculates Julian Day from calendar date
 * @param date The Date struct to convert to JD
 * @returns The Julian Day
*/
double jd(struct Date date) {
    short year = date.year;
    short month = date.month;
    double day = date.day;

    if (month == 1 || month == 2) {
	year = year - 1;
	month = month + 12;
    }

    int a = trunc(year / 100.0);
    int b = 2 - a + trunc(a / 4.0);

    // Should compare the date to
    // Gregorian reform...
    short is_jul_date = 
	    year < 1582 ||
	    (year == 1582 && month < 10) ||
	    (year == 1582 && month == 10 && day < 15);

    if (is_jul_date) { b = 0; }

    double jd = trunc(365.2500 * (year + 4716));

    jd += trunc(30.6001 * (month + 1)) + day + b - 1524.5000;

    return jd;
}
/**
 * @fn
 * Calculates calendar date from Julian Day  
 * _**NOTE**_: not valid for negative JD values
 * @param jd The Julian Day to be converted to Date
*/
struct Date date_from_jd(double jd) {
    int z = trunc(jd + 0.5);
    double f = jd + 0.5 - z;
    int a = 0, b = 0, c = 0, d = 0, e = 0;

    if (z < 2299161) a = z;
    if (z == 2299161 || z > 2299161) {
	int alpha = trunc((z - 1867216.25) / 36524.25);
	a = z + 1 + alpha - trunc(alpha / 4);
    }

    b = a + 1524;
    c = trunc((b - 122.1) / 365.25);
    d = trunc(365.25 * c);
    e = trunc((b - d) / 30.6001);

    double day = b - d - trunc(30.6001 * e) + f;
    short month; 
    short year;
    
    if (e < 14) month = e - 1;
    if (e == 14 || e == 15) month = e - 13;
    if (month > 2) year = c - 4716;
    if (month == 1 || month == 2) year = c - 4715;

    struct Date date = {.year = year, .month = month, .day = day};

    return date;
}
/**
* @fn
* Sets the English name for the month in
* a Date struct
* @param The Date struct where the month string
*        should be set
*/
struct Date set_month_str(struct Date *date) {
    char* test;

    switch (date->month) {
        case 1 :
            test = "January";
            break;
        case 2 :
            test = "February";
            break;
        case 3 :
            test = "March";
            break;
        case 4 :
            test = "April";
            break;
        case 5 :
            test = "May";
            break;
        case 6 :
            test = "June";
            break;
        case 7 :
            test = "July";
            break;
        case 8 :
            test = "August";
            break;
        case 9 :
            test = "September";
            break;
        case 10 :
            test = "October";
            break;
        case 11 :
            test = "November";
            break;
        case 12 :
            test = "December";
            break;
    }

    for (int c = 0; c < strlen(test); c++) {
        date->monthstr[c] = test[c];
    }

    return *date;
}
/**
* Returns the date difference in days
* @param first The first Date (smaller)
* @param second The second Date (larger)
*/
int date_diff(struct Date first, struct Date second) {
   double jd_first = jd(first); 
   double jd_second = jd(second); 
    
   return ceil(jd_second - jd_first);
}
/**
* Returns the week day as a number
* @param date The Date struct to find the week day from
*/
short get_week_day(struct Date date) {
   // Day should be taken at Oh
   //date.day = trunc(date.day) + 0.0;
   double altered_jd = jd(date) + 1.5; 

   return (int)altered_jd % 7;
}
/**
* Checks whether a given year is
* a leap year (Gregorian only!!)
* @param year The year to check
*/
bool is_leap_year(short year) {
    return (year % 4) == 0;
}
/**
* Returns the day number in the given year
 * @param date The Date struct to use
*/
short unsigned get_year_day(struct Date date) {
    short k = is_leap_year(date.year) ? 1 : 2;

    return trunc((275 * date.month) / 9)
        - k * trunc((date.month + 9) / 12)
        + trunc(date.day) - 30;
}


