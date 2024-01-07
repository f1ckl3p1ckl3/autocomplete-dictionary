#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readCSV.h"
#include "array.h"

#ifndef _TREE_H_

#define _TREE_H_

typedef struct bit_array bit_array_t;

struct bit_array {
    size_t len;
    char data[MAX_STRING_LEN];
};

typedef struct duplicates duplicate_t;

struct duplicates {
    data_t **data;
    int size;
    int n;
};

typedef struct tree tree_t;

struct tree {
    bit_array_t prefix;
    data_t *data;
    struct tree *branchA; // common prefix is 0
    struct tree *branchB; // common prefix is 1
    duplicate_t *duplicates;
};

void free_duplicates(duplicate_t *duplicates);
void free_tree(tree_t *tree);
duplicate_t *create_duplicate();
void array_append(duplicate_t *duplicates, data_t *data);
tree_t *new_node(data_t *data);
bool bit_checker(bit_array_t *original_prefix, bit_array_t *inserted);
bit_array_t get_remainder(bit_array_t *prefix, bit_array_t *inserted);
tree_t *insert_into_tree(tree_t *parent, data_t *data);
tree_t *split(bit_array_t *a, bit_array_t *b, tree_t *node);
bool get_bit(bit_array_t *arr, size_t i);
void set_bit(bit_array_t *arr, size_t i, bool b);
bit_array_t get_common_prefix(bit_array_t *a, bit_array_t *b);
void print_bit_array(bit_array_t *arr);
bit_array_t create_bit_array(size_t i, char *string);
void print_tree(tree_t *node);
#endif
