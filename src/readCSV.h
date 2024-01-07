#include <stdio.h>
#include <stdlib.h>
#include "slicing.h"

#ifndef _READCSV_H

#define _READCSV_H

#define MAX_LINE_LEN (512+8)
#define MAX_STRING_LEN (128+8)

struct fixed_string {
    char data[MAX_STRING_LEN];
};

typedef struct fixed_string fixed_string_t;


struct data {
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    fixed_string_t building_address;
    fixed_string_t clue_small_area;
    fixed_string_t business_address;
    fixed_string_t trading_name;
    int industry_code;
    fixed_string_t industry_description;
    fixed_string_t seating_type;
    int number_of_seats;
    double longitude;
    double latitude;
};

typedef struct data data_t;

void nullify_array(char *array);
void initialise_data(data_t *data, int tracker, slice_t slice);
void print_data(data_t *data, FILE *output);
void data_free(data_t *d);
void free_fixed_string(fixed_string_t *s);

#endif
