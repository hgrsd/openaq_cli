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
    if (source->has_pm25 == 1)
        printf("PM25 ");
    if (source->has_pm10 == 1)
        printf("PM10 ");
    if (source->has_bc == 1)
        printf("BC ");
    if (source->has_no2 == 1)
        printf("NO2 ");
    if (source->has_so2 == 1)
        printf("SO2 ");
    if (source->has_o3 == 1)
        printf("O3 ");
    if (source->has_co == 1)
        printf("CO ");
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
    for (int i = 0; i < N_PARAMETERS; i++)
    {
        if (measurement->substances[i].value != -1)
        {
            print_value(labels[i], 
                        measurement->substances[i].value,
                        measurement->substances[i].unit,
                        measurement->substances[i].timestamp);
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
    fprintf(fp, "%s,%s,%s,%f,%f,%d,%d,%d,%d,%d,%d,%d\n",
                source->country_code,
                source->city,
                source->name,
                source->latitude,
                source->longitude,
                source->has_pm25,
                source->has_pm10,
                source->has_o3,
                source->has_so2,
                source->has_no2,
                source->has_co,
                source->has_bc);   
}

static void write_measurement(measurement_t *measurement, FILE *fp)
{
    fprintf(fp, "%s,%s,%s,%f,%f", measurement->country_code,
                                  measurement->city,
                                  measurement->location,
                                  measurement->latitude,
                                  measurement->longitude);
    for (int i = 0; i < N_PARAMETERS; i++)
    {
        fprintf(fp, ",%f,%s,%ld", measurement->substances[i].value,
                                  measurement->substances[i].unit,
                                  measurement->substances[i].timestamp); 
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
        printf("[+] Record #%d\n\n", i + 1);
        print_measurement(source->measurements_array + i);
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
            for (int i = 0; i < N_PARAMETERS; i++)
            {
                fprintf(fp, ",%s,%s%s,%s%s", parameter_names[i],
                                         parameter_names[i], "_unit",
                                         parameter_names[i], "_timestamp");
            }
            fprintf(fp, "\n");
        }
        for (int i = 0; i < source->size; i++)
        {
            if (strcmp(source->measurements_array[i].location, "\0") != 0)
            {
                write_measurement(source->measurements_array + i, fp);
                lines = lines + 1;
            }
        }
        fclose(fp);
    }

    return lines;
}