#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "slicing.h"
#include "readCSV.h"
#include "linkedList.h"
#include "array.h"
#include "compare.h"
#include "tree.h"


#define MAX_LINE_LEN (512+8) // add 8 bits for adding '\0' worst case
#define MAX_STRING_LEN (128+8) // add 8 bits for adding '\0' worst case
#define MAX_DATA_FIELDS 14


int main(int argc, char *argsv[]) {

    // output file
    FILE *output;
    output = fopen(argsv[3], "w");
 
    // input file
    char filepath[MAX_STRING_LEN];
    strcpy(filepath, argsv[2]);

    // finds size of file
    size_t size = find_cake_size(filepath);
    
    simple_array_t *prefixes = simpleCreate(size);

    int c = 0;
    // reads in stdin to find key values for dictionary
    while ((c = fgetc(stdin)) != EOF) {
    ungetc(c, stdin);
    fixed_string_t line = {0};
    size_t size = 0;
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        line.data[size++] = c;
    }
        prefixes->data[prefixes->n] = line;
        // sets array to 0 to reset line value
        nullify_array(line.data);
        (prefixes->n)++;
    }

    // creates buffer array of entire file
    char *buffer = create_cake(filepath, size);

    // creates dictionary
    list_t *list = list_create();

    // initialises each line, skipping header line
    slice_t slice = left_slice(buffer, size, '\n');
    slice_t other = right_slice(buffer, size, '\n');
    slice = left_slice(other.data, other.size, '\n');
    other = right_slice(other.data, other.size, '\n');

    // grabs each slice (except final line)
    while (slice.size != 0) {
        data_t *data_value = calloc(1, sizeof(data_t));

        // finds each data value separated by comma
        slice_t data = find_data(slice.data, slice.size);
        slice_t remainder = {.size = slice.size-data.size, .data = data.data+data.size};
        remainder = find_remainder(remainder.data, remainder.size);

        // goes through line to initialise each field in data_t struct
        for (int i = 0; i < MAX_DATA_FIELDS; i++) {
            // when end of line is reached
            if (data.size == 0) {
                initialise_data(data_value, i, remainder);

                break;
            }
            initialise_data(data_value, i, data);

            // grab next data field
            data = find_data(remainder.data, remainder.size);
            remainder.size = remainder.size-data.size;
            remainder.data = data.data+data.size;
            remainder = find_remainder(remainder.data, remainder.size);
        }
        // appends data to linkedlist
        list_append(list, data_value);

        // grab next line
        slice = left_slice(other.data, other.size, '\n');
        other = right_slice(other.data, other.size, '\n');
    }
    
   // handles last line
    slice_t last_line = find_data(slice.data, slice.size);
    slice.size = find_first_occurence(slice.data, size, '\0');

    slice_t remainder_last = {.size = slice.size-last_line.size, .data = last_line.data+last_line.size};
    remainder_last = find_remainder(remainder_last.data, remainder_last.size);
    last_line = find_data(remainder_last.data, remainder_last.size);
    remainder_last.size = remainder_last.size-last_line.size;
    remainder_last.data = last_line.data+last_line.size;
    remainder_last = find_remainder(remainder_last.data, remainder_last.size);
    
    // data values for last line
    data_t *final = calloc(1, sizeof(data_t));
    // iterates over last line, initialising fields in data struct
    for (int i = 0; i < MAX_DATA_FIELDS; i++){
        if (last_line.size == 0) {
            initialise_data(final, i, remainder_last);
            break;
        }

        initialise_data(final, i, last_line);

        // grab next data field
        last_line = find_data(remainder_last.data, remainder_last.size);
        remainder_last.size = remainder_last.size-last_line.size;
        remainder_last.data = last_line.data+last_line.size;
        remainder_last = find_remainder(remainder_last.data, remainder_last.size);

    }
    // appends final line data to linked list
    list_append(list, final);

    //////////////////////////////
    // stage two /////////////////
    //////////////////////////////

    if (strcmp(argsv[1], "2") == 0) {
    array_t *array = arrayCreate(list->n);

    struct node *temp = list->head;
    while (temp != NULL) {
        insert(array, temp->data);
        temp = temp->next;
    }
    for (int i = 0; i < prefixes->n; i++) {
        fprintf(output, "%s\n", prefixes->data[i].data);
        int index = 0, string_count = 0, char_count = 0, bit_count = 0;
        index = find_and_traverse(array, prefixes->data[i].data, &string_count, &char_count);
        bit_count = char_count*8;
        if (index != -1){
            linearSearch(output, array, index, prefixes->data[i].data, &string_count, &char_count);
            bit_count = char_count*8;
        }
        printf("%s --> b%d c%d s%d\n", prefixes->data[i].data, bit_count, char_count, string_count);
    }
    arrayFree(array);
    }
    
    //////////////////////////////
    // stage three ///////////////
    //////////////////////////////

    if (strcmp(argsv[1], "3") == 0) {
    struct node *temp = list->head;
    tree_t *tree = new_node(list->head->data);
    while (temp != NULL) {
        insert_into_tree(tree, temp->data);
        temp = temp->next;
    }

    //print_tree(tree);
    for (int i = 0; i < prefixes->n; i++) {
        fprintf(output, "%s\n", prefixes->data[i].data);
        //printf("%s --> b%d c%d s%d\n", prefixes->data[i].data, 0, 0, 1);
    }
    //free_tree(tree);
    }
    
    
    // free allocated memory
    simpleFree(prefixes);
    list_free(list);
    free(buffer);
    
    fclose(output);

}
