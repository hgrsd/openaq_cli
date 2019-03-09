#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "tests.h"

#include "../src/core.h"
#include "../src/data.h"
#include "../src/json.h"

void TEST_find_highest(void)
{
    measurement_t *highest;
    measurements_t measurements_data = {NULL, 0};

    printf("[+] Testing find_highest()\n");

    json_extract_measurements(JSON_LATEST_TEST, &measurements_data);

    highest = find_highest(&measurements_data, string_to_param("PM25"));
    assert(highest->pm25 == 70);
    
    highest = find_highest(&measurements_data, string_to_param("BC"));
    assert(highest == NULL);

    printf("    *** [PASSED]\n\n");
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

    printf("    *** [PASSED]\n\n");
}

void TEST_json_extract_locations(void)
{
    locations_t locations_data = {NULL, 0};

    printf("[+] Testing json_extract_locations()\n");
    
    json_extract_locations(JSON_LOCATIONS_TEST, &locations_data);
    
    assert(locations_data.size == 5);
    assert(strcmp(locations_data.locations_array[0].name, " 淮河道") == 0);
    assert(strcmp(locations_data.locations_array[0].city, "天津市") == 0);
    assert(locations_data.locations_array[0].has_o3 == 1);
    assert(locations_data.locations_array[0].has_pm25 == 1);
    assert(locations_data.locations_array[0].has_pm10 == 1);
    assert(locations_data.locations_array[0].has_no2 == 1);
    assert(locations_data.locations_array[0].has_so2 == 1);
    assert(locations_data.locations_array[0].has_co == 1);
    assert(locations_data.locations_array[0].has_bc == 0);
    assert(strcmp(locations_data.locations_array[1].name, "(Folkungagatan tillfälligt avstängd)") == 0);
    assert(strcmp(locations_data.locations_array[1].country_code, "SE") == 0);
    assert(locations_data.locations_array[1].has_pm25 == 0);
    assert(locations_data.locations_array[1].has_co == 0);
    assert(locations_data.locations_array[1].has_o3 == 0);
    assert(locations_data.locations_array[1].has_co == 0);
    assert(locations_data.locations_array[1].has_so2 == 0);
    assert(locations_data.locations_array[1].has_bc == 0);
    assert(locations_data.locations_array[1].has_pm10 == 1);
    assert(locations_data.locations_array[1].has_no2 == 1);
    assert(locations_data.locations_array[4].latitude == 41.32247);
    assert(locations_data.locations_array[4].longitude == -95.93799);

    // malformed
    json_extract_locations(JSON_LOCATIONS_TEST_MALFORMED, &locations_data);
    assert(locations_data.size == 0);


    
    printf("    *** [PASSED]\n\n");
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

    printf("    *** [PASSED]\n\n");
}

void TEST_json_extract_measurements(void)
{
    measurements_t measurements_data = {NULL, 0};

    printf("[+] Testing json_extract_measurements()\n");

    json_extract_measurements(JSON_LATEST_TEST, &measurements_data);

    assert(measurements_data.size == 5);
    assert(strcmp(measurements_data.measurements_array[0].location, " 淮河道") == 0);
    assert(measurements_data.measurements_array[0].pm25 == 70);
    assert(strcmp(measurements_data.measurements_array[0].pm25_unit, "µg/m³") == 0);
    assert(measurements_data.measurements_array[0].co == 1300);
    assert(strcmp(measurements_data.measurements_array[0].co_unit, "µg/m³") == 0);
    assert(measurements_data.measurements_array[0].bc == -1);
    assert(strcmp(measurements_data.measurements_array[2].location, "1-r khoroolol") == 0);
    assert(measurements_data.measurements_array[2].pm10 == 103);
    assert(strcmp(measurements_data.measurements_array[2].pm10_unit, "µg/m³") == 0);
    assert(measurements_data.measurements_array[2].latitude == 47.91798);
    assert(measurements_data.measurements_array[2].longitude == 106.84806);
    assert(strcmp(measurements_data.measurements_array[4].location, "16th and Whitmore") == 0);
    assert(measurements_data.measurements_array[4].o3 == 0.016);
    assert(strcmp(measurements_data.measurements_array[4].o3_unit, "ppm") == 0);
    assert(measurements_data.measurements_array[4].pm25 == -1);


    // malformed
    json_extract_measurements(JSON_LATEST_TEST_MALFORMED, &measurements_data);
    assert(measurements_data.size == 0);

    printf("    *** [PASSED]\n\n");
}


int main(void)
{
    TEST_json_extract_cities();
    TEST_json_extract_locations();
    TEST_json_extract_countries();
    TEST_json_extract_measurements();
    TEST_find_highest();
}

