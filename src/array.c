#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readCSV.h"
#include "array.h"
#include "compare.h"

#define MAX_STRING_LEN (128+8)

// creates dynamic array
array_t *arrayCreate(size_t size) {
    array_t *arr = malloc(sizeof(*arr));
    assert(arr);
    arr->size = size;
    arr->data = malloc(size * sizeof(*(arr->data)));
    assert(arr->data);
    arr->n = 0;
    return arr;
}

simple_array_t *simpleCreate(size_t size) {
    simple_array_t *arr = malloc(sizeof(*arr));
    assert(arr);
    arr->size = size;
    arr->data = malloc(size * sizeof(*(arr->data)));
    assert(arr->data);
    arr->n = 0;
    return arr;
}

void simpleFree(simple_array_t *arr) {
    free(arr->data);
    free(arr);
}

// frees array
void arrayFree(array_t *arr) {
    free(arr->data);
    free(arr);
}

// shifts elements at pivot point one to the right
void shiftElements(array_t *arr, int pivot) {
    for (int i = arr->n-1; i > pivot; i--) {
        arr->data[i] = arr->data[i-1];
    }
}

// compares two strings
// returns 1 if first string lower
// returns 2 if second string lower
// returns 0 if the same string
int compare(char *string1, char *string2) {
    int length = strlen(string1);
    for (int i = 0; i < length; i++) {
        if (string1[i] < string2[i]) {
            return 1;
        }
        if (string2[i] < string1[i]) {
            return 2;
        }
    }
    return 0;
}
// returns 0 if isnt prefix, returns 1 if it is
int hasPrefix(char *prefix, char *string, int *count) {
    int length = strlen(prefix);

    for (int i = 0; i < length; i++) {
        if (prefix[i] < string[i]) {
            (*count)++;
            return 1;
        }
        if (prefix[i] > string[i]) {
            (*count)++;
            return 2;
        }
        else {
            (*count)++;
            }
            continue;
    }
    return 0;
}

// insertion sort in ascending trading_names order
void insert(array_t *arr, data_t *data) {

    char *trading_name1 = data->trading_name.data;

    if (arr->n == 0) {
        arr->data[0] = data;
        (arr->n)++;
    }

    else {
        int isEnd = 0;
        int insertionIndex = 0;

        for (int i = 0; i < arr->n; i++) {
            char *trading_name2 = arr->data[i]->trading_name.data;
            int result = compare(trading_name1, trading_name2);
            
           if (result == 1 || result == 0) {
                insertionIndex = i;
                isEnd = 1;
                break;
           }
           continue;
        }
        // inserts elem at the correct index
        if (isEnd != 0) {
            (arr->n)++;
            shiftElements(arr, insertionIndex);
            arr->data[insertionIndex] = data;
        }
        // else, appends data point to end of array
        else {
            (arr->n)++;
            arr->data[arr->n-1] = data;
        }

    }

}

// binary search
int find_and_traverse(array_t *arr, char *key, int *string_count, int *char_count) {
    int low = 0;
    int high = arr->n-1;
    *string_count = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (compare(key, arr->data[mid]->trading_name.data) == 0) {

            return mid;
        }
        if (compare(key, arr->data[mid]->trading_name.data) == 2) {
            low = mid + 1;
            compare_by_char(key, arr->data[mid]->trading_name.data, char_count);
            (*string_count)++;
        }
        else {
            high = mid - 1;
            compare_by_char(key, arr->data[mid]->trading_name.data, char_count);
            (*string_count)++;
        }
    }
    return -1;
}
void linearSearch(FILE *output, array_t *arr, int index, char *key, int *string_count, int *char_count) {
    if (arr->n == 1) {
        compare_by_char(key, arr->data[index]->trading_name.data, char_count);
        (*string_count)++;
        print_data(arr->data[index], output);
    }
    else {
        for (int i = index; i < arr->n; i++) {
            if (compare_by_char(key, arr->data[i]->trading_name.data, char_count) != 0) {
                (*string_count)++;
                break;
            }
            (*string_count)++;
            print_data(arr->data[i], output);
        }
        for (int j = index-1; j >= 0; j--) {
            if (compare_by_char(key, arr->data[j]->trading_name.data, char_count) != 0) {
                (*string_count)++;
                break;
            }
            (*string_count)++;
            print_data(arr->data[j], output);
        }
    
    }
}

