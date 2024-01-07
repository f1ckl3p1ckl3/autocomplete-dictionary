#include <stdio.h>
#include <stdlib.h>

#ifndef _LINKEDLIST_H_

#define _LINKEDLIST_H_


typedef struct node node_t;
struct node {
    void *data;
    node_t *next;
};

typedef struct list list_t;
struct list {
    node_t *head;
    node_t *tail;
    size_t n;

};

list_t *list_create();
void list_append(list_t *list, void *data);
void search(char *key, list_t *list, int *count, FILE *output);
void node_free(node_t *node);
void list_free(list_t *list);

#endif
