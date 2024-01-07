#include <stdio.h>
#include <stdlib.h>
#include "readCSV.h"

#ifndef _ARRAY_H_

#define _ARRAY_H_


// dynamic array
typedef struct array array_t;
typedef struct simple simple_array_t;

struct array {
    data_t **data; // pointer to csv data fields
    int size; // size allocated to array
    int n; // number of elements in array
};

struct simple {
    fixed_string_t *data;
    int size;
    int n;
};

void simpleFree(simple_array_t *arr);
array_t *arrayCreate(size_t size);
simple_array_t *simpleCreate(size_t size);
void arrayFree(array_t *arr);
void shiftElements(array_t *arr, int pivot);
void insert(array_t *arr, data_t *data);
int compare(char *string1, char *string2);
int find_and_traverse(array_t *arr, char *key, int *string_count, int *char_count);
int hasPrefix(char *prefix, char *string, int *char_count);
void linearSearch(FILE *output, array_t *arr, int index, char *key, int *string_count, int *char_count);

#endif
