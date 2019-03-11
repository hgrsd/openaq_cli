#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "core.h"

#include "api_calls.h"
#include "data.h"
#include "io.h"
#include "json.h"
#include "string_util.h"

void all_countries(print_mode_t mode, const char *filename)
{   
    int lines_written;

    response_data_t raw_data;
    countries_t countries_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_countries(&raw_data);
    json_extract_countries(raw_data.data, &countries_data);
    
    if (mode == TO_CSV)
    {
        lines_written = write_countries(&countries_data, filename);
        if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
    }
    else
        print_countries(&countries_data);

    clear_data(&raw_data);
    free(countries_data.countries_array);
}

void cities_by_country(const char *country, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    cities_t cities_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_cities(country, &raw_data);
    json_extract_cities(raw_data.data, &cities_data);

    if (mode == TO_CSV)
    {
        lines_written = write_cities(&cities_data, filename);
        if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
    }
    else
        print_cities(&cities_data);

    clear_data(&raw_data);
    free(cities_data.cities_array);
}

void locations_by_city(const char *city, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    locations_t locations_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_locations_by_city(city, &raw_data);
    json_extract_locations(raw_data.data, &locations_data);

    if (mode == TO_CSV)
    {
        lines_written = write_locations(&locations_data, filename);
        if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
    }
    else
        print_locations(&locations_data);

    clear_data(&raw_data);   
    free(locations_data.locations_array);
}

void latest_by_country(const char *country, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_country(country, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);

    if (mode == TO_CSV)
    {
        lines_written = write_measurements(&measurements_data, filename);
        if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
    }
    else
        print_measurements(&measurements_data);

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}

void latest_by_city(const char *city, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_city(city, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);

    if (mode == TO_CSV)
    {
        lines_written = write_measurements(&measurements_data, filename);
        if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
    }
    else
        print_measurements(&measurements_data);

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}

void latest_by_location(const char *location, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_location(location, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);
    
    if (mode == TO_CSV)
    {
        lines_written = write_measurements(&measurements_data, filename);
        if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
    }
    else
        print_measurements(&measurements_data);

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}

void highest_by_country(const char *country_code, const char *parameter, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};
    measurements_t highest = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_country(country_code, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);

    highest.measurements_array = find_highest(&measurements_data, string_to_param(parameter));
    if (highest.measurements_array != NULL)
    {
        highest.size = 1;
        if (mode == TO_CSV)
        {
            lines_written = write_measurements(&highest, filename);
            if (lines_written)
                printf("    * written %d lines to file\n", lines_written);
        }
        else
        {
            printf("\n[+] Highest amount of %s found in the following location: \n\n", parameter);
            print_measurements(&highest);
        }
    }
    else
        printf("    * highest not found.\n");

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}

void highest_by_city(const char *city, const char *parameter, print_mode_t mode, const char *filename)
{
    int lines_written;

    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};
    measurements_t highest = {NULL, 0};

    init_data(&raw_data);
    api_fetch_latest_by_city(city, &raw_data);
    json_extract_measurements(raw_data.data, &measurements_data);

    highest.measurements_array = find_highest(&measurements_data, string_to_param(parameter));
    if (highest.measurements_array != NULL)
    {
        highest.size = 1;
        if (mode == TO_CSV)
        {
            lines_written = write_measurements(&highest, filename);
            if (lines_written)
                printf("    * written %d line(s) to file.\n", lines_written);
        }
        else
        {
            printf("\n    * highest amount of %s found in the following location: \n\n", parameter);
            print_measurements(&highest);
        }
    }
    else
        printf("    * highest not found.\n");

    clear_data(&raw_data);
    free(measurements_data.measurements_array);
}