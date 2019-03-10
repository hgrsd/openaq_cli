#include <stdio.h>

#include "args.h"

const char *HELP_STRING = "\n** Modes:\n\n  -g [-y/c/l country code/city/location]:\tget latest measurements\n"
                            "  -h [PARAMETER] [-y/c country code/city]:\tget highest measurement of PARAMETER\n"
                            "  -y [COUNTRY CODE]:\t\t\t\tlist cities in COUNTRY, or list all countries if COUNTRY is not specified\n"
                            "  -c [CITY]:\t\t\t\t\tlist locations in CITY\n\n"
                            "** Note: use quotation marks around cities or locations comprising multiple words, e.g. \"Dublin City\".\n\n";

void print_info(char *program_name)
{
    printf(HELP_STRING, program_name);
}
