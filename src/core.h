#ifndef _CORE_H_
#define _CORE_H_

// fetches list of all countries from OpenAQ and prints it to stdout
void list_countries(void);
// fetches list of all cities in country from OpenAQ and prints it to stdout
void list_cities_by_country(char *country);
// fetches latest measurements for city and prints them to stdout
void fetch_latest_by_city(char *city);

#endif