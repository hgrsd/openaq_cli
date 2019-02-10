#include <stdio.h>

#include "args.h"

const char *HELP_STRING = "Usage: %s <mode> <target>\n"
                          "Modes: \n\n"
                          "\t"HELP "\t\t\t\t\tshow information\n"
                          "\t"LIST_COUNTRIES "\t\t\t\tlist all countries in database\n"
                          "\t"LIST_CITIES_BY_COUNTRY " <country code>\t\tlist all cities in country\n"
                          "\t"LIST_LOCATIONS_BY_CITY " <city>\t\t\tlists all locations in city\n"
                          "\t"FETCH_LATEST_BY_LOCATION " <location>\tfetch latest measurements for location\n"
                          "\t"FETCH_LATEST_BY_CITY " <city>\t\tfetch latest measurements for city.\n\n"
                          "Note: use quotation marks around multi-word cities or locations.\n";

void print_info(char *program_name)
{
    printf(HELP_STRING, program_name);
}
