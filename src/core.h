#ifndef _CORE_H_
#define _CORE_H_

#include "args.h"

// fetches list of all countries from OpenAQ and prints it to stdout or CSV
void all_countries(print_mode_t mode, const char *filename);
// fetches list of all cities in country from OpenAQ and prints it to stdout or CSV
void cities_by_country(const char *country, print_mode_t mode, const char *filename);
// fetches list of locations in city and available parameters, prints it to stdout or CSV
void locations_by_city(const char *city, print_mode_t mode, const char *filename);

// fetches latest measurements for country/city/location and prints to stdout or CSV
void latest(request_type_t type, const char *argument, print_mode_t mode, const char *filename);

// fetches range of measurements for country/city/location and prints to stdout or CSV
void date_range(request_type_t type, const char *argument, const char *date_from, const char *date_to, print_mode_t mode, const char *filename);


// finds location within country/city with highest amount of parameter specified, prints to stdout or CSV
void highest(request_type_t type, const char *argument, const char *parameter, print_mode_t mode, const char *filename);
// finds location withi country/city with highest amount of parameter specified, within date range, prints to stdout or CSV
void highest_range(request_type_t type, const char *argument, const char *parameter, const char* date_from, const char* date_to, print_mode_t mode, const char *filename);

#endif