#include <stdio.h>
#include <string.h>

#include "io.h"
#include "date_util.h"

// returns mode for use with fopen() - "c" if user cancels / enters invalid response.
static const char *get_mode(const char *filename)
{
    char response;
    FILE *fp;
    
    if ((fp = fopen(filename, "r")) != NULL)
    {
        fclose(fp);
        printf("File %s exists. (o)verwrite, (a)ppend, or (c)ancel?\n  (o, a, c) > ", filename);
        response = getchar();
        switch (response)
        {
            case 'o':
                return "w";
            
            case 'a':
                return "a";
            
            case 'c':
                return "c";
            
            default:
                printf("Input not recognised, cancelling.\n");
                return "c";
        }
    }

    // file does not exist
    return "w";   
}

static void print_country(country_t *source)
{
    printf("    * Name:\t\t%s\n", source->name);
    printf("    * Code:\t\t%s\n", source->country_code);
    printf("    * # of cities:\t%d\n", source->n_cities);
    printf("    * # of locations:\t%d\n\n", source->n_locations);
}

static void print_city(city_t *source)
{
    printf("    * Name:\t\t%s\n", source->name);
    printf("    * Country code:\t%s\n", source->country_code);
    printf("    * # of locations:\t%d\n\n", source->n_locations);
}

static void print_location(location_t *source)
{
    printf("    * Name:\t\t\t%s\n", source->name);
    printf("    * City:\t\t\t%s\n", source->city);
    printf("    * Country code:\t\t%s\n", source->country_code);
    printf("    * Latitude:\t\t\t%f\n", source->latitude);
    printf("    * Longitude:\t\t%f\n", source->longitude);
    printf("    * Available parameters:\n        ");
    for (parameter_t param = PARAM_PM25; param < N_PARAMETERS; param++)
    {
        if(source->parameters[param] == 1)
            printf("%s ", parameter_names[param]);
    }
    printf("\n\n"); 
}

static inline void print_value(const char *measurement, float value, const char *unit, time_t timestamp)
{
    char date[DATE_MAX];
    timestamp_to_string(date, timestamp);
    printf("%s: \t\t\t%.3f %s\t (%sUTC, timestamp: %ld)\n", measurement, value, unit, date, timestamp);
}

static void print_measurement(measurement_t *measurement)
{
    const char *labels[N_PARAMETERS] = {
        "    * PM25",
        "    * PM10",
        "    * O3",
        "    * SO2",
        "    * NO2",
        "    * CO",
        "    * BC"
    };

    printf("    * Country: \t\t\t%s\n", measurement->country_code);
    printf("    * City: \t\t\t%s\n", measurement->city);
    printf("    * Location: \t\t%s\n", measurement->location);
    printf("    * Latitude:\t\t\t%f\n", measurement->latitude);
    printf("    * Longitude:\t\t%f\n", measurement->longitude);
    for (parameter_t param = PARAM_PM25; param < N_PARAMETERS; param++)    
    {
        if (measurement->substances[param].value != -1)
        {
            print_value(labels[param], 
                        measurement->substances[param].value,
                        measurement->substances[param].unit,
                        measurement->substances[param].timestamp);
        }
    }   
    printf("\n");
}

static void write_city(city_t *source, FILE *fp)
{
    fprintf(fp, "%s,%s,%d\n",
                source->country_code,
                source->name,
                source->n_locations);   
}

static void write_country(country_t *source, FILE *fp)
{
    fprintf(fp, "%s,%s,%d,%d\n",
                source->name,
                source->country_code,
                source->n_cities,
                source->n_locations);   
}

static void write_location(location_t *source, FILE *fp)
{
    fprintf(fp, "%s,%s,%s,%f,%f");
    for (parameter_t param = PARAM_PM25; param < N_PARAMETERS; param++)
    {
        fprintf(fp, ",%d", source->parameters[param] == 1 ? 1 : 0);
    }
    fprintf(fp, "\n"); 
}

static void write_measurement(measurement_t *measurement, FILE *fp)
{
    fprintf(fp, "%s,%s,%s,%f,%f", measurement->country_code,
                                  measurement->city,
                                  measurement->location,
                                  measurement->latitude,
                                  measurement->longitude);
    for (parameter_t param = PARAM_PM25; param < N_PARAMETERS; param++)    {
        fprintf(fp, ",%f,%s,%ld", measurement->substances[param].value,
                                  measurement->substances[param].unit,
                                  measurement->substances[param].timestamp); 
    }
    fprintf(fp, "\n");
}

void print_countries(countries_t *source)
{
    if(source->size == 0)
        puts("No countries found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_country(source->countries_array + i);
    }
}

void print_cities(cities_t *source)
{
    if(source->size == 0)
        puts("No cities found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_city(source->cities_array + i);
    }
}

void print_locations(locations_t *source)
{
    if(source->size == 0)
        puts("No locations found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("[+] Record #%d\n\n", i + 1);
        print_location(source->locations_array + i);
    }
}

void print_measurements(measurements_t *source)
{
    if(source->size == 0)
    {
        printf("No measurements found.\n");
        return;
    }

    for (int i = 0; i < source->size; i++)
    {   
        printf("[+] Record #%d\n", i + 1);
        if (source->measurements_array[i].valid_data == 1)
        {
            printf("\n");
            print_measurement(source->measurements_array + i);
        }
        else
        {
            printf("    * Invalid data.\n\n");
        }
        
    }
}

int write_countries(countries_t *source, const char *filename)
{
    int lines = 0;
    const char *mode = get_mode(filename);

    FILE *fp;
    
    if(source->size == 0)
    {
        printf("No countries found.\n");
        return 0;
    }
    
    if ((fp = fopen(filename, mode)) == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return 0;
    }
    else
    {
        // if file does not exist, or if user chooses to overwrite it, write column names first
        if (strcmp(mode, "w") == 0)
            fprintf(fp, "name,country_code,n_cities,n_locations\n");

        for (int i = 0; i < source->size; i++)
        {
            write_country(source->countries_array + i, fp);
            lines = lines + 1;
        }
        fclose(fp);
    }
    
    return lines;
}

int write_cities(cities_t *source, const char *filename)
{
    int lines = 0;
    const char *mode = get_mode(filename);
    
    FILE *fp;
        
    if(source->size == 0)
    {
        printf("No cities found.\n");
        return 0;
    }
    
    if ((fp = fopen(filename, mode)) == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return 0;
    }
    else
    {
        // if file does not exist, or if user chooses to overwrite it, write column names first
        if (strcmp(mode, "w") == 0)
            fprintf(fp, "country_code,city,n_locations\n");

        for (int i = 0; i < source->size; i++)
        {
            write_city(source->cities_array + i, fp);
            lines = lines + 1;
        }
        fclose(fp);
    }

    return lines;
}

int write_locations(locations_t *source, const char *filename)
{
    int lines = 0;
    const char *mode = get_mode(filename);

    FILE *fp;    
    
    if(source->size == 0)
    {
        printf("No locations found.\n");
        return 0;
    }
    
    if ((fp = fopen(filename, mode)) == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return 0;
    }
    else
    {
        // if file does not exist, or if user chooses to overwrite it, write column names first
        if (strcmp(mode, "w") == 0)
            fprintf(fp, "country_code,city,location,latitude,longitude,pm25,pm10,o3,so2,no2,co,bc\n");

        for (int i = 0; i < source->size; i++)
        {
            write_location(source->locations_array + i, fp);
            lines = lines + 1;
        }
        fclose(fp);
    }
    
    return lines;
}

int write_measurements(measurements_t *source, const char *filename)
{
    int lines = 0;
    const char *mode = get_mode(filename);
    FILE *fp;
    
    if(source->size == 0)
    {
        printf("No measurements found.\n");
        return 0;
    }
    
    if ((fp = fopen(filename, mode)) == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return 0;
    }
    else
    {
        // if file does not exist, or if user chooses to overwrite it, write column names first
        if (strcmp(mode, "w") == 0)
        {
            fprintf(fp, "country_code,city,location,latitude,longitude");
            for (parameter_t param = PARAM_PM25; param < N_PARAMETERS; param++)
            {
                fprintf(fp, ",%s,%s%s,%s%s", parameter_names[param],
                                             parameter_names[param], "_unit",
                                             parameter_names[param], "_timestamp");
            }
            fprintf(fp, "\n");
        }
        for (int i = 0; i < source->size; i++)
        {
            if (source->measurements_array[i].valid_data == 1)
            {
                write_measurement(source->measurements_array + i, fp);
                lines = lines + 1;
            }
        }
        fclose(fp);
    }

    return lines;
}