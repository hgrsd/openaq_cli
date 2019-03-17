#ifndef _API_CALLS_H_
#define _API_CALLS_H_

#define URL_CITIES "https://api.openaq.org/v1/cities?limit=10000&country=%s"
#define URL_COUNTRIES "https://api.openaq.org/v1/countries"
#define URL_LOCATIONS "https://api.openaq.org/v1/locations?limit=10000&city=%s"
#define URL_LATEST "https://api.openaq.org/v1/latest?limit=10000&%s=%s"
#define URL_MEASUREMENTS_FROM "https://api.openaq.org/v1/measurements?limit=10000&%s=%s&date_from=%s"
#define URL_MEASUREMENTS_TO "https://api.openaq.org/v1/measurements?limit=10000&%s=%s&date_to=%s"
#define URL_MEASUREMENTS_RANGE "https://api.openaq.org/v1/measurements?limit=10000&%s=%s&date_from=%s&date_to=%s"

#define MAX_REQUEST_SIZE 256

#include "args.h"

// Fetches all countries and country codes, stores response for further processing.
void api_fetch_countries(void *response);
// Fetches all cities in the specified country, stores response for further processing.
void api_fetch_cities(const char *country, void *response);
// Fetches all locations in the specified city, sttores response for further processing.
void api_fetch_locations_by_city(const char *city, void *response);

// Fetches the latest measurements for country/city/location, stores response for further processing.
void api_fetch_latest(request_type_t type, const char *argument, void *response);

// Fetches measurements for a date range for country/city/location, stores response for further processing.
void api_fetch_range(request_type_t type, const char *argument, const char *date_from, const char *date_to, void *response);



#endif 