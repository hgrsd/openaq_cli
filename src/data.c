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

void json_extract_measurements(char *raw_data)
{
    json_t *root, *results, *entry, *location, *measurements;
    json_t *measurement_line, *parameter, *value, *unit;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    if (!json_is_object(root))
    {
        puts("error");
        json_decref(root);
        return;
    }
    results = json_object_get(root, "results");
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        location = json_object_get(entry, "location");
        measurements = json_object_get(entry, "measurements");
        printf("%d. Location: %s.\n", i + 1, json_string_value(location));
        for (int j = 0; j < json_array_size(measurements); j++)
        {
            measurement_line = json_array_get(measurements, j);
            parameter = json_object_get(measurement_line, "parameter");
            value = json_object_get(measurement_line, "value");
            unit = json_object_get(measurement_line, "unit");
            printf("\t\tParameter: %s -- %lld %s.\n", 
                    json_string_value(parameter),
                    json_integer_value(value),
                    json_string_value(unit));
            json_decref(measurement_line);
            json_decref(parameter);
            json_decref(value);
            json_decref(unit);
        }
        json_decref(entry);
        json_decref(location);
        json_decref(measurements);
    }
    json_decref(root);
    json_decref(results);
}

void json_extract_cities(char *raw_data)
{
    json_t *root, *results, *entry, *city, *locations;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    if (!json_is_object(root))
    {
        puts("error");
        json_decref(root);
        return;
    }
    results = json_object_get(root, "results");
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        city = json_object_get(entry, "city");
        locations = json_object_get(entry, "locations");
        printf("%d. %s: %lld location(s).\n", i + 1, 
                json_string_value(city), json_integer_value(locations));
    }
    json_decref(entry);
    json_decref(city);
    json_decref(city);
    json_decref(locations);
    json_decref(results);
}

void json_extract_locations(char *raw_data)
{
    json_t *root, *results, *entry, *location, *parameters, *parameter;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    if (!json_is_object(root))
    {
        puts("error");
        json_decref(root);
        return;
    }
    results = json_object_get(root, "results");
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        location = json_object_get(entry, "location");
        parameters = json_object_get(entry, "parameters");
        printf("%d.\tLocation: %s\n\tParameters: ", i + 1, json_string_value(location));
        for (int j = 0; j < json_array_size(parameters); j++)
        {
            parameter = json_array_get(parameters, j);
            printf("%s ", json_string_value(parameter));
            json_decref(parameter);
        }
        printf("\n");
    }
    json_decref(entry);
    json_decref(location);
    json_decref(parameters);
    json_decref(root);
    json_decref(parameter);
}