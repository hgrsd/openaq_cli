#include <stdio.h>

#include "args.h"

const char *HELP_STRING =   "\n[+] OpenAQ_CLI\n\n"
                            "* Modes:\n\n"
                            "  -g [-y/c/l country code/city/location]\t\tget measurements for country/city/location (latest if no date range specified)\n"
                            "  -h [PARAMETER] [-y/c/l country code/city/location]\tget highest measurement of PARAMETER in country/city\n"
                            "\t\t\t\t\t\t\tnote: location only works using a date range, otherwise there is nothing to compare\n\n"
                            "  -y\t\t\t\t\t\t\tlists all countries\n"
                            "  -c [COUNTRY CODE]\t\t\t\t\tlist all cities in COUNTRY\n"
                            "  -l [CITY]\t\t\t\t\t\tlist all locations in CITY\n\n"
                            "  -w [FILENAME]\t\t\t\t\t\twrite output in CSV format\n\n"
                            "* Date ranges\n\n"
                            "  -f [dd/mm/yyyy]\t\t\t\t\tmeasurements from this date (inclusive) and/or\n"
                            "  -t [dd/mm/yyyy]\t\t\t\t\tmeasurements to this date (inclusive)\n\n"
                            "* Examples:\n\n"
                            "  %s -y\n"
                            "  %s -c NL\n"
                            "  %s -l \"Dublin City\"\n"
                            "  %s -gy IE\n"
                            "  %s -gc Rotterdam -w amsterdam_latest.csv\n"
                            "  %s -gc London -f 01/01/2019 -t 03/01/2019 -w london_threedays.csv\n"                           
                            "  %s -h PM10 -y GB\n"
                            "  %s -h PM25 -c London -f 01/03/2019 -t 04/03/2019 -w london_pm25_highest.csv\n\n"
                            "* Note: use quotation marks around cities or locations comprising multiple words, e.g. \"Dublin City\".\n\n";

void print_info(char *program_name)
{
    printf(HELP_STRING, program_name, program_name, program_name, program_name, program_name, program_name, program_name, program_name);
}
