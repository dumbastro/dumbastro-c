/** @file julianday.h
    @brief Collection of algorithms related to the Julian Day

    From "Astronomical Algorithms", Chapter 7
*/
#include <stdbool.h>

/** @struct
* Represents a date
* with decimal day
*/
struct Date {
	short year; /*!< Represents the year */
	short month; /*!< Represents the month */
	double day; /*!< Represents the day as a double (to consider time) */
    char monthstr[10]; /*!< The string name of the month */
};

double jd(struct Date date);
struct Date date_from_jd(double jd);
struct Date set_month_str(struct Date *date);
int date_diff (struct Date first, struct Date second);
short get_week_day(struct Date date);
bool is_leap_year(short year);
short unsigned get_year_day(struct Date date);
