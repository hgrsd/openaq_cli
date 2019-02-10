#ifndef _JSON_H_
#define _JSON_H_

#include "data.h"

// Extracts cities from the raw string passed in and prints them to stdout.
void json_extract_cities(const char *raw_data);
// Extracts countries from the raw string passed in and prints them to stdout.
void json_extract_countries(const char *raw_data);
// Extracts locations from the raw string passed in and prints them to stdout.
void json_extract_locations(const char *raw_data);
// Extracts measurements from the raw string and stores them as an array of measurement_t structs. 
void json_extract_measurements(const char *raw_data, measurements_t *target);

#endif