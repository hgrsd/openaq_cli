#include <stdio.h>
#include <string.h>

#include "data.h"

size_t offsets[] = {
    offsetof(measurement_t, substances[PARAM_PM25].value),
    offsetof(measurement_t, substances[PARAM_PM10].value),
    offsetof(measurement_t, substances[PARAM_O3].value),
    offsetof(measurement_t, substances[PARAM_SO2].value),
    offsetof(measurement_t, substances[PARAM_NO2].value),
    offsetof(measurement_t, substances[PARAM_CO].value),
    offsetof(measurement_t, substances[PARAM_BC].value),
    0
};

const char* parameter_names[N_PARAMETERS] = {
    "pm25",
    "pm10",
    "no2",
    "co",
    "bc",
    "o3",
    "so2"
};

parameter_t string_to_param(const char* string)
{
    if (!strcmp(string, "pm25"))
        return PARAM_PM25;
    else if (!strcmp(string, "pm10"))
        return PARAM_PM10;
    else if (!strcmp(string, "no2"))
        return PARAM_NO2;
    else if (!strcmp(string, "co"))
        return PARAM_CO; 
    else if (!strcmp(string, "bc"))
        return PARAM_BC;
    else if (!strcmp(string, "o3"))
        return PARAM_O3; 
    else if (!strcmp(string, "so2"))
        return PARAM_SO2;
    else
        return PARAM_INVALID;    
}

void clear_data(response_data_t *data)
{
    free(data->data);
    data->data = malloc(1);
    data->size = 0;
}

void init_data(response_data_t *data)
{
    data->data = malloc(1);
    data->size = 0;
}

void init_measurements(measurements_t *target, int nmemb)
{   
    if (target->measurements_array != NULL)
    {
        target->size = 0;
        free(target->measurements_array);
        target->measurements_array = NULL;
    }
    target->measurements_array = (measurement_t *) malloc(sizeof(measurement_t) * nmemb);
    if (target->measurements_array != NULL)
    {
        target->size = nmemb;
        for (int i = 0; i < nmemb; i++)
        {
            strcpy(target->measurements_array[i].location, "\0");
            strcpy(target->measurements_array[i].city, "\0");
            strcpy(target->measurements_array[i].country_code, "\0");
            target->measurements_array[i].latitude = 0;
            target->measurements_array[i].longitude = 0;
            target->measurements_array[i].valid_data = 0;
            for (int j = 0; j < N_PARAMETERS; j++)
            {
                target->measurements_array[i].substances[j].timestamp = -1;
                target->measurements_array[i].substances[j].value = -1;
                strcpy(target->measurements_array[i].substances[j].unit, "\0");
            }
        }
    }
}

void init_countries(countries_t *target, int nmemb)
{
    if (target->countries_array != NULL)
    {
        free(target->countries_array);
        target->size = 0;
        target->countries_array = NULL;
    }
    target->countries_array = (country_t *) malloc(sizeof(country_t) * nmemb);
    if (target->countries_array != NULL)
    {
        target->size = nmemb;
        for (int i = 0; i < nmemb; i++)
        {
            strcpy(target->countries_array[i].name, "\0");
            strcpy(target->countries_array[i].country_code, "\0");
            target->countries_array[i].n_cities = 0;
            target->countries_array[i].n_locations = 0;
        }
    }
}

void init_cities(cities_t *target, int nmemb)
{
    if (target->cities_array != NULL)
    {
        free(target->cities_array);
        target->size = 0;
        target->cities_array = NULL;
    }
    target->cities_array = (city_t *) malloc(sizeof(city_t) * nmemb);
    if (target->cities_array != NULL)
    {
        target->size = nmemb;
        for (int i = 0; i < nmemb; i++)
        {
            strcpy(target->cities_array[i].name, "\0");
            strcpy(target->cities_array[i].country_code, "\0");
            target->cities_array[i].n_locations = 0;
        }
    }
}

void init_locations(locations_t *target, int nmemb)
{
    if (target->locations_array != NULL)
    {
        free(target->locations_array);
        target->size = 0;
        target->locations_array = NULL;
    }
    target->locations_array = (location_t *) malloc(sizeof(location_t) * nmemb);
    if (target->locations_array != NULL)
    {
        target->size = nmemb;
        for (int i = 0; i < nmemb; i++)
        {
            strcpy(target->locations_array[i].name, "\0");
            strcpy(target->locations_array[i].country_code, "\0");
            for (int j = 0; j < N_PARAMETERS; j++)
                target->locations_array[i].parameters[i] = 0;
            target->locations_array[i].latitude = 0;
            target->locations_array[i].longitude = 0;
        }
    }
}

measurement_t *find_highest(measurements_t *measurements_data, parameter_t parameter)
{
    void *base;
    double max = -1;
    double val;
    size_t offset = offsets[parameter];
    measurement_t *highest = NULL;
        
    if (offset == 0 || measurements_data->size == 0)
    {
        return NULL;
    }

    for (int i = 0; i < measurements_data->size; i++)
    {
        base = measurements_data->measurements_array + i;
        val = *(double *)(base + offset);
        if (val > max)
        {
            max = val;
            highest = base;
        }    
    }

    return highest;
}

