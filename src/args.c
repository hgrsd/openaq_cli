#include <stdio.h>

#include "args.h"

const char *HELP_STRING =   "\nModes:\n\n"
                            "  -y\t\t\t\t\t\tlists all countries\n"
                            "  -c [COUNTRY CODE]\t\t\t\tlist all cities in COUNTRY\n"
                            "  -l [CITY]\t\t\t\t\tlist all locations in CITY\n\n"
                            "  -g [-y/c/l country code/city/location]\tget latest measurements for country/city/location\n"
                            "  -h [PARAMETER] [-y/c country code/city]\tget highest measurement of PARAMETER in country/city\n"
                            "  -w [FILENAME]\t\t\t\t\toutput in CSV format\n\n\n"
                            "Examples:\n\n"
                            "  %s -y\n"
                            "  %s -c NL\n"
                            "  %s -l \"Dublin City\"\n"
                            "  %s -gy IE\n"
                            "  %s -gc Amsterdam\n"
                            "  %s -gc Amsterdam -w amsterdam_latest.csv\n"
                            "  %s -h PM10 -y GB\n"
                            "  %s -h PM25 -c London -w london_pm25_highest.csv\n\n"
                            "Note: use quotation marks around cities or locations comprising multiple words, e.g. \"Dublin City\".\n\n";

void print_info(char *program_name)
{
    printf(HELP_STRING, program_name, program_name, program_name, program_name, program_name, program_name, program_name, program_name);
}
