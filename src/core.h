#ifndef _CORE_H_
#define _CORE_H_

typedef enum print_mode
{
    TO_SCREEN,
    TO_CSV
} print_mode_t;

// fetches list of all countries from OpenAQ and prints it to stdout
void all_countries(print_mode_t mode, const char *filename);
// fetches list of all cities in country from OpenAQ and prints it to stdout
void cities_by_country(const char *country, print_mode_t mode, const char *filename);
// fetches list of locations in city and available parameters, prints it to stdout
void locations_by_city(const char *city, print_mode_t mode, const char *filename);

// fetches latest measurements for country and prints them to stdout
void latest_by_country(const char *country, print_mode_t mode, const char *filename);
// fetches latest measurements for city and prints them to stdout
void latest_by_city(const char *city, print_mode_t mode, const char *filename);
// fetches latest measurements for location and prints them to stdout
void latest_by_location(const char *location, print_mode_t mode, const char *filename);

// finds location within city with highest amount of parameter specified, prints to stdout
void highest_by_city(const char *city, const char *parameter, print_mode_t mode, const char *filename);
// finds location within country with highest amount of parameter specified, prints to stdout
void highest_by_country(const char *country_code, const char *parameter, print_mode_t mode, const char *filename);

#endif