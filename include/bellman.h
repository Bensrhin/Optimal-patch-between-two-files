#ifndef __BELLMAN_H__
#define __BELLMAN_H__

#include "manageFile.h"
#include "operations.h"

/*******************************************************************************/

int ** initialiser(int depi, int depj, int n, int m,  char **source,
                   char **target, int*lA, int*lB);

/*******************************************************************************/
#endif
