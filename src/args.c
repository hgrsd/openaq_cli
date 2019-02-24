#include <stdio.h>

#include "args.h"

const char *HELP_STRING = "\nUsage: %s <mode> <target>\n"
                          "\nModes: \n\n"
                          "\t"HELP "\t\t\t\t\t\tshow information\n"
                          "\t"LIST_COUNTRIES "\t\t\t\t\tlist all countries in database\n"
                          "\t"LIST_CITIES_BY_COUNTRY " <country code>\t\t\tlist all cities in <country>\n"
                          "\t"LIST_LOCATIONS_BY_CITY " <city>\t\t\t\tlists all locations in <city>\n"
                          "\t"PRINT_LATEST_BY_LOCATION " <location>\t\t\tfetch latest measurements for <location>\n"
                          "\t"PRINT_LATEST_BY_CITY " <city>\t\t\t\tfetch latest measurements for <city>.\n"
                          "\t"FIND_HIGHEST_BY_COUNTRY " <country code> <parameter>\tfetch latest measurements for <country>.\n"
                          "\t"FIND_HIGHEST_BY_CITY " <city> <parameter>\t\tfind location within <city> with highest parameter <parameter>\n"
                          "\nNote: use quotation marks around multi-word cities or locations.\n\n";

void print_info(char *program_name)
{
    printf(HELP_STRING, program_name);
}
