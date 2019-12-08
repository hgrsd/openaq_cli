#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "api_calls.h"
#include "data.h"
#include "date_util.h"

static int write_callback(void *input, size_t size, size_t nmemb, void *target)
{
    response_data_t *received = (response_data_t *)target;
    char *ptr = realloc(received->data, received->size + nmemb + 1);
	
	received->data = ptr;
	memcpy(&(received->data[received->size]), input, nmemb);
	received->size += nmemb;
	received->data[received->size] = '\0';

	return nmemb;
}

static void api_init(void)
{
	static int initialised = 0;

	if (!initialised)
		curl_global_init(CURL_GLOBAL_ALL);

	initialised = 1;
}

static void fetch_data(const char *request, void *response)
{
    CURL *curl_handle;
    CURLcode curl_response;
    
    api_init();
    curl_handle = curl_easy_init();
    if (curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, request);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla Firefox");
    }
    
    curl_response = curl_easy_perform(curl_handle);
    if (curl_response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_response));

    curl_easy_cleanup(curl_handle);
}

void api_fetch_countries(void *response)
{
    fetch_data(URL_COUNTRIES, response);
}

void api_fetch_cities(const char *country, void *response)
{
    char request[MAX_REQUEST_SIZE];
    snprintf(request, MAX_REQUEST_SIZE - 1, URL_CITIES, country);
    fetch_data(request, response);
}

void api_fetch_locations_by_city(const char *city, void *response)
{
    char request[MAX_REQUEST_SIZE];
    char *city_urlencoded;

    CURL *curl_handle; 
    curl_handle = curl_easy_init();
    
    city_urlencoded = curl_easy_escape(curl_handle, city, 0);
    snprintf(request, MAX_REQUEST_SIZE - 1, URL_LOCATIONS, city_urlencoded);
    fetch_data(request, response);

    curl_free(city_urlencoded);
    curl_easy_cleanup(curl_handle);
}

void api_fetch_range(request_type_t type, const char *argument, const char *date_from, const char *date_to, void *response)
{
    char request[MAX_REQUEST_SIZE];
    char *argument_urlencoded;

    CURL *curl_handle;
    curl_handle = curl_easy_init();

    argument_urlencoded = curl_easy_escape(curl_handle, argument, 0);
    
    if (type == REQUEST_COUNTRY)
    {
        if (date_from && date_to)
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_RANGE, "country", argument_urlencoded, date_from, date_to);
        else if (date_from)
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_FROM, "country", argument_urlencoded, date_from);
        else
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_TO, "country", argument_urlencoded, date_to);
    }
    else if (type == REQUEST_CITY)
    {
        if (date_from && date_to)
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_RANGE, "city", argument_urlencoded, date_from, date_to);
        else if (date_from)
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_FROM, "city", argument_urlencoded, date_from);
        else
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_TO, "city", argument_urlencoded, date_to);
    }
    else if (type == REQUEST_LOCATION)
    {
        if (date_from && date_to)
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_RANGE, "location", argument_urlencoded, date_from, date_to);
        else if (date_from)
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_FROM, "location", argument_urlencoded, date_from);
        else
            snprintf(request, MAX_REQUEST_SIZE - 1, URL_MEASUREMENTS_TO, "location", argument_urlencoded, date_to);
    }
    else
    {
        return;
    }
    fetch_data(request, response);

    curl_easy_cleanup(curl_handle);
}

void api_fetch_latest(request_type_t type, const char *argument, void *response)
{
    char request[MAX_REQUEST_SIZE];
    char *argument_urlencoded;

    CURL *curl_handle;
    curl_handle = curl_easy_init();

    argument_urlencoded = curl_easy_escape(curl_handle, argument, 0);
    
    if (type == REQUEST_COUNTRY)
    {
        snprintf(request, MAX_REQUEST_SIZE - 1, URL_LATEST, "country", argument_urlencoded);
    }
    else if (type == REQUEST_CITY)
    {
        snprintf(request, MAX_REQUEST_SIZE - 1, URL_LATEST, "city", argument_urlencoded);
    }
    else if (type == REQUEST_LOCATION)
    {
        snprintf(request, MAX_REQUEST_SIZE - 1, URL_LATEST, "location", argument_urlencoded);
    }
    else
    {
        return;
    }
    fetch_data(request, response);

    curl_easy_cleanup(curl_handle);
}
