#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "api_calls.h"
#include "data.h"
#include "json.h"
#include "args.h"

int main(int argc, char *argv[])
{
    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    if (argc < 2)
    {
        printf("Invalid arguments. ");
        print_info(argv[0]);
        return 1;
    } 

    init_data(&raw_data);

    if (!strcmp(argv[1], HELP))
    {
        print_info(argv[0]);
    }
    else if (!strcmp(argv[1], LIST_COUNTRIES))
    {
        fetch_countries(&raw_data);
        json_extract_countries(raw_data.data);
        clear_data(&raw_data);
    }
    else if (!strcmp(argv[1], LIST_COUNTRIES))
    {
        fetch_countries(&raw_data);
        json_extract_countries(raw_data.data);
        clear_data(&raw_data);
    }
    else if (!strcmp(argv[1], LIST_CITIES_BY_COUNTRY))
    {
        if (argc < 3)
        {
            puts("No country code specified.");
            print_info(argv[0]);
            return 1;
        }
        else
        {
            fetch_cities(argv[2], &raw_data);
            json_extract_cities(raw_data.data);
            clear_data(&raw_data);
        }
    }
    else if (!strcmp(argv[1], FETCH_LATEST_BY_CITY))
    {
        if (argc < 3)
        {
            puts("No city specified.");
            print_info(argv[0]);
            return 1;
        }
        else
        {
            fetch_latest_by_city(argv[2], &raw_data);
            json_extract_measurements(raw_data.data, &measurements_data);
            clear_data(&raw_data);
            print_measurements(&measurements_data);
            free(measurements_data.measurements_array);
        }
    }
    else
    {
        puts("Argument not recognised.");
        print_info(argv[0]);
        return 1;
    }

    return 0;
}