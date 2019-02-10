#include "api_calls.h"
#include "data.h"
#include "json.h"
#include "core.h"

void list_countries(void)
{   
    response_data_t raw_data;

    init_data(&raw_data);
    api_fetch_countries(&raw_data);
    json_extract_countries(raw_data.data);
}

void list_cities_by_country(char *country)
{
    response_data_t raw_data;

    init_data(&raw_data);
    api_fetch_cities(country, &raw_data);
    json_extract_cities(raw_data.data);
}

void fetch_latest_by_city(char *city)
{
    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_city(city, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);
    print_measurements(&measurements_data);
    free(measurements_data.measurements_array);
}

