#include <stdio.h>
#include <stdlib.h>
#include "readCSV.h"

#ifndef _COMPARE_H_

#define _COMPARE_H_

#define BITS_PER_BYTE 8 // max space for bits

int compare_by_bits(char letter1, char letter2, int *bit_count);
int compare_by_char(char *string1, char *string2, int *char_count);


#endif
