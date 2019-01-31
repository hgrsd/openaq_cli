#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "api_calls.h"
#include "data.h"
#include "json.h"

char *trim(char *string)
{
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';

    return string;
}

int main(void)
{
    response_data_t raw_data;
    measurements_t measurements_data;
    char city[MAX_REQUEST_SIZE];
    char country[3];

    init_data(&raw_data);

    puts("Please enter abbreviation of the country: ");
    scanf("%2s", country);
    while (getchar() != '\n')
        continue;
    fetch_cities(country, &raw_data);
    json_extract_cities(raw_data.data);
    
    printf("Enter city/region (q to quit):\n> ");
    fgets(city, MAX_REQUEST_SIZE, stdin);
    while(strcmp(city, "q\n") != 0)
    {
        clear_data(&raw_data);
        init_measurements(&measurements_data);
        fetch_latest_by_city(trim(city), &raw_data);
        json_extract_measurements(raw_data.data, &measurements_data);
        print_measurements(&measurements_data);
        printf("Enter city/region (q to quit):\n> ");
        fgets(city, MAX_REQUEST_SIZE, stdin);
    }

    return 0;
}