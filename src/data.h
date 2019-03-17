#ifndef _DATA_H_
#define _DATA_H_

#include <stdlib.h>
#include <stddef.h>

#define LOCATION_MAX 128
#define CITY_MAX 128
#define COUNTRY_MAX 64
#define COUNTRY_CODE_MAX 3
#define DATE_MAX 30
#define UNIT_MAX 12

// all possible parameters that may be returned
typedef enum parameter
{
    PARAM_PM25,
    PARAM_PM10,
    PARAM_O3,
    PARAM_SO2,
    PARAM_NO2,
    PARAM_CO,
    PARAM_BC,
    PARAM_INVALID
} parameter_t;

// offset of each parameter, defined in data.c
extern size_t offsets[];

// holds raw reponses from a GET request
typedef struct _response_data_t
{
    char *data;
    int size;
} response_data_t;

// holds JSON-decoded information about a city
typedef struct _city_t
{
    char name[CITY_MAX];
    char country_code[COUNTRY_CODE_MAX];
    int n_locations;
} city_t;

// holds a series of cities
typedef struct _cities_t
{
    city_t *cities_array;
    int size;
} cities_t;

// holds JSON-decoded information about a country
typedef struct _country_t
{
    char name[COUNTRY_MAX];
    char country_code[COUNTRY_CODE_MAX];
    int n_cities;
    int n_locations;
} country_t;

// for a series of countries
typedef struct _countries_t
{
    country_t *countries_array;
    int size;
} countries_t;

// holds JSON-decoded information about a location
typedef struct _location_t
{
    char name[LOCATION_MAX];
    char city[CITY_MAX];
    char country_code[COUNTRY_CODE_MAX];
    double latitude;
    double longitude;
    int has_pm25;
    int has_pm10;
    int has_o3;
    int has_so2;
    int has_no2;
    int has_co;
    int has_bc;
} location_t;

// holds a series of locations
typedef struct _locations_t
{
    location_t *locations_array;
    int size;
} locations_t;

// holds JSON-decoded measurements for a single location
typedef struct _measurement_t
{
    char country_code[COUNTRY_CODE_MAX];
    char city[CITY_MAX];
    char location[LOCATION_MAX];
    char date[DATE_MAX];
    char pm25_unit[UNIT_MAX];
    char pm10_unit[UNIT_MAX];
    char o3_unit[UNIT_MAX];
    char so2_unit[UNIT_MAX];
    char no2_unit[UNIT_MAX];
    char co_unit[UNIT_MAX];
    char bc_unit[UNIT_MAX];
    double latitude;
    double longitude;
    double pm25;
    double pm10;
    double o3;
    double so2;
    double no2;
    double co;
    double bc;
} measurement_t;

// holds a series of JSON-decoded measurements
typedef struct _measurements_t
{
    struct _measurement_t *measurements_array;
    int size;
} measurements_t;

// Clears a previously initialised and/or previously used response_data_t structure
void clear_data(response_data_t *data);

// Initialises a declared, unused response_data_t structure. Must be called before using the structure.
void init_data(response_data_t *data);
// Initialises an array of measurements. Must be called before using the structure.
void init_measurements(measurements_t *target, int nmemb);
// Initialises an array of cities. Must be called before using the structure.
void init_cities(cities_t *target, int nmemb);
// Initialises an array of locations. Must be called before using the structure.
void init_locations(locations_t *target, int nmemb);
// Initialises an array of countries. Must be called before using the structure.
void init_countries(countries_t *target, int nmemb);

// returns parameter_t enum based on string input
parameter_t string_to_param(const char *string);

// returns pointer to the measurement_t struct within a series of measurements
// with the highest value for the specified parameter
measurement_t *find_highest(measurements_t *measurements_data, parameter_t parameter);
#endif
