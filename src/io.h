#ifndef _IO_H_
#define _IO_H_

#include "data.h"

// Prints a list of countries and their info
void print_countries(countries_t *source);
// Prints a list of cities and their info
void print_cities(cities_t *source);
// Prints a list of locations and their info
void print_locations(locations_t *source);
// Prints a single measurement 
void print_measurement(measurement_t *measurement);
// Prints all measurements contained in the structure passed in.
void print_measurements(measurements_t *source);

// Writes a list of countries and their info to a CSV file, returns lines written
int write_countries(countries_t *source, const char *filename);
// Writes a list of cities and their info to a CSV file, returns lines written
int write_cities(cities_t *source, const char* filename);
// Writes a list of locations and their info to a CSV file, returns lines written
int write_locations(locations_t *source, const char *filename);
// Writes a single measurement to a CSV file
void write_measurement(measurement_t *measurement, FILE *fp);
// Writes all measurements contained in the structure passed in to a CSV file, returns linesn written
int write_measurements(measurements_t *source, const char *filename);

#endif