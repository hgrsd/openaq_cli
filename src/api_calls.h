#ifndef _API_CALLS_H_
#define _API_CALLS_H_

#define URL_CITIES "https://api.openaq.org/v1/cities?limit=10000&country=%s"
#define URL_COUNTRIES "https://api.openaq.org/v1/countries"
#define URL_LOCATIONS "https://api.openaq.org/v1/locations?limit=10000&city=%s"
#define URL_LATEST_BY_CITY "https://api.openaq.org/v1/latest?&limit=10000&city=%s"
#define URL_LATEST_BY_COUNTRY "https://api.openaq.org/v1/latest?limit=10000&country=%s"
#define URL_LATEST_BY_LOCATION "https://api.openaq.org/v1/latest?location=%s"

#define MAX_REQUEST_SIZE 256

#include "data.h"

// Fetches all countries and country codes, stores raw response string in response
void api_fetch_countries(void *response);
// Fetches all cities in the specified country, stores raw response string in response
void api_fetch_cities(const char *country, void *response);
// Fetches all locations in the specified city, stores raw response string in response
void api_fetch_locations_by_city(const char *city, void *response);
// Fetches the latest measurements for each location in the specified city, stores raw response string in response.
void api_fetch_latest_by_city(const char *city, void *response);
// Fetches the latest measurements for each location in the country specified, stores raw response string in response.
void api_fetch_latest_by_country(const char *country_code, void *response);
// Fetches the latest measurements for the location specified, stores raw response string in response.
void api_fetch_latest_by_location(const char *location, void *response);

#endif 