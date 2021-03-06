#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "tests.h"

#include <core.h>
#include <data.h>
#include <json.h>

/*
TODO: Add test for json_extract_measurements_range()
*/

void TEST_data_find_highest(void)
{
    measurement_t *highest;
    measurements_t measurements_data = {NULL, 0};

    printf("[+] Testing find_highest()\n");

    json_extract_latest(JSON_LATEST_TEST, &measurements_data);

    highest = find_highest(&measurements_data, string_to_param("pm25"));
    assert(highest->substances[PARAM_PM25].value == 70);
    
    highest = find_highest(&measurements_data, string_to_param("bc"));
    assert(highest == NULL);

    json_extract_latest(JSON_LATEST_TEST_EMPTY, &measurements_data);
    highest = find_highest(&measurements_data, string_to_param("co"));
    assert(highest->substances[PARAM_CO].value == 2);

    json_extract_latest(JSON_LATEST_TEST_MALFORMED, &measurements_data);
    highest = find_highest(&measurements_data, string_to_param("pm25"));
    assert(highest == NULL);

    printf("    [PASS]\n\n");
}

void TEST_json_extract_cities(void)
{
    cities_t cities_data = {NULL, 0};

    printf("[+] Testing json_extract_cities()\n");
    
    json_extract_cities(JSON_CITIES_TEST, &cities_data);
    assert(cities_data.size == 5);
    assert(strcmp(cities_data.cities_array[0].country_code, "GB") == 0);
    assert(cities_data.cities_array[1].n_locations == 1);
    assert(strcmp(cities_data.cities_array[2].name, "Eskdalemuir") == 0);
    assert(cities_data.cities_array[4].n_locations == 2);

    // malformed
    json_extract_cities(JSON_CITIES_TEST_MALFORMED, &cities_data);
    assert(cities_data.size == 0);

    printf("    [PASS]\n\n");
}

void TEST_json_extract_locations(void)
{
    locations_t locations_data = {NULL, 0};

    printf("[+] Testing json_extract_locations()\n");
    
    json_extract_locations(JSON_LOCATIONS_TEST, &locations_data);
    
    assert(locations_data.size == 5);
    assert(strcmp(locations_data.locations_array[0].name, " 淮河道") == 0);
    assert(strcmp(locations_data.locations_array[0].city, "天津市") == 0);
    assert(locations_data.locations_array[0].parameters[PARAM_O3] == 1);
    assert(locations_data.locations_array[0].parameters[PARAM_PM25] == 1);
    assert(locations_data.locations_array[0].parameters[PARAM_PM10] == 1);
    assert(locations_data.locations_array[0].parameters[PARAM_NO2] == 1);
    assert(locations_data.locations_array[0].parameters[PARAM_SO2] == 1);
    assert(locations_data.locations_array[0].parameters[PARAM_CO] == 1);
    assert(locations_data.locations_array[0].parameters[PARAM_BC] == 0);
    assert(strcmp(locations_data.locations_array[1].name, "(Folkungagatan tillfälligt avstängd)") == 0);
    assert(strcmp(locations_data.locations_array[1].country_code, "SE") == 0);
    assert(locations_data.locations_array[1].parameters[PARAM_PM25] == 0);
    assert(locations_data.locations_array[1].parameters[PARAM_CO] == 0);
    assert(locations_data.locations_array[1].parameters[PARAM_O3] == 0);
    assert(locations_data.locations_array[1].parameters[PARAM_SO2] == 0);
    assert(locations_data.locations_array[1].parameters[PARAM_BC] == 0);
    assert(locations_data.locations_array[1].parameters[PARAM_PM10] == 1);
    assert(locations_data.locations_array[1].parameters[PARAM_NO2] == 1);
    assert(locations_data.locations_array[4].latitude == 41.32247);
    assert(locations_data.locations_array[4].longitude == -95.93799);

    // malformed
    json_extract_locations(JSON_LOCATIONS_TEST_MALFORMED, &locations_data);
    assert(locations_data.size == 0);

    printf("    [PASS]\n\n");
}

void TEST_json_extract_countries(void)
{
    countries_t countries_data = {NULL, 0};
    
    printf("[+] Testing json_extract_countries()\n");

    json_extract_countries(JSON_COUNTRIES_TEST, &countries_data);
   
    assert(countries_data.size == 4);
    assert(strcmp(countries_data.countries_array[0].name, "Andorra") == 0);
    assert(strcmp(countries_data.countries_array[0].country_code, "AD") == 0);
    assert(countries_data.countries_array[0].n_cities == 2);
    assert(countries_data.countries_array[0].n_locations == 3);
    assert(strcmp(countries_data.countries_array[1].name, "Australia") == 0);
    assert(strcmp(countries_data.countries_array[1].country_code, "AU") == 0);
    assert(countries_data.countries_array[1].n_cities == 19);
    assert(countries_data.countries_array[1].n_locations == 104);
    assert(strcmp(countries_data.countries_array[3].name, "Bahrain") == 0);
    assert(strcmp(countries_data.countries_array[3].country_code, "BH") == 0);
    assert(countries_data.countries_array[3].n_cities == 1);
    assert(countries_data.countries_array[3].n_locations == 1);

    // malformed
    json_extract_countries(JSON_COUNTRIES_TEST_MALFORMED, &countries_data);
    assert(countries_data.size == 0);

    printf("    [PASS]\n\n");
}

void TEST_json_extract_latest(void)
{
    measurements_t measurements_data = {NULL, 0};

    printf("[+] Testing json_extract_latest()\n");

    json_extract_latest(JSON_LATEST_TEST, &measurements_data);

    assert(measurements_data.size == 5);
    assert(strcmp(measurements_data.measurements_array[0].location, " 淮河道") == 0);
    assert(strcmp(measurements_data.measurements_array[0].city, "天津市") == 0);
    assert(strcmp(measurements_data.measurements_array[0].country_code, "CN") == 0);
    assert(measurements_data.measurements_array[0].substances[PARAM_PM25].value == 70);
    assert(strcmp(measurements_data.measurements_array[0].substances[PARAM_PM25].unit, "µg/m³") == 0);
    assert(measurements_data.measurements_array[0].substances[PARAM_CO].value == 1300);
    assert(strcmp(measurements_data.measurements_array[0].substances[PARAM_CO].unit, "µg/m³") == 0);
    assert(measurements_data.measurements_array[0].substances[PARAM_BC].value == -1);
    assert(measurements_data.measurements_array[1].latitude == 0);
    assert(measurements_data.measurements_array[1].longitude == 0);
    assert(strcmp(measurements_data.measurements_array[2].location, "1-r khoroolol") == 0);
    assert(measurements_data.measurements_array[2].substances[PARAM_PM10].value == 103);
    assert(measurements_data.measurements_array[2].substances[PARAM_CO].value == -1);
    assert(strcmp(measurements_data.measurements_array[2].substances[PARAM_PM10].unit, "µg/m³") == 0);
    assert(measurements_data.measurements_array[2].latitude == 47.91798);
    assert(measurements_data.measurements_array[2].longitude == 106.84806);
    assert(strcmp(measurements_data.measurements_array[4].location, "16th and Whitmore") == 0);
    assert(measurements_data.measurements_array[4].substances[PARAM_O3].value == 0.016);
    assert(strcmp(measurements_data.measurements_array[4].substances[PARAM_O3].unit, "ppm") == 0);
    assert(measurements_data.measurements_array[4].substances[PARAM_PM25].value == -1);


    // malformed
    json_extract_latest(JSON_LATEST_TEST_MALFORMED, &measurements_data);
    assert(measurements_data.size == 0);

    // empty parameters
    json_extract_latest(JSON_LATEST_TEST_EMPTY, &measurements_data);
    assert(measurements_data.measurements_array[0].substances[PARAM_PM25].value == -1);
    assert(measurements_data.measurements_array[0].substances[PARAM_PM10].value == -1);
    assert(measurements_data.measurements_array[0].substances[PARAM_NO2].value == -1);
    assert(measurements_data.measurements_array[0].substances[PARAM_SO2].value == -1);
    assert(measurements_data.measurements_array[0].substances[PARAM_BC].value == -1);
    assert(measurements_data.measurements_array[0].substances[PARAM_O3].value == -1);
    assert(measurements_data.measurements_array[0].substances[PARAM_CO].value == -1);


    printf("    [PASS]\n\n");
}

void TEST_data_string_to_param(void)
{
    parameter_t return_value;

    printf("[+] Testing string_to_param()\n");

    return_value = string_to_param("pm25");
    assert(return_value == PARAM_PM25);
    return_value = string_to_param("pm10");
    assert(return_value == PARAM_PM10);
    return_value = string_to_param("no2");
    assert(return_value == PARAM_NO2);
    return_value = string_to_param("co");
    assert(return_value == PARAM_CO);
    return_value = string_to_param("bc");
    assert(return_value == PARAM_BC);
    return_value = string_to_param("o3");
    assert(return_value == PARAM_O3);
    return_value = string_to_param("so2");
    assert(return_value == PARAM_SO2);
    return_value = string_to_param("THISISWRONG");
    assert(return_value == PARAM_INVALID);  

    printf("    [PASS]\n\n");
}

void TEST_data_init_measurements(void)
{
    measurements_t measurements_data;
    measurements_data.measurements_array = (measurement_t *) malloc(sizeof(measurement_t) * 5);

    printf("[+] Testing init_measurements()\n");

    init_measurements(&measurements_data, 5);

    for (int i = 0; i < 5; i++)
    {
        assert(strcmp(measurements_data.measurements_array[i].location, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_BC].unit, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_CO].unit, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_NO2].unit, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_O3].unit, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_PM10].unit, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_PM25].unit, "\0") == 0);
        assert(strcmp(measurements_data.measurements_array[i].substances[PARAM_SO2].unit, "\0") == 0);
        assert(measurements_data.measurements_array[i].substances[PARAM_BC].value == -1);
        assert(measurements_data.measurements_array[i].substances[PARAM_CO].value == -1);
        assert(measurements_data.measurements_array[i].substances[PARAM_NO2].value == -1);
        assert(measurements_data.measurements_array[i].substances[PARAM_O3].value == -1);
        assert(measurements_data.measurements_array[i].substances[PARAM_PM10].value == -1);
        assert(measurements_data.measurements_array[i].substances[PARAM_PM25].value == -1);
        assert(measurements_data.measurements_array[i].substances[PARAM_SO2].value == -1);
    }

    printf("    [PASS]\n\n");

}

void TEST_data_init_locations()
{
    locations_t locations_data;
    locations_data.locations_array = (location_t *) malloc(sizeof(location_t) * 5); 

    printf("[+] Testing init_locations()\n");

    init_locations(&locations_data, 5);
    for(int i = 0; i < 5; i++)
    {
        assert(strcmp(locations_data.locations_array[i].name, "\0") == 0);
        assert(strcmp(locations_data.locations_array[i].country_code, "\0") == 0);
        for (parameter_t param; param < N_PARAMETERS; param++)
            assert(locations_data.locations_array[i].parameters[param] == 0);
    }
    printf("    [PASS]\n\n");
}

int main(void)
{   
    printf("\n> RUNNING OPENAQ_CLI TEST SUITE\n\n");
    TEST_data_string_to_param();
    TEST_data_init_measurements();
    TEST_data_init_locations();
    TEST_json_extract_cities();
    TEST_json_extract_locations();
    TEST_json_extract_countries();
    TEST_json_extract_latest();
    TEST_data_find_highest();   
}

