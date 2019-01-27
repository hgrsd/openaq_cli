#ifndef _DATA_H_
#define _DATA_H_

#define LOCATION_MAX 40
#define DATE_MAX 30
#define MAX_MEASUREMENTS 100

struct response_data
{
    char *data;
    int size;
};

struct measurement
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

struct measurements
{
    struct measurement measurements_array[MAX_MEASUREMENTS];
    int size;
};

void clear_data(struct response_data *data);
void init_data(struct response_data *data);
void init_measurements(struct measurements *target);
void print_measurements(struct measurements *source);

#endif
