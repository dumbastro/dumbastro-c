#include <math.h>
#include "dumbastro.h"

/** @file earth.c
    @brief Functions related to Earth's properties

    From "Astronomical Algorithms", Chapter 10 _The Earth's Globe_
*/

/**
* @fn
* Initializes an Earth structure
* @todo Even more useless??
*/
void set_earth_values(struct Earth * earth) {
	earth->a = EQ_RADIUS; 
	earth->f = FLATTENING; 
    earth->b = POL_RADIUS; 
	earth->e = MERID_ECC;
}
/**
* @fn
* Convert Latitude to decimal degrees
* @param lat The Latitude struct (sessagesimal)
* @returns The converted Latitude number
*/
double lat_to_dec(struct Latitude lat) {
    double dec_minutes = (double)lat.arcmins / 60.0;
    double dec_seconds = lat.arcsecs / 3600;

    short sign = lat.degrees < 0 ? -1 : 1;

    return lat.degrees + sign*(dec_minutes + dec_seconds);
}
/**
* @fn
* Convert Longitude to decimal degrees
* @param lon The Longitude struct (sessagesimal)
* @returns The converted Longitude number
*/
double lon_to_dec(struct Longitude lon) {
    double dec_minutes = (double)lon.arcmins / 60.0;
    double dec_seconds = (double)lon.arcsecs / 3600.0;

    short sign = lon.degrees < 0 ? -1 : 1;

    return lon.degrees + sign*(dec_minutes + dec_seconds);
}
/**
* @fn
* Calculates $\rho \sin{\phi}$ for
* a location
* @param h The location's height in meters
* @param decimal_lat The location's decimal latitude in degrees
*/
double rho_sin_phi(double h, double decimal_lat) {
    // Convert lat from deg to radians
    double lat_rad = decimal_lat * RAD;
    double tan_u = RAD_RATIO * tan(lat_rad);
    double u = atan(tan_u);
    double rho_sin_phi = RAD_RATIO * sin(u) + (h / 6378140.) * sin(lat_rad);

    return rho_sin_phi;
}
/**
* @fn
* Calculates $\rho \sin{\phi}$ for
* a location
* @param h The location's height in meters
* @param decimal_lat The location's decimal latitude in degrees
*/
double rho_cos_phi(double h, double decimal_lat) {
    // Convert lat from deg to radians
    double lat_rad = decimal_lat * RAD;
    double tan_u = RAD_RATIO * tan(lat_rad);
    double u = atan(tan_u);

    double rho_cos_phi = cos(u) + (h / 6378140) * cos(lat_rad);

    return rho_cos_phi;
}
/**
* @fn
* Calculates and sets geographical parameters
* related to a location
* @param loc The Location to set
* @param lat The location's Latitude
* @param h The location's height in meters
*/
struct Location set_location_params(struct Location * loc) {
    double decimal_lat = lat_to_dec(loc->lat);

    loc->r_sin_phi_p = rho_sin_phi(loc->h, decimal_lat);
    loc->r_cos_phi_p = rho_cos_phi(loc->h, decimal_lat);

    return *loc;
}
/**
* @fn
* Calculates the approximate linear distance between two points
* (Locations) on the Earth's surface (at sea level)
* @param loc1 First Location
* @param loc2 Second Location
*/
double distance(struct Location *loc1, struct Location *loc2) {
    double lat1 = lat_to_dec(loc1->lat) * RAD;
    double lat2 = lat_to_dec(loc2->lat) * RAD;
    double lon1 = lon_to_dec(loc1->lon) * RAD;
    double lon2 = lon_to_dec(loc2->lon) * RAD;

    double cos_d = sin(lat1)*sin(lat2) + (cos(lat1)*cos(lat2))*cos(lon1 - lon2);

    double d = acos(cos_d) * DEG;

    return (6371. * M_PI * d) / 180.;
}
/**
* @fn
* Calculates the linear distance between two points
* on the Earth's surface with better accuracy
* @param loc1 First Location
* @param loc2 Second Location
*/
double better_distance(struct Location *loc1, struct Location *loc2) {
    double lat1 = lat_to_dec(loc1->lat);
    double lat2 = lat_to_dec(loc2->lat);
    double lon1 = lon_to_dec(loc1->lon);
    double lon2 = lon_to_dec(loc2->lon);

    double F = (lat1 + lat2) / 2.;
    double G = (lat1 - lat2) / 2.;
    double lambda = (lon1 - lon2) / 2.;
    G *= RAD;
    F *= RAD;
    lambda *= RAD;
    double S = sin(G)*sin(G)*(cos(lambda)*cos(lambda)) + \
        + cos(F)*cos(F)*(sin(lambda)*sin(lambda));
    double C = cos(G)*cos(G)*(cos(lambda)*cos(lambda)) + \
        + sin(F)*sin(F)*(sin(lambda)*sin(lambda));

    double tan_w = sqrt(S/C);
    // Here, w (atan) is in radians (see Ch. 10, pag. 81)
    double w = atan(tan_w);
    double R = sqrt(S*C) / w; 
    double D = 2 * w * EQ_RADIUS;
    double H1 = (3*R - 1) / 2*C;
    double H2 = (3*R + 1) / 2*S;

    double dist = D*(1 + FLATTENING*H1*(sin(F)*sin(F))*(cos(G)*cos(G)) - \
        - FLATTENING*H2*(cos(F)*cos(F))*(sin(G)*sin(G)));

    return dist;
}
