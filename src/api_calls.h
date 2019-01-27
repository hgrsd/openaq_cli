#ifndef _API_CALLS_H_
#define _API_CALLS_H_

#define URL_CITIES "https://api.openaq.org/v1/cities?limit=1000&country=%s"
#define URL_COUNTRIES "https://api.openaq.org/v1/countries%s"
#define URL_LOCATIONS "https://api.openaq.org/v1/locations?limit=100&city=%s"
#define URL_LATEST "https://api.openaq.org/v1/latest?city=%s"

#define MAX_REQUEST_SIZE 80

void fetch_countries(void *response);
void fetch_cities(char *country, void *response);
void fetch_locations_by_city(char *city, void *response);
void fetch_latest_by_city(char *city, void *response);
void fetch_latest_by_location(char *location, void *response);

#endif 