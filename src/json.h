#ifndef _JSON_H_
#define _JSON_H_

#include "data.h"

// Extracts measurements from the raw string and stores them as an array of measurement_t structs. 
void json_extract_measurements(const char *raw_data, measurements_t *target);
// Extracts countries from the raw string and stores them as an array of country_t structs. 
void json_extract_countries(const char *raw_data, countries_t *target);
// Extracts cities from the raw  string and stores them as an array of city_t structs.
void json_extract_cities(const char *raw_data, cities_t *target);
// Extracts locations from the raw  string and stores them as an array of location_t structs.
void json_extract_locations(const char *raw_data, locations_t *target);


#endif