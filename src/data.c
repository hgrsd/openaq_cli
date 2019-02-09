#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"

static void print_measurement(char label[MEASUREMENT_LABEL_MAX], float value, char unit[UNIT_MAX])
{
    printf("%s: \t\t\t%.3f %s\n", label, value, unit);
}

void clear_data(response_data_t *data)
{
    free(data->data);
    data->data = malloc(1);
    data->size = 0;
}

void init_data(response_data_t *data)
{
    data->data = malloc(1);
    data->size = 0;
}

void init_measurements(measurements_t *target, int size)
{
    target->size = size;
    for (int i = 0; i < size; i++)
    {
        target->measurements_array[i].bc = -1;
        target->measurements_array[i].co = -1;
        target->measurements_array[i].no2 = -1;
        target->measurements_array[i].o3 = -1;
        target->measurements_array[i].pm10 = -1;
        target->measurements_array[i].pm25 = -1;
        target->measurements_array[i].so2 = -1;
    }
}

void print_measurements(measurements_t *source)
{
    if(source->size == 0)
        puts("No measurements found.");

    for (int i = 0; i < source->size; i++)
    {
        printf("Location: \t\t%s\n", source->measurements_array[i].location);
        printf("Date: \t\t\t%s\n", source->measurements_array[i].date);
        if (source->measurements_array[i].bc != -1)
            print_measurement("BC", source->measurements_array[i].bc, source->measurements_array[i].bc_unit);
        if (source->measurements_array[i].co != -1)
            print_measurement("CO", source->measurements_array[i].co, source->measurements_array[i].co_unit);
        if (source->measurements_array[i].no2 != -1)
            print_measurement("NO2", source->measurements_array[i].no2, source->measurements_array[i].no2_unit);
        if (source->measurements_array[i].o3 != -1)
            print_measurement("O3", source->measurements_array[i].o3, source->measurements_array[i].o3_unit);
        if (source->measurements_array[i].pm10 != -1)
            print_measurement("PM10", source->measurements_array[i].pm10, source->measurements_array[i].pm10_unit);
        if (source->measurements_array[i].pm25 != -1)
            print_measurement("PM25", source->measurements_array[i].pm25, source->measurements_array[i].pm25_unit);
        if (source->measurements_array[i].so2 != -1)
            print_measurement("SO2", source->measurements_array[i].so2, source->measurements_array[i].so2_unit);
        printf("\n");
    }
}

