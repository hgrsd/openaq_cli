#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "api_calls.h"
#include "data.h"
#include "json.h"
#include "core.h"
#include "string_util.h"

measurement_t *find_highest(measurements_t *measurements_data, parameter_t parameter)
{
    void *base;
    float max = -1;
    float val;
    measurement_t *highest = NULL;
    size_t offset;
    
    switch(parameter)
    {
        case PARAM_BC:
            offset = offsetof(measurement_t, bc);
            break;

        case PARAM_CO:
            offset = offsetof(measurement_t, co);
            break;

        case PARAM_NO2:
            offset = offsetof(measurement_t, no2);
            break;

        case PARAM_O3:
            offset = offsetof(measurement_t, o3);
            break;

        case PARAM_PM10:
            offset = offsetof(measurement_t, pm10);
            break;

        case PARAM_PM25:
            offset = offsetof(measurement_t, pm25);
            break;

        case PARAM_SO2:
            offset = offsetof(measurement_t, so2);
            break;
        
        case PARAM_INVALID:
            printf("Invalid parameter. Valid parameters: BC, CO, NO2, O3, PM10, PM25, SO2.\n");
            return NULL;
    }

    for (int i = 0; i < measurements_data->size; i++)
    {
        base = &(measurements_data->measurements_array[i]);
        val = *(float *)(base + offset);
        if (val > max)
        {
            max = val;
            highest = &(measurements_data->measurements_array[i]);
        }    
    }

    return highest;
}

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

void find_highest_by_city(const char *city, const char *parameter)
{
    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    measurement_t *highest;

    init_data(&raw_data);
    api_fetch_latest_by_city(city, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);

    highest = find_highest(&measurements_data, string_to_param(parameter));
    if (highest != NULL)
    {
        printf("Highest amount of %s found in the following location: \n", parameter);
        print_measurement(highest);
    }
}