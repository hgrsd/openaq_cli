#ifndef _JSON_H_
#define _JSON_H_

#include "data.h"


void json_extract_cities(const char *raw_data);
void json_extract_countries(const char *raw_data);
void json_extract_locations(const char *raw_data);
void json_extract_measurements(const char *raw_data, measurements_t *target);

#endif