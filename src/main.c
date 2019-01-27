#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "api_calls.h"
#include "data.h"



int main(void)
{
    struct response_data raw_data;
    char city[MAX_REQUEST_SIZE];
    char country[3];

    init_data(&raw_data);
    puts("Please enter abbreviation of the country: ");
    scanf("%2s", country);

    fetch_cities(country, &raw_data);
    json_extract_cities(raw_data.data);
    clear_data(&raw_data);

    puts("Enter city: ");
    scanf("%s", city);
    fetch_latest_by_city(city, &raw_data);
    json_extract_measurements(raw_data.data);

    return 0;
}