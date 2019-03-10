#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "args.h"
#include "core.h"

int main(int argc, char *argv[])
{   
    int highest_flag = 0;
    char *highest_parameter;
    int get_flag = 0;
    int country_flag = 0;
    char *country;
    int city_flag = 0;
    char *city;
    int location_flag = 0;
    char *location;
    int write_flag = 0;
    char *out_file;
    int c;

    extern char *optarg;
    extern int opterr, optopt;
    opterr = 0; // disables getopt's error messages

    // read arguments from command line and set flags
    while ((c = getopt(argc, argv, "gy:c:l:w:h:")) != -1)
    {
        switch(c)
        {
            case 'y':
                country_flag = 1;
                country = optarg;                
                break;
            
            case 'c':
                city_flag = 1;
                city = optarg;
                break;

            case 'l':
                location_flag = 1;
                location = optarg;
                break;
            
            case 'w':
                write_flag = 1;
                out_file = optarg;
                break;
            
            case 'h':
                highest_flag = 1;
                highest_parameter = optarg;
                break;

            case 'g':
                get_flag = 1;
                break;
            
            case '?':
                if (optopt == 'y')
                {
                    country_flag = 1;
                    country = NULL;
                }
                else
                {
                    print_info(argv[0]);
                    return 1;
                }
        }
    }

    // process flags and call relevant function
    if (get_flag == 1)
    {
        if (country_flag == 1 && country != NULL)
        {
            print_latest_by_country(country);
        }
        else if (city_flag == 1)
        {
            print_latest_by_city(city);
        }
        else if (location_flag == 1)
        {
            print_latest_by_location(location);
        }
        else
        {
            print_info(argv[0]);
            return 1;
        }
    }
    else if (highest_flag == 1)
    {
        if (country_flag == 1 && country != NULL)
        {
            print_highest_by_country(country, highest_parameter);
        }
        else if (city_flag == 1)
        {
            print_highest_by_city(city, highest_parameter);
        }
        else
        {
            print_info(argv[0]);
            return 1;
        }
    }
    else if (country_flag == 1)
    {
        if (country == NULL)
            print_all_countries();
        else
        {
            print_cities_by_country(country);
        }
    }
    else if (city_flag == 1)
    {
        print_locations_by_city(city);
    }
    else
    {
        print_info(argv[0]);
        return 1;
    }

    return 0;
}