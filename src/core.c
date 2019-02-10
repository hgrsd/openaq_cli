#include "api_calls.h"
#include "data.h"
#include "json.h"
#include "core.h"

void list_countries(void)
{   
    response_data_t raw_data;

    init_data(&raw_data);
    api_fetch_countries(&raw_data);
    json_print_countries(raw_data.data);
    
    clear_data(&raw_data);
}

void list_cities_by_country(const char *country)
{
    response_data_t raw_data;

    init_data(&raw_data);
    api_fetch_cities(country, &raw_data);
    json_print_cities(raw_data.data);

    clear_data(&raw_data);
}

void list_locations_by_city(const char *city)
{
    response_data_t raw_data;

    init_data(&raw_data);
    api_fetch_locations_by_city(city, &raw_data);
    json_print_locations(raw_data.data);

    clear_data(&raw_data);   
}

void fetch_latest_by_city(const char *city)
{
    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_city(city, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);
    print_measurements(&measurements_data);

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}

void fetch_latest_by_location(const char *location)
{
    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_location(location, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);
    print_measurements(&measurements_data);

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}