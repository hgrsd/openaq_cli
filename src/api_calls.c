#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "api_calls.h"
#include "data.h"

int write_callback(void *input, size_t size, size_t nmemb, void *target)
{
    struct response_data *received = (struct response_data *)target;
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

void fetch_countries(void *response)
{
    CURL *curl_handle;
    CURLcode curl_response;
    char request[MAX_REQUEST_SIZE];

    api_init();
    curl_handle = curl_easy_init();
    sprintf(request, URL_COUNTRIES, "?limit=200");
    if (curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, request);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);
    }
    curl_response = curl_easy_perform(curl_handle);
    if (curl_response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                curl_easy_strerror(curl_response));
    curl_easy_cleanup(curl_handle);
}

void fetch_cities(char *country, void *response)
{
    CURL *curl_handle;
    CURLcode curl_response;
    char request[MAX_REQUEST_SIZE];

    api_init();
    curl_handle = curl_easy_init();
    sprintf(request, URL_CITIES, country);
    if (curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, request);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);
    }
    curl_response = curl_easy_perform(curl_handle);
    if (curl_response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                curl_easy_strerror(curl_response));
    curl_easy_cleanup(curl_handle);
}

void fetch_locations_by_city(char *city, void *response)
{
    CURL *curl_handle;
    CURLcode curl_response;
    char request[MAX_REQUEST_SIZE];

    api_init();
    curl_handle = curl_easy_init();
    sprintf(request, URL_LOCATIONS, city);
    if (curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, request);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);
    }
    curl_response = curl_easy_perform(curl_handle);
    if (curl_response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                curl_easy_strerror(curl_response));
    curl_easy_cleanup(curl_handle);
}