#ifndef DUMBASTRO_H
#define DUMBASTRO_H

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

/**
* Conversions
*/
const static double RAD = M_PI / 180.;
const static double DEG = 180. / M_PI;
/**
* Earth constants
*/
const static double EQ_RADIUS = 6378.14;
const static double FLATTENING = 1.0 / 298.257;
const static double POL_RADIUS = 6356.755;
const static double RAD_RATIO = 1 - FLATTENING;
const static double MERID_ECC = 0.08181922;
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
* Representation of geographical
* longitude
*/
struct Longitude {
    short degrees;  /*!< Longitude degrees as an integer */
    short arcmins;  /*!< Longitude arc minutes as an integer */
    double arcsecs; /*!< Longitude arc seconds as decimal */
};
/**
* @struct
* Representation of a location
* on the Earth's surface
*/
struct Location {
    struct Latitude lat; /*!< The location's geographical latitude */
    struct Longitude lon; /*!< The location's geographical longitude */
    double h; /*!< Observer's height above sea level in m */
    double r_sin_phi_p; /*!< Earth's radius times sin(geocentric_latitude) */
    double r_cos_phi_p; /*!< Earth's radius times cos(geocentric_latitude) */
};

// Julian Day functions
double jd(struct Date date);
struct Date date_from_jd(double jd);
struct Date set_month_str(struct Date *date);
int date_diff (struct Date first, struct Date second);
short get_week_day(struct Date date);
bool is_leap_year(short year);
short unsigned get_year_day(struct Date date);
// Earth functions
void set_earth_values(struct Earth * earth);
double lat_to_dec(struct Latitude lat);
double rho_sin_phi(double h, double decimal_lat);
double rho_cos_phi(double h, double decimal_lat);
struct Latitude dec_to_lat(double dec_lat);
struct Location set_location_params(struct Location * loc);
double distance(struct Location *loc1, struct Location *loc2);
double better_distance(struct Location *loc1, struct Location *loc2);
// Time functions
double g_mean_ha(struct Date date, bool in_hours);
double g_app_ha(struct Date date);

#endif /* DUMBASTRO_H */
