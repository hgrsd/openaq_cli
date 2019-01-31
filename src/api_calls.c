#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "api_calls.h"
#include "data.h"

int write_callback(void *input, size_t size, size_t nmemb, void *target)
{
    response_data_t *received = (response_data_t *)target;
    char *ptr = realloc(received->data, received->size + nmemb + 1);
	
	received->data = ptr;
	memcpy(&(received->data[received->size]), input, nmemb);
	received->size += nmemb;
	received->data[received->size] = '\0';

	return nmemb;
}

void api_init(void)
{
	static int initialised = 0;

	if (!initialised)
		curl_global_init(CURL_GLOBAL_ALL);

	initialised = 1;
}

void fetch_data(char *request, void *response)
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
        fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                curl_easy_strerror(curl_response));
    curl_easy_cleanup(curl_handle);
}

void fetch_countries(void *response)
{
    char request[MAX_REQUEST_SIZE];
    sprintf(request, URL_COUNTRIES, "?limit=200");
    fetch_data(request, response);
}

void fetch_cities(char *country, void *response)
{
    char request[MAX_REQUEST_SIZE];
    sprintf(request, URL_CITIES, country);
    fetch_data(request, response);
}

void fetch_locations_by_city(char *city, void *response)
{
    char request[MAX_REQUEST_SIZE];
    sprintf(request, URL_LOCATIONS, city);
    fetch_data(request, response);
}

void fetch_latest_by_city(char *city, void *response)
{
    char request[MAX_REQUEST_SIZE];
    sprintf(request, URL_LATEST, city);
    fetch_data(request, response);
}