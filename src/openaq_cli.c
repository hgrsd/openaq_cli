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
    char *country_arg = NULL;
    int city_flag = 0;
    char *city_arg = NULL;
    int location_flag = 0;
    char *location_arg = NULL;
    int write_flag = 0;
    char *out_file = NULL;
    int date_flag = 0;
    char *from_date = NULL;
    char *to_date = NULL;
    int c;

    extern char *optarg;
    extern int opterr, optopt, optind;
    opterr = 0; // disables getopt's error messages

    // read arguments from command line and set flags
    while ((c = getopt(argc, argv, "gy:c:l:w:h:f:t:")) != -1)
    {
        switch(c)
        {
            case 'y':
                country_flag = 1;
                if (optarg[0] != '-')
                    country_arg = optarg;
                else
                    optind--;                
                break;
            
            case 'c':
                city_flag = 1;
                city_arg = optarg;
                break;

            case 'l':
                location_flag = 1;
                location_arg = optarg;
                break;
            
            case 'w':
                printf("[+] Entering writing mode.\n");
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
            
            case 'f':
                date_flag = 1;
                from_date = optarg;
                break;
            
            case 't':
                date_flag = 1;
                to_date = optarg;
                break;

            case '?':
                if (optopt == 'y')
                {
                    country_flag = 1;
                    country_arg = NULL;
                }
                else
                {
                    print_info(argv[0]);
                    return 1;
                }
        }
    }

    // process flags and call relevant function
    if (get_flag)
    {
        if (country_flag && country_arg != NULL)
        {
            if (date_flag)
            {
                if (write_flag)
                    date_range(REQUEST_COUNTRY, country_arg, from_date, to_date, TO_CSV, out_file);
                else
                    date_range(REQUEST_COUNTRY, country_arg, from_date, to_date, TO_SCREEN, NULL);
            }
            else if (write_flag)
                latest(REQUEST_COUNTRY, country_arg, TO_CSV, out_file);
            else
                latest(REQUEST_COUNTRY, country_arg, TO_SCREEN, NULL);
        }
        else if (city_flag)
        {
            if (date_flag)
            {
                if (write_flag)
                    date_range(REQUEST_CITY, city_arg, from_date, to_date, TO_CSV, out_file);
                else
                    date_range(REQUEST_CITY, city_arg, from_date, to_date, TO_SCREEN, NULL);
            }
            else if (write_flag)
                latest(REQUEST_CITY, city_arg, TO_CSV, out_file);
            else
                latest(REQUEST_CITY, city_arg, TO_SCREEN, NULL);
        }
        else if (location_flag)
        {
            if (date_flag)
            {
                if (write_flag)
                    date_range(REQUEST_LOCATION, location_arg, from_date, to_date, TO_CSV, out_file);
                else
                    date_range(REQUEST_LOCATION, location_arg, from_date, to_date, TO_SCREEN, NULL);
            }
            else if (write_flag)
                latest(REQUEST_LOCATION, location_arg, TO_CSV, out_file);
            else
                latest(REQUEST_LOCATION, location_arg, TO_SCREEN, NULL);
        }
        else
        {
            print_info(argv[0]);
            return 1;
        }
    }
    else if (highest_flag)
    {
        if (country_flag && country_arg != NULL)
        {
            if (date_flag)
            {
                if (write_flag)
                    highest_range(REQUEST_COUNTRY, country_arg, highest_parameter, from_date, to_date, TO_CSV, out_file);
                else
                    highest_range(REQUEST_COUNTRY, country_arg, highest_parameter, from_date, to_date, TO_SCREEN, NULL);
            }
            else if (write_flag)
                highest(REQUEST_COUNTRY, country_arg, highest_parameter, TO_CSV, out_file);
            else
                highest(REQUEST_COUNTRY, country_arg, highest_parameter, TO_SCREEN, NULL);
        }
        else if (city_flag)
        {
            if (date_flag)
            {
                if (write_flag)
                    highest_range(REQUEST_CITY, city_arg, highest_parameter, from_date, to_date, TO_CSV, out_file);
                else
                    highest_range(REQUEST_CITY, city_arg, highest_parameter, from_date, to_date, TO_SCREEN, NULL);
            }
            else if (write_flag)
                highest(REQUEST_CITY, city_arg, highest_parameter, TO_CSV, out_file);
            else
                highest(REQUEST_CITY, city_arg, highest_parameter, TO_SCREEN, NULL);
        }
        else
        {
            print_info(argv[0]);
            return 1;
        }
    }
    else if (country_flag)
    {
        if(write_flag)
            all_countries(TO_CSV, out_file);
        else
            all_countries(TO_SCREEN, NULL);
    }
    else if (city_flag)
    {
        if (write_flag)
            cities_by_country(city_arg, TO_CSV, out_file);
        else
            cities_by_country(city_arg, TO_SCREEN, NULL);
    }
    else if (location_flag)
    {
        if (write_flag)
            locations_by_city(location_arg, TO_CSV, out_file);
        else
            locations_by_city(location_arg, TO_SCREEN, NULL);
    }
    else
    {
        print_info(argv[0]);
        return 1;
    }

    return 0;
}