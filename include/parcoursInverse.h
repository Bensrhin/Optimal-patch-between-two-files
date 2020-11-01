#ifndef __PARCOURSINVERSE_H__
#define __PARCOURSINVERSE_H__

#include "instruction.h"
#include "operations.h"
#include "manageFile.h"

/***************************************************************************/
struct instruction *courtChemin(int depi, int depj, struct instruction * end,
                                int n, int m, int ** matrix, char ** pA,
                                char **pB, int * lA, int * lB);
/***************************************************************************/
#endif
