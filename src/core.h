#ifndef _CORE_H_
#define _CORE_H_

// fetches list of all countries from OpenAQ and prints it to stdout
void print_all_countries(void);
// fetches list of all cities in country from OpenAQ and prints it to stdout
void print_cities_by_country(const char *country);
// fetches list of locations in city and available parameters, prints it to stdout
void print_locations_by_city(const char *city);

// fetches latest measurements for country and prints them to stdout
void print_latest_by_country(const char *country);
// fetches latest measurements for city and prints them to stdout
void print_latest_by_city(const char *city);
// fetches latest measurements for location and prints them to stdout
void print_latest_by_location(const char *location);

// finds location within city with highest amount of parameter specified, prints to stdout
void print_highest_by_city(const char *city, const char *parameter);
// finds location within country with highest amount of parameter specified, prints to stdout
void print_highest_by_country(const char *country_code, const char *parameter);

#endif