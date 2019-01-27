#include <stdlib.h>
#include <jansson.h>
#include <string.h>

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

void init_measurements(struct measurements *target)
{
    for (int i = 0; i < MAX_MEASUREMENTS; i++)
    {
        target->measurements_array[i].bc = -1;
        target->measurements_array[i].co = -1;
        target->measurements_array[i].no2 = -1;
        target->measurements_array[i].o3 = -1;
        target->measurements_array[i].pm10 = -1;
        target->measurements_array[i].pm25 = -1;
        target->measurements_array[i].so2 = -1;
        target->size = 0;
    }
}

void print_measurements(struct measurements *source)
{
    for (int i = 0; i < source->size; i++)
    {
        printf("\nLocation: \t\t%s\n", source->measurements_array[i].location);
        printf("Date: \t\t\t%s\n", source->measurements_array[i].date);
        printf("Values:\n");
        printf("\t\t\tBC: %.2f\n", source->measurements_array[i].bc);
        printf("\t\t\tCO: %.2f\n", source->measurements_array[i].co);
        printf("\t\t\tNo2: %.2f\n", source->measurements_array[i].no2);
        printf("\t\t\to3: %.2f\n", source->measurements_array[i].o3);
        printf("\t\t\tpm10: %.2f\n", source->measurements_array[i].pm10);
        printf("\t\t\tpm25: %.2f\n", source->measurements_array[i].pm25);
        printf("\t\t\tso2: %.2f\n\n", source->measurements_array[i].so2);
    }
}

void json_extract_measurements(char *raw_data, struct measurements *target)
{
    json_t *root, *results, *entry, *location, *measurements;
    json_t *measurement_line, *parameter, *date, *value;
    json_error_t error;
    char *parameter_string;

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
        strcpy(target->measurements_array[i].location, json_string_value(location));
        for (int j = 0; j < json_array_size(measurements) && j < MAX_MEASUREMENTS; j++)
        {
            measurement_line = json_array_get(measurements, j);
            parameter = json_object_get(measurement_line, "parameter");
            date = json_object_get(measurement_line, "lastUpdated");
            strcpy(target->measurements_array[i].date, json_string_value(date));
            parameter_string = json_string_value(parameter);
            value = json_object_get(measurement_line, "value");
            if (strcmp(parameter_string, "pm25") == 0)
                target->measurements_array[i].pm25 = json_real_value(value);
            else if (strcmp(parameter_string, "pm10") == 0)
                target->measurements_array[i].pm10 = json_real_value(value);
            else if (strcmp(parameter_string, "o3") == 0)
                target->measurements_array[i].o3 = json_real_value(value);
            else if (strcmp(parameter_string, "so2") == 0)
                target->measurements_array[i].so2 = json_real_value(value);
            else if (strcmp(parameter_string, "no2") == 0)
                target->measurements_array[i].no2 = json_real_value(value);
            else if (strcmp(parameter_string, "co") == 0)
                target->measurements_array[i].co = json_real_value(value);
            else if (strcmp(parameter_string, "bc") == 0)
                target->measurements_array[i].bc = json_real_value(value);
            else
                printf("Unknown parameter: %s. Ignoring.\n", parameter_string);
            json_decref(parameter);
            json_decref(value);
            json_decref(date)
        }
        target->size++;
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
        json_decref(entry);
        json_decref(city);
        json_decref(locations);
    }
    json_decref(results);
    json_decref(root);
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
        json_decref(entry);
        json_decref(location);
        json_decref(parameters);
    }
    json_decref(root);
    json_decref(results);
}