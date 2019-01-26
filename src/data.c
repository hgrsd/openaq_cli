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
    json_t *root, *results, *entry, *city;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    if (!json_is_object(root))
        puts("error");
    results = json_object_get(root, "results");
    if (json_is_array(results))
        puts("It's an array, hooray!");
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        city = json_object_get(entry, "city");
        puts(json_string_value(city));
    }
}