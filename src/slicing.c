#include <stdio.h>
#include <stdlib.h>
#include "slicing.h"
#include <assert.h>


// finds total size of file
size_t find_cake_size(const char *filepath) {
    FILE *f = fopen(filepath, "r");

    fseek(f, 0L, SEEK_END);

    long int size = ftell(f);
    fclose(f);

    return size;
}

// creates array from file input
char *create_cake(const char *filepath, size_t size) {
    FILE *f = NULL;
    char *buffer = NULL;

    f = fopen(filepath, "r");

    buffer = malloc(size*sizeof(char) + 1);
    assert(buffer!= NULL);

    fread(buffer, 1, size, f);
    if (buffer[size-1] == '\n') {
        buffer[size-1] = '\0';
    }
    else {
        buffer[size] = '\0';
    }

    fclose(f);

    return buffer;
}

// finds first occurence of char specified
int find_first_occurence(char *cake, size_t size, char split_condition) {
    int i;
    for (i = 0; i < size; i++) {
        if (cake[i] == split_condition) {
            return i;
        }
    }
    return -1;
}

// finds total occurences of char specified
int find_total_occurences(char *cake, size_t size, char split_condition) {
    int i, count = 0;
    for (i = 0; i < size; i++) {
        if (cake[i] == split_condition){
            count+=1;
        }
    }
    return count;
}

// slices file array when first instance of character specified is found...
// returns new array to the left side of character (excluding character)
struct slice left_slice(char *cake, size_t size, char split_condition) {
    int i;
    slice_t s = {.size = 0, .data = NULL};

    for (i = 0; i < size; i++) {
        if (cake[i] == split_condition) {
            s.size = i;
            break;
        }
    }   
    s.data = &cake[0];
    return s;
}

// slices file array when first instance of character specified is found... 
// returns new array to the right side of character (excluding character)
struct slice right_slice(char *cake, size_t size, char split_condition) {
    int i;
    slice_t s = {.size = 0, .data = NULL};

    for (i = 0; i < size; i++) {
        if (cake[i] == split_condition){
            s.size = size-(i+1);
            break;
        }
    }
    s.data = &cake[i+1];
    return s;
}

// finds subslice from buffer input
struct slice find_subslice(char *cake, size_t size, char split_condition) {
    int i;
    slice_t s = {.size = 0, .data = NULL};
    int isFirst = 0;
    int size_tracker = 0;
    for (i = 0; i < size; i++) {
        if (cake[i] == split_condition && isFirst == 0) {
            s.data = &cake[i+1];
            isFirst = 1;
            continue;
        }
        if (isFirst == 1) {
            size_tracker += 1;
        }
        if (cake[i] == split_condition && isFirst == 1) {
            s.size = size_tracker-1;
            break;
        }
    }
    return s;
}

// readjusts slice depending on start values of cake
struct slice find_data(char *cake, size_t size) {
    slice_t s = {.size = 0, .data = NULL};
    if (cake[0] == '"') {
        s.data = &cake[1];
        for (int i = 1; i < size; i++) {
            if (cake[i] == '"') {
                s.size = i-1;
                break;
            }
        }
        return s;
    }
    else {
        s.data = &cake[0];
        for (int i = 0; i < size; i++) {
            if (cake[i] == '\n') {
                s.size = i;
                break;
            }
            else if (cake[i] == ',') {
                s.size = i;
                break;
            }
            else if (cake[i] == '\0') {
                s.size = i;
                break;
            }
        }
        return s;
    }
    return s;
}

// readjusts slice depending on start conditions of cake
struct slice find_remainder(char *cake, size_t size) {
    slice_t s = {.size = 0, .data = NULL};
    if (cake[0] == '\n' && cake[1] == '"' && cake[2] == ',') {
        s.data = &cake[3];
        s.size = size-3;
    }
    else if (cake[0] == '\n' && cake[1] == ',') {
        s.data = &cake[2];
        s.size = size-2;
    }
    else if (cake[0] == '"' && cake[1] == ',') {
        s.data = &cake[2];
        s.size = size - 2;
    }
    else if (cake[0] == ',') {
        s.data = &cake[1];
        s.size = size-1;
    }
    else {
        s.data = &cake[0];
        s.size = size;
    }
    return s;
}
// boolean for whether currently in quote
int is_quote(char *cake) {
    if (cake[0] == '"') {
        return 1;
    }
    return 0;
}