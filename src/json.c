#include <jansson.h>
#include <string.h>
#include "string_util.h"

#include "json.h"

static json_t *get_results(const char *raw_data, json_t *root)
{
    json_t *return_array;

    if (!json_is_object(root))
    {
        puts("error");
        json_decref(root);
        return NULL;
    }
    return_array = json_object_get(root, "results");
    
    return return_array;
}

void json_extract_measurements(const char *raw_data, measurements_t *target)
{
    json_t *root, *results, *entry, *location, *measurements, *coordinates, *latitude, *longitude;
    json_t *measurement_line, *parameter, *date, *json_value, *unit;
    json_error_t error;
    double val;
    int array_size;
    const char *parameter_string;
   
    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);    
    array_size = json_array_size(results);
    if (target->measurements_array != NULL)
        free(target->measurements_array);
    target->measurements_array = (measurement_t *) malloc(sizeof(measurement_t) * array_size);
    init_measurements(target, array_size);
    
    for (int i = 0; i < array_size; i++)
    {
        entry = json_array_get(results, i);

        location = json_object_get(entry, "location");
        strcpy_s(target->measurements_array[i].location, json_string_value(location), LOCATION_MAX);  
        coordinates = json_object_get(entry, "coordinates");
        latitude = json_object_get(coordinates, "latitude");     
        longitude = json_object_get(coordinates, "longitude");    
        target->measurements_array[i].latitude = json_real_value(latitude); 
        target->measurements_array[i].longitude = json_real_value(longitude);  

        measurements = json_object_get(entry, "measurements");
        for (int j = 0; j < json_array_size(measurements); j++)
        {
            measurement_line = json_array_get(measurements, j);
            parameter = json_object_get(measurement_line, "parameter");
            date = json_object_get(measurement_line, "lastUpdated");
            strcpy_s(target->measurements_array[i].date, json_string_value(date), DATE_MAX);
            parameter_string = json_string_value(parameter);
            json_value = json_object_get(measurement_line, "value");
            unit = json_object_get(measurement_line, "unit");
            val = json_number_value(json_value);
            if (val < 0)
                continue;
            if (strcmp(parameter_string, "pm25") == 0)
            {
                target->measurements_array[i].pm25 = val;
                strcpy_s(target->measurements_array[i].pm25_unit, json_string_value(unit), UNIT_MAX);
            }
            else if (strcmp(parameter_string, "pm10") == 0)
            {
                target->measurements_array[i].pm10 = val;
                strcpy_s(target->measurements_array[i].pm10_unit, json_string_value(unit), UNIT_MAX);
            }
            else if (strcmp(parameter_string, "o3") == 0)
            {
                target->measurements_array[i].o3 = val;
                strcpy_s(target->measurements_array[i].o3_unit, json_string_value(unit), UNIT_MAX);
            }
            else if (strcmp(parameter_string, "so2") == 0)
            {
                target->measurements_array[i].so2 = val;
                strcpy_s(target->measurements_array[i].so2_unit, json_string_value(unit), UNIT_MAX);
            }
            else if (strcmp(parameter_string, "no2") == 0)
            {
                target->measurements_array[i].no2 = val;
                strcpy_s(target->measurements_array[i].no2_unit, json_string_value(unit), UNIT_MAX);
            }
            else if (strcmp(parameter_string, "co") == 0)
            {
                target->measurements_array[i].co = val;
                strcpy_s(target->measurements_array[i].co_unit, json_string_value(unit), UNIT_MAX);
            }
            else if (strcmp(parameter_string, "bc") == 0)
            {
                target->measurements_array[i].bc = val;
                strcpy_s(target->measurements_array[i].bc_unit, json_string_value(unit), UNIT_MAX);
            }
            else
                printf("Unknown parameter: %s. Ignoring.\n", parameter_string);
        }
    }

    json_decref(root);
}

void json_print_cities(const char *raw_data)
{
    json_t *root, *results, *entry, *city, *locations;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);
    
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        city = json_object_get(entry, "city");
        locations = json_object_get(entry, "locations");
        printf("\n%d. %s: %lld location(s).", i + 1, 
                json_string_value(city), json_integer_value(locations));
    }
    printf("\n");

    json_decref(root);
}

void json_print_locations(const char *raw_data)
{
    json_t *root, *results, *entry, *location, *parameters, *parameter, *coordinates, *latitude, *longitude;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);
   
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        location = json_object_get(entry, "location");
        parameters = json_object_get(entry, "parameters");
        coordinates = json_object_get(entry, "coordinates");
        latitude = json_object_get(coordinates, "latitude");
        longitude = json_object_get(coordinates, "longitude");
        printf("\n\n%d.\t%s\n\tLatitude: %f\n\tLongitude: %f\n\tParameters: ", 
                i + 1, 
                json_string_value(location),
                json_real_value(latitude),
                json_real_value(longitude));
        for (int j = 0; j < json_array_size(parameters); j++)
        {
            parameter = json_array_get(parameters, j);
            printf("%s ", json_string_value(parameter));
        }        
    }
    printf("\n\n");

    json_decref(root);
}

void json_print_countries(const char *raw_data)
{
    json_t *root, *results, *entry, *country, *country_code, *cities;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);
    
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        country = json_object_get(entry, "name");
        country_code = json_object_get(entry, "code");
        cities = json_object_get(entry, "cities");
        printf("\n%4d. %2s - %45s (%lld cities)", 
                i + 1, 
                json_string_value(country_code), 
                json_string_value(country),
                json_integer_value(cities));
    }
    printf("\n");

    json_decref(root);
}