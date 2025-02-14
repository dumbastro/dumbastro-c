#include <math.h>
#include "dumbastro.h"

// Mean obliquity of the ecliptic
const double mean_ecl_obl[] = {
    [0] = 23.4392911, //J2000
    [2] = 23.4457889, //B1950
};

// Days in a Julian century
const short unsigned JCENTURY = 36525;

/** @file coords.c
    @brief Functions related to coordinate transformations

    From "Astronomical Algorithms", Chapter 12 _Transformation of Coordinates_
*/

/**
* Calculates ecliptical longitude
* from equatorial coordinates
* @param alpha R.A. in decimal degrees
* @param delta DEC in decimal degrees
* @returns The ecliptical longitude in degrees
*/
double ecl_lon_from_eq(double alpha, double delta, Equinox eq) {
    double eps = 0.;

    // Default to J2000
    switch (eq) {
        case J2000:
        case JNOW:
            eps = mean_ecl_obl[J2000];
            break;
        case B1950:
            eps = mean_ecl_obl[B1950];
            break;
        default:
            eps = mean_ecl_obl[J2000];
            break;
    }
            
    double tan_lon = sin(alpha*RAD)*cos(eps*RAD) + tan(delta*RAD)*sin(eps*RAD);
    tan_lon /= cos(alpha*RAD);
    double lon = atan(tan_lon) * DEG;

    if (lon < 0) lon += 180;

    return lon;
}
/**
* Calculates ecliptical latitude
* from equatorial coordinates
* @param alpha R.A. in decimal degrees
* @param delta DEC in decimal degrees
* @returns The ecliptical latitude in degrees
*/
double ecl_lat_from_eq(double alpha, double delta, Equinox eq) {
    double eps = 0.;

    // Default to J2000
    switch (eq) {
        case J2000:
        case JNOW:
            eps = mean_ecl_obl[J2000];
            break;
        case B1950:
            eps = mean_ecl_obl[B1950];
            break;
        default:
            eps = mean_ecl_obl[J2000];
            break;
    }
            
    double sin_lat = sin(delta*RAD)*cos(eps*RAD) - cos(delta*RAD)*sin(eps*RAD)*sin(alpha*RAD);
    double lat = asin(sin_lat) * DEG;

    if (lat < 0) lat += 180;

    return lat;
}
/**
* Calculate R.A. from ecliptical coords
*/
double alpha_from_ecl(double lat, double lon, Equinox eq) {
    double eps = 0.;

    // Default to J2000
    switch (eq) {
        case J2000:
        case JNOW:
            eps = mean_ecl_obl[J2000];
            break;
        case B1950:
            eps = mean_ecl_obl[B1950];
            break;
        default:
            eps = mean_ecl_obl[J2000];
            break;
    }
            
    double tan_alpha = sin(lon*RAD)*cos(eps*RAD) - tan(lat*RAD)*sin(eps*RAD);
    tan_alpha /= cos(lon*RAD);
    double alpha = atan(tan_alpha) * DEG;

    if (alpha < 0) alpha += 180;

    return alpha;
}
/**
* Calculate dec from ecliptical coords
*/
double delta_from_ecl(double lat, double lon, Equinox eq) {
    double eps = 0.;

    // Default to J2000
    switch (eq) {
        case J2000:
        case JNOW:
            eps = mean_ecl_obl[J2000];
            break;
        case B1950:
            eps = mean_ecl_obl[B1950];
            break;
        default:
            eps = mean_ecl_obl[J2000];
            break;
    }
            
    double sin_delta = sin(lat*RAD)*cos(eps*RAD) + cos(lat*RAD)*sin(eps*RAD)*sin(lon*RAD);

    return asin(sin_delta) * DEG;
}
