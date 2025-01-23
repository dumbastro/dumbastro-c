/** @file earth.h
    @brief Functions related to Earth's properties

    From "Astronomical Algorithms", Chapter 10 _The Earth's Globe_
*/
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

void set_earth_values(struct Earth * earth);
double lat_to_dec(struct Latitude lat);
double rho_sin_phi(double h, double decimal_lat);
double rho_cos_phi(double h, double decimal_lat);
struct Latitude dec_to_lat(double dec_lat);
struct Location set_location_params(struct Location * loc);
double distance(struct Location *loc1, struct Location *loc2);
double better_distance(struct Location *loc1, struct Location *loc2);

