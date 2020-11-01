#ifndef __WRITEPATCH_H__
#define __WRITEPATCH_H__

#include <string.h>
#include <stdio.h>
#include <string.h>
#include "../include/instruction.h"

/***************************************************************************/
extern void print_string(FILE * file, char * s, int len);

extern void write_patch(FILE* file, struct instruction * instruction,
                        int *tab1, int*tab2);

/***************************************************************************/
#endif
