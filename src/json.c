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
    double val;
    int array_size;
    const char *parameter_string;
    
    json_t *root, *results, *entry, *location, *measurements, *coordinates, *latitude, *longitude;
    json_t *measurement_line, *parameter, *date, *json_value, *unit;
    json_error_t error; 
    
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
            parameter_string = json_string_value(parameter);
            json_value = json_object_get(measurement_line, "value");
            unit = json_object_get(measurement_line, "unit");
            val = json_number_value(json_value);

            strcpy_s(target->measurements_array[i].date, json_string_value(date), DATE_MAX);
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

void json_extract_cities(const char *raw_data, cities_t *target)
{
    int array_size;

    json_t *root, *results, *entry, *city, *locations, *country_code;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);    
    array_size = json_array_size(results);
    
    if (target->cities_array != NULL)
        free(target->cities_array);
    target->cities_array = (city_t *) malloc(sizeof(city_t) * array_size);
    init_cities(target, array_size);
    
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        city = json_object_get(entry, "city");
        locations = json_object_get(entry, "locations");
        country_code = json_object_get(entry, "country");
        strcpy_s(target->cities_array[i].name, json_string_value(city), CITY_MAX);
        strcpy_s(target->cities_array[i].country_code, json_string_value(country_code), COUNTRY_CODE_MAX);
        target->cities_array[i].n_locations = json_integer_value(locations);

    }

    json_decref(root);
}

void json_extract_locations(const char *raw_data, locations_t *target)
{
    int array_size;
    const char *parameter_string;

    json_t *root, *results, *entry, *location, *parameters, *parameter, *coordinates, *latitude, *longitude, *country_code, *city;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);    
    array_size = json_array_size(results);
    
    if (target->locations_array != NULL)
        free(target->locations_array);
    target->locations_array = (location_t *) malloc(sizeof(location_t) * array_size);
    init_locations(target, array_size);
   
    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        location = json_object_get(entry, "location");
        city = json_object_get(entry, "city");
        country_code = json_object_get(entry, "country");
        parameters = json_object_get(entry, "parameters");
        coordinates = json_object_get(entry, "coordinates");
        latitude = json_object_get(coordinates, "latitude");
        longitude = json_object_get(coordinates, "longitude");
        strcpy_s(target->locations_array[i].name, json_string_value(location), LOCATION_MAX);
        strcpy_s(target->locations_array[i].city, json_string_value(city), CITY_MAX);
        strcpy_s(target->locations_array[i].country_code, json_string_value(country_code), COUNTRY_CODE_MAX);
        target->locations_array[i].latitude = json_real_value(latitude);
        target->locations_array[i].longitude = json_real_value(longitude);
        for (int j = 0; j < json_array_size(parameters); j++)
        {
            parameter = json_array_get(parameters, j);
            parameter_string = json_string_value(parameter);
            if (strcmp(parameter_string, "pm25") == 0)
                target->locations_array[i].has_pm25 = 1;
            else if (strcmp(parameter_string, "pm10") == 0)
                target->locations_array[i].has_pm10 = 1;
            else if (strcmp(parameter_string, "o3") == 0)
                target->locations_array[i].has_o3 = 1;
            else if (strcmp(parameter_string, "so2") == 0)
                target->locations_array[i].has_so2 = 1;
            else if (strcmp(parameter_string, "no2") == 0)
                target->locations_array[i].has_no2 = 1;
            else if (strcmp(parameter_string, "co") == 0)
                target->locations_array[i].has_co = 1;
            else if (strcmp(parameter_string, "bc") == 0)
                target->locations_array[i].has_bc = 1;
        }        
    }

    json_decref(root);
}

void json_extract_countries(const char *raw_data, countries_t *target)
{
    int array_size;

    json_t *root, *results, *entry, *country, *country_code, *cities, *locations;
    json_error_t error;

    root = json_loads(raw_data, 0, &error);
    results = get_results(raw_data, root);    
    array_size = json_array_size(results);
    
    if (target->countries_array != NULL)
        free(target->countries_array);
    target->countries_array = (country_t *) malloc(sizeof(country_t) * array_size);
    init_countries(target, array_size);

    for (int i = 0; i < json_array_size(results); i++)
    {
        entry = json_array_get(results, i);
        country = json_object_get(entry, "name");
        country_code = json_object_get(entry, "code");
        cities = json_object_get(entry, "cities");
        locations = json_object_get(entry, "locations");
        
        strcpy_s(target->countries_array[i].name, json_string_value(country), COUNTRY_MAX);
        strcpy_s(target->countries_array[i].country_code, json_string_value(country_code), COUNTRY_CODE_MAX);
        target->countries_array[i].n_cities = json_integer_value(cities);
        target->countries_array[i].n_locations = json_integer_value(locations);
    }
    
    json_decref(root);
}