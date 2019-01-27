#ifndef _DATA_H_
#define _DATA_H_

struct response_data
{
    char *data;
    int size;
};

void clear_data(struct response_data *data);
void init_data(struct response_data *data);

void json_extract_cities(char *raw_data);
void json_extract_locations(char *raw_data);
void json_extract_measurements(char *raw_data);

#endif