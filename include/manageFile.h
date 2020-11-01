#ifndef __MANAGEFILE_H__
#define __MANAGEFILE_H__

/***************************************************************************/
int nbLine(char *file, int size);

int cout(int i, int j, char **source, char **target, int*tab1, int*tab2);

int *longeurFile(char *file, int size, int lineNb);

char **pointeurLigne(char *file, int * tab, int len);

/***************************************************************************/
#endif
