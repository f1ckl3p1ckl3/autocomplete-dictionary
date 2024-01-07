#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "readCSV.h"
#include "array.h"
#include "tree.h"
#include "compare.h"

#define MAX_STRING_LEN (128+8)

duplicate_t *create_duplicate() {
    duplicate_t *arr = malloc(sizeof(*arr));
    assert(arr);
    int size = MAX_STRING_LEN;      // "size" used for convenience
	arr->size = size;
	arr->data = malloc(size * sizeof(*(arr->data)));
	assert(arr->data);
	arr->n = 0;
	return arr;
}

void array_append(duplicate_t *duplicates, data_t *data) {
    if (duplicates->size == duplicates->n) {
        duplicates->size *= 2;
        duplicates->data = realloc(duplicates->data, duplicates->size * sizeof(*(duplicates->data)));
    }
    if (duplicates->data == NULL) {
        duplicates->size /= 2;
    }
    else {
        duplicates->data[duplicates->n] = data;
        (duplicates->n)++;
    }
}

// create bit array from predefined values
bit_array_t create_bit_array(size_t i, char *string) {
    bit_array_t bits = {0};
    bits.len = i*BITS_PER_BYTE;
    for (int n = 0; n < i; n++) {
        bits.data[n] = string[n];
    }
    return bits;
}

// finds the value of bit at an index of byte
bool get_bit(bit_array_t *arr, size_t i) {
    size_t byte = i / BITS_PER_BYTE;
    size_t bit = BITS_PER_BYTE - 1 - (i % BITS_PER_BYTE);
    return (arr->data[byte] >> bit) & 1;
}

bool bit_checker(bit_array_t *original_prefix, bit_array_t *inserted) {
    for (int i = 0; i < original_prefix->len; i++) {
        if (original_prefix->data[i]!=inserted->data[i]) {
            return false;
        }
    }
    return true;
}

// sets bit of bit array to either 0 or 1
void set_bit(bit_array_t *arr, size_t i, bool b) {
    size_t byte = i / BITS_PER_BYTE;
    size_t bit = BITS_PER_BYTE - 1 - (i % BITS_PER_BYTE);
    if (b) {
        arr->data[byte] |= 1 << bit;
    }
    else {
        arr->data[byte] &= ~((unsigned int) 1 << bit);
    }
}

// prints bit array
void print_bit_array(bit_array_t *arr) {
    for (size_t i = 0; i < arr->len; i++) {
        printf("%d", get_bit(arr, i));
        if (i % BITS_PER_BYTE == 7) {
            printf(" ");
        }
    }
    printf("\n");
}

// finds common bit prefix
bit_array_t get_common_prefix(bit_array_t *a, bit_array_t *b) {
    size_t n;
    for (n = 0; n < a->len && n < b->len; ++n) {
        if (get_bit(a, n) != get_bit(b, n)) {
            break;
        }
    }
    bit_array_t prefix = {0};
    for (size_t i = 0; i < n; i++) {
        bool x = get_bit(a, i);
        set_bit(&prefix, i, x);
        prefix.len += 1;
    }
    return prefix;
}

bit_array_t get_remainder(bit_array_t *prefix, bit_array_t *inserted) {
    size_t n;
    for (n = 0; n < prefix->len && n < inserted->len; ++n) {
        if (get_bit(prefix, n) != get_bit(inserted, n)) {
            break;
        }
    }
    
    bit_array_t remainder = {0};

    for (int i = n; i < inserted->len; i++) {
        bool x = get_bit(inserted, i-n);
        set_bit(&remainder, i, x);
        remainder.len += 1;
    }
    return remainder;
}

// creates new node of radix tree
tree_t *new_node(data_t *data) {
    tree_t *temp = malloc(sizeof(tree_t));
    temp->data = data;
    temp->prefix = create_bit_array(strlen(data->trading_name.data), data->trading_name.data);
    temp->branchA = temp->branchB = NULL;
    temp->duplicates = create_duplicate();
    return temp;
}
void free_duplicates(duplicate_t *duplicates) {
        free(duplicates->data);
        free(duplicates);
}
void free_tree(tree_t *tree) {
    if (tree != NULL) {
        free_tree(tree->branchA);
        free(tree->data);
        free_duplicates(tree->duplicates);
        free_tree(tree->branchB);
        free(tree);
    }
}

tree_t *split(bit_array_t *a, bit_array_t *b, tree_t *node) {
    return node;
}

tree_t *insert_into_tree(tree_t *root, data_t *data) {
    tree_t *new = new_node(data);
    tree_t *curr = root;
    tree_t *prev = NULL;
    bit_array_t more_prefix = get_common_prefix(&curr->prefix, &new->prefix);
    bit_array_t remainder = get_remainder(&curr->prefix, &new->prefix);

    // printf("remainder: ");
    // print_bit_array(&remainder);

    while (curr != NULL) {
        prev = curr;
        if (more_prefix.len != curr->prefix.len) {
            if (get_bit(&remainder, 0)) {
                bit_array_t spare_prefix = more_prefix;
                bit_array_t spare_remainder = remainder;
                curr = curr->branchA;


                more_prefix = get_common_prefix(&spare_prefix, &spare_remainder);
                remainder = get_remainder(&spare_prefix, &spare_remainder);
            }
            else {
                bit_array_t spare_prefix = more_prefix;
                bit_array_t spare_remainder = remainder;
                curr = curr->branchB;
                more_prefix = get_common_prefix(&spare_prefix, &spare_remainder);
                remainder = get_remainder(&spare_prefix, &spare_remainder);
            }
        }
        else {
            array_append(curr->duplicates, data);
            break;
        }
    }
    prev->prefix = more_prefix;
    if (prev == NULL) {
        prev = new;
    }
    else if (get_bit(&remainder, 0)) {
        prev->prefix = remainder;
        prev->branchA = new;
    }
    else {
        prev->prefix = remainder;
        prev->branchB = new;
    }
    // printf("name inserted:");
    // print_bit_array(&prev->prefix);
    // printf("remainder: ");
    // print_bit_array(&remainder);
    //free_tree(new);
    return prev;
}

void print_tree(tree_t *node) {
    if (node != NULL) {
        print_tree(node->branchA);
        print_bit_array(&node->prefix);
        print_tree(node->branchB);
    }
}
