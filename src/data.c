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
    target->size = 0;
    for (int i = 0; i < MAX_MEASUREMENTS; i++)
    {
        target->measurements_array[i].bc = -1;
        target->measurements_array[i].co = -1;
        target->measurements_array[i].no2 = -1;
        target->measurements_array[i].o3 = -1;
        target->measurements_array[i].pm10 = -1;
        target->measurements_array[i].pm25 = -1;
        target->measurements_array[i].so2 = -1;
        target->measurements_array[i].bc_unit[0] = '\0';
        target->measurements_array[i].co_unit[0] = '\0';
        target->measurements_array[i].no2_unit[0] = '\0';
        target->measurements_array[i].o3_unit[0] = '\0';
        target->measurements_array[i].pm10_unit[0] = '\0';
        target->measurements_array[i].pm25_unit[0] = '\0';
        target->measurements_array[i].so2_unit[0] = '\0';
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
            printf("\t  BC:\t\t%.3f %s\n", 
                    source->measurements_array[i].bc,
                    source->measurements_array[i].bc_unit);
        if (source->measurements_array[i].co != -1)
            printf("\t  CO:\t\t%.3f %s\n", 
                    source->measurements_array[i].co,
                    source->measurements_array[i].co_unit);
        if (source->measurements_array[i].no2 != -1)
            printf("\t  No2\t\t%.3f %s\n", 
                    source->measurements_array[i].no2, 
                    source->measurements_array[i].no2_unit);
        if (source->measurements_array[i].o3 != -1)
            printf("\t  o3:\t\t%.3f %s\n", 
                    source->measurements_array[i].o3, 
                    source->measurements_array[i].o3_unit);
        if (source->measurements_array[i].pm10 != -1)
            printf("\t  pm10:\t\t%.3f %s\n", 
                    source->measurements_array[i].pm10, 
                    source->measurements_array[i].pm10_unit);
        if (source->measurements_array[i].pm25 != -1)
            printf("\t  pm25:\t\t%.3f %s\n", 
                    source->measurements_array[i].pm25, 
                    source->measurements_array[i].pm25_unit);
        if (source->measurements_array[i].so2 != -1)
            printf("\t  so2\t\t%.3f %s\n\n", 
                    source->measurements_array[i].so2, 
                    source->measurements_array[i].so2_unit);
        printf("\n");
    }

}

