#ifndef _JSON_H_
#define _JSON_H_

#include "data.h"


void json_extract_cities(char *raw_data);
void json_extract_countries(char *raw_data);
void json_extract_locations(char *raw_data);
void json_extract_measurements(char *raw_data, measurements_t *target);

#endif