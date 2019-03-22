#ifndef _ARGS_H_
#define _ARGS_H_

typedef enum request_type
{
    REQUEST_COUNTRY,
    REQUEST_CITY,
    REQUEST_LOCATION,
} request_type_t;

typedef enum print_mode
{
    TO_SCREEN,
    TO_CSV
} print_mode_t;

void print_info(char *program_name);

#endif