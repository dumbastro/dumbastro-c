#include <stdio.h>
#include <stdlib.h>
#include "./src/dumbastro.h"

int main(void) {
    // Test earth.c functions
    struct Latitude lat_palomar = {
        .degrees = 33,
        .arcmins = 21,
        .arcsecs = 22
    };
    struct Latitude lat_paris = {
        .degrees = 48,
        .arcmins = 50,
        .arcsecs = 11
    };
    struct Longitude lon_paris = {
        .degrees = -2,
        .arcmins = 20,
        .arcsecs = 14
    };
    struct Latitude lat_washing = {
        .degrees = 38,
        .arcmins = 55,
        .arcsecs = 17
    };
    struct Longitude lon_washing = {
        .degrees = 77,
        .arcmins = 3,
        .arcsecs = 56
    };

    printf("\n##### Testing decimal latitude #####\n\n");
    printf("Decimal latitude: %.6f\n", lat_to_dec(lat_palomar));

    struct Earth earth = { 0 };
    struct Location palomar = { .lat = lat_palomar, .h = 1706 };
    set_earth_values(&earth);
    palomar = set_location_params(&palomar);

    printf("\n##### Testing Earth values ####\n\n");
    printf(" \
    Equatorial radius: %.4f\n \
    Polar radius:      %.4f\n \
    Flattening:        %.8f\n \
    Eccentricity:      %.8f\n \
    Rad ratio (b/a):   %.8f\n",
            earth.a,
            earth.b,
            earth.f,
            earth.e,
            earth.b / earth.a
    );

    printf("\n##### Testing Location values ####\n\n");
    printf("rho_sin_phi: %.6f, rho_cos_phi: %.6f\n", palomar.r_sin_phi_p, palomar.r_cos_phi_p);

    printf("\n##### Testing distance ####\n\n");

    struct Location paris = {
        .lat = lat_paris,
        .lon = lon_paris,
        .h = 0
    };
    struct Location washing = {
        .lat = lat_washing,
        .lon = lon_washing,
        .h = 0
    };
    
    printf("Approx. distance: %.2f\n", distance(&paris, &washing));
    printf("Better distance: %.2f\n", better_distance(&paris, &washing));

// Test julianday.c functions
    struct Date dates[] = {
	    {
		.year = -1000, 
		.month = 7, 
		.day = 12.5
	    },
	    {
		.year = 333, 
		.month = 1, 
		.day = 27.5
	    },
	    {
		.year = 2000, 
		.month = 1, 
		.day = 1.5
	    },
	    {
		.year = 1582, 
		.month = 10, 
		.day = 3.901
	    },
	    {
		.year = 1582, 
		.month = 10, 
		.day = 15.901
	    },
	    {
		.year = 1987, 
		.month = 1, 
		.day = 27.0
	    },
	    {
		.year = 1987, 
		.month = 6, 
		.day = 19.50
	    },
	    {
		.year = 2024, 
		.month = 7, 
		.day = 16.81
	    },
	    {
		.year = 1988, 
		.month = 1, 
		.day = 27.00
	    },
	    {
		.year = -4712, 
		.month = 1, 
		.day = 1.5
	    }
    };

    double expected[] = {
	    1356001.00,
	    1842713.00,
	    2451545.00,
	    2299159.41,
	    2299161.42,
	    2446822.5,
	    2446966.0,
	    2460508.31,
	    2447187.50,
	    0.00,
    };

   printf("####### TEST Julian Day from date #######\n\n");

   for (int i = 0; i < (int)sizeof(expected)/sizeof(double); i++) {
	   printf("Expected: %.2f\t Calculated: %.2f\n",
		   expected[i],
		   jd(dates[i])
	  ); 
   }

   struct Date test_date = date_from_jd(2436116.31);
   set_month_str(&test_date);

   printf("\n####### TEST Date from Julian Day #######\n\n");

   printf(
        "Date from JD: %d %s %.2f\n",
        test_date.year,
        test_date.monthstr,
        test_date.day);

   for (int i = 0; i < (int)sizeof(expected)/sizeof(double); i++) {
       struct Date temp = date_from_jd(jd(dates[i]));
       set_month_str(&temp);
	   printf(
            "Date from JD: %d %s %.2f\n",
            temp.year,
            temp.monthstr,
            temp.day
	  ); 
   }

   printf("\n####### TEST Date date diff #######\n\n");

   struct Date first = {
        .year = 1991,
        .month = 7,
        .day = 11,
    };
   struct Date second = {
        .year = 2018,
        .month = 11,
        .day = 26,
    };
   
   printf("Date diff: %d\n", date_diff(first, second));

   printf("\n####### TEST Week day #######\n\n");

   struct Date day_test = {
        .year = 1954,
        .month = 6,
        .day = 30.5,
    };
   struct Date day_test2 = {
        .year = 2024,
        .month = 7,
        .day = 19,
   };
   struct Date day_test3 = {
        .year = 2024,
        .month = 7,
        .day = 22,
   };

   printf("Week day (should be 3): %d\n", get_week_day(day_test));
   printf("Week day (should be 5): %d\n", get_week_day(day_test2));
   printf("Week day (should be 1): %d\n", get_week_day(day_test3));

   printf("\n####### TEST day of the year #######\n\n");

   struct Date day_test4 = {
        .year = 1988,
        .month = 4,
        .day = 22,
   };
   struct Date day_test5 = {
        .year = 1978,
        .month = 11,
        .day = 14,
   };
   struct Date day_test6 = {
        .year = 2016,
        .month = 6,
        .day = 1,
   };

   printf("Day of the year? (Should be 113): %d\n", get_year_day(day_test4));
   printf("Day of the year? (Should be 318): %d\n", get_year_day(day_test5));
   printf("Day of the year? (Should be 153): %d\n", get_year_day(day_test6));

    // Test mean sideral time at Greenwich
    struct Date gw_date = {
        .year = 1987,
        .month = 4,
        .day = 10.80625,
    };

    printf("\n\n");
    printf("Mean sidereal Greenwich (degrees): %.8f\n", g_mean_ha(gw_date, false));
    printf("Mean sidereal Greenwich (hours): %.8f\n", g_mean_ha(gw_date, true));

    printf("\n\n");
    double ecl_lon = ecl_lon_from_eq(116.328942, 28.026183, J2000);
    double ecl_lat = ecl_lat_from_eq(116.328942, 28.026183, J2000);
    printf("Ecliptical lon. (Pollux): %.6f\n", ecl_lon);
    printf("Ecliptical lat. (Pollux): %.6f\n", ecl_lat);
    printf("R.A. from ecliptical (Pollux): %.6f\n", alpha_from_ecl(ecl_lat, ecl_lon, J2000));
    printf("DEC from ecliptical (Pollux): %.6f\n", delta_from_ecl(ecl_lat, ecl_lon, J2000));
    
    return EXIT_SUCCESS;
}
