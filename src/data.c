#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"

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

void init_measurements(measurements_t *target)
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

void print_measurements(measurements_t *source)
{
    for (int i = 0; i < source->size; i++)
    {
        printf("\nLocation: \t\t%s\n", source->measurements_array[i].location);
        printf("Date: \t\t\t%s\n", source->measurements_array[i].date);
        printf("Values:\n");
        if (source->measurements_array[i].bc != -1)
            printf("\t\t\tBC: %.2f\n", source->measurements_array[i].bc);
        if (source->measurements_array[i].co != -1)
            printf("\t\t\tCO: %.2f\n", source->measurements_array[i].co);
        if (source->measurements_array[i].no2 != -1)
            printf("\t\t\tNo2: %.2f\n", source->measurements_array[i].no2);
        if (source->measurements_array[i].o3 != -1)
            printf("\t\t\to3: %.2f\n", source->measurements_array[i].o3);
        if (source->measurements_array[i].pm10 != -1)
            printf("\t\t\tpm10: %.2f\n", source->measurements_array[i].pm10);
        if (source->measurements_array[i].pm25 != -1)
            printf("\t\t\tpm25: %.2f\n", source->measurements_array[i].pm25);
        if (source->measurements_array[i].so2 != -1)
            printf("\t\t\tso2: %.2f\n\n", source->measurements_array[i].so2);
    }
}

