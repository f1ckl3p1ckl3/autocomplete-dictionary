#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compare.h"

// returns 0 equal, else returns 1 if NOT equal
// note: bit_count int MUST ALREADY BE INITIALISED!!!
int compare_by_bits(char letter1, char letter2, int *bit_count) {
    int cock = *bit_count;
    for (int i = sizeof(char)*BITS_PER_BYTE - 1; i >= 0; i--) {
        int a = (letter1 & (1<<i))&&1;
        int b = (letter2 & (1<<i))&&1;
        printf("%d, %d\n", a, b);
        if (a != b) {
            (*bit_count)++;
            printf("\n");
            printf("bits added: %d\n", *bit_count-cock);
            printf("total bits: %d\n\n", *bit_count);
            return 1;
        }
        (*bit_count)++;
    }
    printf("\n");
    printf("bits added: %d\n", *bit_count-cock);
    printf("total bits: %d\n\n", *bit_count);
    return 0;
}


// returns 0 if equal, returns 1 if string1 smaller, returns 2 if string1 bigger
int compare_by_char(char *string1, char *string2, int *char_count) {
    for (int i = 0; i < strlen(string1); i++) {
        if (string1[i] < string2[i]) {
            (*char_count)++;
            return 1;
        }
        if (string2[i] < string1[i]) {
            (*char_count)++;
            return 2;
        }
        (*char_count)++;
    }
    // add 1 for char, 8 for bit, for null pointer
    (*char_count)++;
    return 0;
}