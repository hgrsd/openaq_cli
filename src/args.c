#include <stdio.h>

#include "args.h"

const char *HELP_STRING = "Usage: %s <mode> <target>\n"
                          "Modes: \n\n"
                          "\t" HELP "\t\t\t\tshow information\n"
                          "\t" LIST_COUNTRIES "\t\t\tlist all countries in database\n"
                          "\t" LIST_CITIES_BY_COUNTRY " <country code>\tlist all cities in country\n"
                          "\t" FETCH_LATEST_BY_CITY " <city>\t\tfetch latest measurements for city.\n\n"
                          "Note: use quotation marks around multi-word cities.\n";

void print_info(char *program_name)
{
    printf(HELP_STRING, program_name);
}
