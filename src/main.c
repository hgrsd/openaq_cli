#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "api_calls.h"
#include "data.h"
#include "json.h"
#include "string_util.h"

const char *help_string = "Usage: %s <mode> <target>\n"
                          "modes: \n\t-l: list countries in database\n"
                          "\t-lc <country code>: list cities in country\n"
                          "\t-gc <city>: get latest measurements for city.\n"
                          "\t(use quotation marks around multi-word cities).\n";



int main(int argc, char *argv[])
{
    response_data_t raw_data;
    measurements_t measurements_data = {NULL, 0};

    if (argc < 2)
    {
        printf("Invalid arguments.\n");
        printf(help_string, argv[0]);
        return 1;
    } 

    init_data(&raw_data);

    if (!strcmp(argv[1], "-l"))
    {
        fetch_countries(&raw_data);
        json_extract_countries(raw_data.data);
        clear_data(&raw_data);
    }
    else if (!strcmp(argv[1], "-lc"))
    {
        if (argc < 3)
        {
            puts("No country code specified.");
            printf(help_string, argv[0]);
            return 1;
        }
        else
        {
            fetch_cities(argv[2], &raw_data);
            json_extract_cities(raw_data.data);
            clear_data(&raw_data);
        }
    }
    else if (!strcmp(argv[1], "-gc"))
    {
        if (argc < 3)
        {
            puts("No city specified.");
            printf(help_string, argv[0]);
            return 1;
        }
        else
        {
            fetch_latest_by_city(argv[2], &raw_data);
            json_extract_measurements(raw_data.data, &measurements_data);
            clear_data(&raw_data);
            print_measurements(&measurements_data);
        }
    }

    return 0;
}