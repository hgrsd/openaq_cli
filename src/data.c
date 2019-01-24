#include <stdlib.h>
#include <jansson.h>

#include "data.h"

void clear_data(struct response_data *data)
{
    free(data->data);
    data->data = malloc(1);
    data->size = 0;
}

void init_data(struct response_data *data)
{
    data->data = malloc(1);
    data->size = 0;
}

void json_extract_cities(char *raw_data)
{
    
}