#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedList.h"
#include "readCSV.h"
#include "slicing.h"


// creates empty linked list
list_t *list_create() {
    list_t *list = malloc(sizeof(*list));
    assert(list);
    list->head = list->tail = NULL;
    list->n = 0;
    return list;
}

// appends node to end of linked list
void list_append(list_t *list, void *data) {
    assert(list);
    node_t *new_node = malloc(sizeof(*new_node));
    assert(new_node);
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        (list->n)++;
        return;
    }
    list->tail->next = new_node;
    list->tail = new_node;
    (list->n)++;
    return;
}


// performs a linear search on linked list, finding node which contains key input
void search(char *key, list_t *list, int *count, FILE *output) {
    node_t *temp = list->head;
    *count = 0;
    fprintf(output,"%s\n", key);
    while (temp != NULL) {
        data_t *soln = temp->data;
        if ((strcmp(key, soln->trading_name.data)) == 0) {
                (*count)++;
                print_data(soln, output);
        }
        temp = temp->next;
    }
}

// frees linked list
void list_free(list_t *list) {
    assert(list != NULL);
    node_t *curr = list->head;
    while (curr) {
        node_t *temp = curr;
        curr = curr->next;
        free(temp->data);
        free(temp);
    }
    free(list);
}

