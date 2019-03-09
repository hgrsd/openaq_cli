#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"

size_t offsets[] = {
    offsetof(measurement_t, pm25),
    offsetof(measurement_t, pm10),
    offsetof(measurement_t, o3),
    offsetof(measurement_t, so2),
    offsetof(measurement_t, no2),
    offsetof(measurement_t, co),
    offsetof(measurement_t, bc),
    0
};

static inline void print_value(const char *measurement, float value, const char *unit)
{
    printf("%s: \t\t\t%.3f %s\n", measurement, value, unit);
}

parameter_t string_to_param(const char* string)
{
    if (!strcmp(string, "PM25"))
        return PARAM_PM25;
    else if (!strcmp(string, "PM10"))
        return PARAM_PM10;
    else if (!strcmp(string, "NO2"))
        return PARAM_NO2;
    else if (!strcmp(string, "CO"))
        return PARAM_CO; 
    else if (!strcmp(string, "BC"))
        return PARAM_BC;
    else if (!strcmp(string, "O3"))
        return PARAM_O3; 
    else if (!strcmp(string, "SO2"))
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
    target->size = nmemb;
    for (int i = 0; i < nmemb; i++)
    {
        strcpy(target->measurements_array[i].location, "\0");
        strcpy(target->measurements_array[i].date, "\0");
        target->measurements_array[i].latitude = 0;
        target->measurements_array[i].longitude = 0;
        target->measurements_array[i].bc = -1;
        strcpy(target->measurements_array[i].bc_unit, "\0");
        target->measurements_array[i].co = -1;
        strcpy(target->measurements_array[i].co_unit, "\0");
        target->measurements_array[i].no2 = -1;
        strcpy(target->measurements_array[i].no2_unit, "\0");
        target->measurements_array[i].o3 = -1;
        strcpy(target->measurements_array[i].o3_unit, "\0");
        target->measurements_array[i].pm10 = -1;
        strcpy(target->measurements_array[i].pm10_unit, "\0");
        target->measurements_array[i].pm25 = -1;
        strcpy(target->measurements_array[i].pm25_unit, "\0");
        target->measurements_array[i].so2 = -1;
        strcpy(target->measurements_array[i].so2_unit, "\0");
    }
}

void init_countries(countries_t *target, int nmemb)
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

void init_cities(cities_t *target, int nmemb)
{
    target->size = nmemb;
    for (int i = 0; i < nmemb; i++)
    {
        strcpy(target->cities_array[i].name, "\0");
        strcpy(target->cities_array[i].country_code, "\0");
        target->cities_array[i].n_locations = 0;
    }
}

void init_locations(locations_t *target, int nmemb)
{
    target->size = nmemb;
    for (int i = 0; i < nmemb; i++)
    {
        strcpy(target->locations_array[i].name, "\0");
        strcpy(target->locations_array[i].country_code, "\0");
        target->locations_array[i].has_pm25 = 0;
        target->locations_array[i].has_pm10 = 0;
        target->locations_array[i].has_bc = 0;
        target->locations_array[i].has_no2 = 0;
        target->locations_array[i].has_so2 = 0;
        target->locations_array[i].has_o3 = 0;
        target->locations_array[i].has_co = 0;
        target->locations_array[i].latitude = 0;
        target->locations_array[i].longitude = 0;
    }
}

void print_location(location_t *source)
{
    printf("    * Name:\t\t\t%s\n", source->name);
    printf("    * City:\t\t\t%s\n", source->city);
    printf("    * Country code:\t\t%s\n", source->country_code);
    printf("    * Latitude:\t\t\t%f\n", source->latitude);
    printf("    * Longitude:\t\t%f\n", source->longitude);
    printf("    * Available parameters:\n        ");
    if (source->has_pm25 == 1)
        printf("PM25 ");
    if (source->has_pm10 == 1)
        printf("PM10 ");
    if (source->has_bc == 1)
        printf("BC ");
    if (source->has_no2 == 1)
        printf("NO2 ");
    if (source->has_so2 == 1)
        printf("SO2 ");
    if (source->has_o3 == 1)
        printf("O3 ");
    if (source->has_co == 1)
        printf("CO ");
    printf("\n\n"); 
}

void print_locations(locations_t *source)
{
    if(source->size == 0)
        puts("No locations found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_location(source->locations_array + i);
    }
}

void print_city(city_t *source)
{
    printf("    * Name:\t\t%s\n", source->name);
    printf("    * Country code:\t%s\n", source->country_code);
    printf("    * # of locations:\t%d\n\n", source->n_locations);
}

void print_cities(cities_t *source)
{
    if(source->size == 0)
        puts("No cities found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_city(source->cities_array + i);
    }
}

void print_country(country_t *source)
{
    printf("    * Name:\t\t%s\n", source->name);
    printf("    * Code:\t\t%s\n", source->country_code);
    printf("    * # of cities:\t%d\n", source->n_cities);
    printf("    * # of locations:\t%d\n\n", source->n_locations);
}

void print_countries(countries_t *source)
{
    if(source->size == 0)
        puts("No countries found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_country(source->countries_array + i);
    }
}

void print_measurement(measurement_t *measurement)
{
    printf("    * Location: \t\t%s\n", measurement->location);
    printf("    * Date: \t\t\t%s\n", measurement->date);
    printf("    * Latitude:\t\t\t%f\n", measurement->latitude);
    printf("    * Longitude:\t\t%f\n", measurement->longitude);
    
    if (measurement->bc != -1)
        print_value("    * BC", measurement->bc, measurement->bc_unit);
    if (measurement->co != -1)
        print_value("    * CO", measurement->co, measurement->co_unit);
    if (measurement->no2 != -1)
        print_value("    * NO2", measurement->no2, measurement->no2_unit);
    if (measurement->o3 != -1)
        print_value("    * O3", measurement->o3, measurement->o3_unit);
    if (measurement->pm10 != -1)
        print_value("    * PM10", measurement->pm10, measurement->pm10_unit);
    if (measurement->pm25 != -1)
        print_value("    * PM25", measurement->pm25, measurement->pm25_unit);
    if (measurement->so2 != -1)
        print_value("    * SO2", measurement->so2, measurement->so2_unit);
        
    printf("\n");
}

void print_measurements(measurements_t *source)
{
    if(source->size == 0)
        puts("No measurements found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_measurement(source->measurements_array + i);
    }
}

measurement_t *find_highest(measurements_t *measurements_data, parameter_t parameter)
{
    void *base;
    double max = -1;
    double val;
    size_t offset = offsets[parameter];
    measurement_t *highest = NULL;
        
    if (offset == 0)
    {
        printf("Invalid parameter. Valid parameters are: PM25, PM10, NO2, CO, BC, O3, SO2.\n");
        return NULL;
    }

    if (measurements_data->size == 0)
        return NULL;
    
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

