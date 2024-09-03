/** @file earth.h
    @brief Functions related to Earth's properties

    From "Astronomical Algorithms", Chapter 10 _The Earth's Globe_
*/
#include <stdlib.h>
#include <math.h>

const double PI = 3.14159265365358979323;
/**
* Earth constants...
*/
const double EQ_RADIUS = 6378.14;
const double FLATTENING = 1.0 / 298.257;
const double POL_RADIUS = 6356.755;
const double RAD_RATIO = 1 - FLATTENING;
const double MERID_ECC = 0.08181922;
/**
* @struct
* A representation of the Earth
* with some geometrical properties
* @todo Useless?
*/
struct Earth {
	double a; /*!< The Earth's equatorial radius in km */
	double f; /*!< The Earth's flattening */
    double b; /*!< The Earth's polar radius in km */
	double e; /*!< The eccentricity of Earth's meridian */
};
/**
* @struct
* Representation of geographical
* latitude
*/
struct Latitude {
    short degrees;  /*!< Latitude degrees as an integer */
    short arcmins;  /*!< Latitude arc minutes as an integer */
    double arcsecs; /*!< Latitude arc seconds as decimal */
};
/**
* @struct
* Representation of a location
* on the Earth's surface
*/
struct Location {
    struct Latitude lat; /*!< The location's geographical latitude */
    double h; /*!< Observer's height above sea level in m */
    double r_sin_phi_p; /*!< Earth's radius times sin(geocentric_latitude) */
    double r_cos_phi_p; /*!< Earth's radius times cos(geocentric_latitude) */
};

void set_earth_values(struct Earth * earth);
double lat_to_dec(struct Latitude lat);
double r_sin_phi(double h, double decimal_lat);
struct Latitude dec_to_lat(double dec_lat);
struct Location set_location_params(struct Location * loc);

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

    return lat.degrees + dec_minutes + dec_seconds;
}
/**
* @fn
* Calculates $\rho \sin{\phi}$ for
* a location
* @param h The location's height in meters
* @param decimal_lat The location's decimal latitude in deg
*/
double rho_sin_phi(double h, double decimal_lat) {
    // Convert lat from deg to radians
    double lat_rad = decimal_lat * (PI / 180.);
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
* @param decimal_lat The location's decimal latitude
*/
double rho_cos_phi(double h, double decimal_lat) {
    // Convert lat from deg to radians
    double lat_rad = decimal_lat * (PI / 180.);
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

