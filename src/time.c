#include "dumbastro.h"

/** @file time.c
    @brief Functions related to (astronomical) time

    From "Astronomical Algorithms", Chapter 11 _Sidereal Time at Greenwich_
    and Chapters ...
*/

/**
* Calculates the mean hour angle
* (sidereal time) at Greenwich
* using formula (11.4)
* @returns The hour angle in degrees
*/
double g_mean_ha(struct Date date, bool in_hours) {
    double jday = jd(date);
    double T = (jday - 2451545.) / 36525.;

    double ha = 280.46061837 + 360.985647366299 * (jday - 2451545.) + \
        + 0.000387933*T*T - (T*T*T) / 38710000.;

    if (in_hours) ha = (ha + 1677960.) / 15.;

    return ha;
}
