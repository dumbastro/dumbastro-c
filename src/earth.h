/** @file earth.h
    @brief Functions related to Earth's properties

    From "Astronomical Algorithms", Chapter 10 _The Earth's Globe_
*/
#include <stdlib.h>
#include <math.h>

/**
* @struct
* A representation of the Earth
* with some geometrical properties
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
    short degrees;
    short arcmins;
    double arcsecs;
};
/**
* @struct
* Representation of a location
* on the Earth's surface
*/
struct Location {
    struct Latitude lat; /*!< The location's geographical latitude */
    double h; /*!< Observer's height above sea level in m */
    double r_sin_phi_p; /*!< Earth's radius times sin(geocentric latitude) */
    double r_cos_phi_p; /*!< Earth's radius times cos(geocentric latitude) */
};

struct Earth set_earth_values(struct Earth * earth);
double lat_to_dec(struct Latitude lat);
struct Latitude dec_to_lat(double dec_lat);
struct Location set_location_params(struct Location * loc);
/**
* @fn
* Initializes an Earth structure
* @param *earth The Earth struct pointer
*/
struct Earth set_earth_values(struct Earth * earth) {
	earth->a = 6378.14; 
	earth->f = 1 / 298.257; 
    double f = earth->f;
    earth->b = earth->a * (1 - earth->f); 
	earth->e = sqrt(2*f - f*f);

    return *earth;
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

