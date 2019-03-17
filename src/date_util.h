#ifndef _DATE_UTILS_H
#define _DATE_UTILS_H
#define _XOPEN_SOURCE 

#include <time.h>


time_t string_to_timestamp(const char* string);
void timestamp_to_string(char *string, time_t timestamp);

#endif