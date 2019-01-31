#ifndef _DATA_H_
#define _DATA_H_

#define LOCATION_MAX 40
#define DATE_MAX 30
#define MAX_MEASUREMENTS 100

struct _response_data_t
{
    char *data;
    int size;
};
typedef struct _response_data_t response_data_t;

struct _measurement_t
{
    char location[LOCATION_MAX];
    char date[DATE_MAX];
    float pm25;
    float pm10;
    float o3;
    float so2;
    float no2;
    float co;
    float bc;
};
typedef struct _measurement_t measurement_t;

struct _measurements_t
{
    struct _measurement_t measurements_array[MAX_MEASUREMENTS];
    int size;
};
typedef struct _measurements_t measurements_t;

void clear_data(response_data_t *data);
void init_data(response_data_t *data);
void init_measurements(measurements_t *target);
void print_measurements(measurements_t *source);

#endif
