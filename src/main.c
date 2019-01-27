#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "api_calls.h"
#include "data.h"

int main(void)
{
    struct response_data raw_data;
    struct measurements measurements_data;
    char city[MAX_REQUEST_SIZE];
    char country[3];

    init_data(&raw_data);
    puts("Please enter abbreviation of the country: ");
    scanf("%2s", country);
    while (getchar() != '\n')
        continue;
    fetch_cities(country, &raw_data);
    json_extract_cities(raw_data.data);

    while(strcmp(city, "q") != 0)
    {
        clear_data(&raw_data);
        init_measurements(&measurements_data);
        printf("Enter city/region (q to quit):\n> ");
        scanf("%s", city);
        while (getchar() != '\n')
            continue;
        fetch_latest_by_city(city, &raw_data);
        json_extract_measurements(raw_data.data, &measurements_data);
        print_measurements(&measurements_data);
    }

    return 0;
}