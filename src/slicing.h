#include <stdio.h>
#include <stdlib.h>



#ifndef _SLICING_H

#define _SLICING_H


typedef struct file {
    size_t size;
    char *cake;
} file_t;

typedef struct slice {
    size_t size; // length
    char *data; //ptr to start

} slice_t;

typedef struct file file_t;

struct slice find_subslice(char *cake, size_t size, char split_condition);
size_t find_cake_size(const char *filepath);
char *create_cake(const char *filepath, size_t size);
struct slice left_slice(char *cake, size_t size, char split_condition);
struct slice right_slice(char *cake, size_t size, char split_condition);
int find_first_occurence(char *cake, size_t size, char split_condition);
int find_total_occurences(char *cake, size_t size, char split_condition);
int is_quote(char *cake);
struct slice find_data(char *cake, size_t size);
struct slice find_remainder(char *cake, size_t size);

#endif
