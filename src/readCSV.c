#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readCSV.h"
#include "slicing.h"

#define MAX_LINE_LEN (512+8)
#define MAX_STRING_LEN (128+8)


// initialises data fields of struct
void initialise_data(data_t *data, int tracker, slice_t slice) {
    fixed_string_t buffer = {0};
    switch(tracker)
    {
        case 0:
            data->census_year = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->census_year = strtol(buffer.data, NULL, 0);
            buffer = (fixed_string_t) {0};
        break;
        case 1:
            data->block_id = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->block_id = strtol(buffer.data, NULL, 0);
            buffer = (fixed_string_t) {0};
            break;
        case 2:
            data->property_id = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->property_id = strtol(buffer.data, NULL, 0);
            buffer = (fixed_string_t) {0};
            break;
        case 3:
            data->base_property_id = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->base_property_id = strtol(buffer.data, NULL, 0);
            buffer = (fixed_string_t) {0};
            break;
        case 4:
            nullify_array(data->building_address.data);
            strncpy(data->building_address.data, slice.data, slice.size);
            break;
        case 5:
            nullify_array(data->clue_small_area.data);
            strncpy(data->clue_small_area.data, slice.data, slice.size);
            break;
        case 6:
            nullify_array(data->business_address.data);
            strncpy(data->business_address.data, slice.data, slice.size);
            break;
        case 7:
            nullify_array(data->trading_name.data);
            strncpy(data->trading_name.data, slice.data, slice.size);
            break;
        case 8:
            data->industry_code = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->industry_code = strtol(buffer.data, NULL, 0);
            buffer = (fixed_string_t) {0};
            break;
        case 9:
            nullify_array(data->industry_description.data);
            strncpy(data->industry_description.data, slice.data, slice.size);
            break;
        case 10:
            nullify_array(data->seating_type.data);
            strncpy(data->seating_type.data, slice.data, slice.size);
            break;
        case 11:
            data->number_of_seats = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->number_of_seats = strtol(buffer.data, NULL, 0);
            buffer = (fixed_string_t) {0};
            break;
        case 12:
            data->longitude = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->longitude = strtod(buffer.data, NULL);
            buffer = (fixed_string_t) {0};
            break;
        case 13:
            data->latitude = 0;
            strncpy(buffer.data, slice.data, slice.size);
            data->latitude = strtod(buffer.data, NULL);
            buffer = (fixed_string_t) {0};
            break;
    }  

}

// creates an empty string array
void nullify_array(char *array) {
    for (int i = 0; i < MAX_STRING_LEN; i++) {
        array[i] = '\0';
    }
}

// prints data to specified file output
void print_data(data_t *data, FILE *output) {
    fprintf(output, "--> census_year: %d || block_id: %d || property_id: %d || base_property_id: %d || building_address: %s || clue_small_area: %s || business_address: %s || trading_name: %s || industry_code: %d || industry_description: %s || seating_type: %s || number_of_seats: %d || longitude: %0.5f || latitude: %0.5f || \n", data->census_year, data->block_id, 
data->property_id, data->base_property_id, data->building_address.data, data->clue_small_area.data, data->business_address.data,
data->trading_name.data, data->industry_code, data->industry_description.data, data->seating_type.data, data->number_of_seats,
data->longitude, data->latitude);
}
