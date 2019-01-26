#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "api_calls.h"
#include "data.h"



int main(void)
{
    struct response_data raw_data;

    init_data(&raw_data);
    
    fetch_cities("NL", &raw_data);
    json_extract_cities(raw_data.data);
    
    return 0;
}