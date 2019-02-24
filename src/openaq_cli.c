#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "args.h"
#include "core.h"

int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        print_info(argv[0]);
        return 1;
    } 
    if (!strcmp(argv[1], HELP))
    {
        print_info(argv[0]);
    }
    else if (!strcmp(argv[1], LIST_COUNTRIES))
    {
        list_countries();
    }
    else if (!strcmp(argv[1], LIST_CITIES_BY_COUNTRY))
    {
        if (argc < 3)
        {
            puts("No country code specified.");
            print_info(argv[0]);
            return 1;
        }
        list_cities_by_country(argv[2]);
    }
    else if (!strcmp(argv[1], LIST_LOCATIONS_BY_CITY))
    {
        if (argc < 3)
        {
            puts("No city specified.");
            print_info(argv[0]);
            return 1;
        }
        list_locations_by_city(argv[2]);
    }
    else if (!strcmp(argv[1], PRINT_LATEST_BY_CITY))
    {
        if (argc < 3)
        {
            puts("No city specified.");
            print_info(argv[0]);
            return 1;
        }
        print_latest_by_city(argv[2]);
    }
    else if (!strcmp(argv[1], PRINT_LATEST_BY_LOCATION))
    {
        if (argc < 3)
        {
            puts("No location specified.");
            print_info(argv[0]);
            return 1;
        }
        print_latest_by_location(argv[2]);
    }
    else if (!strcmp(argv[1], FIND_HIGHEST_BY_CITY))
    {
        if (argc < 4)
        {
            puts("No city and/or parameter specified.");
            print_info(argv[0]);
            return 1;
        }
        find_highest_by_city(argv[2], argv[3]);
    }
    else if (!strcmp(argv[1], FIND_HIGHEST_BY_COUNTRY))
    {
        if (argc < 4)
        {
            puts("No country code and/or parameter specified.");
            print_info(argv[0]);
            return 1;
        }
        find_highest_by_country(argv[2], argv[3]);
    }
    else
    {
        print_info(argv[0]);
        return 1;
    }
    return 0;
}