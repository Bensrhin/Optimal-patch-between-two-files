#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "../include/bellman.h"
#include "../include/parcoursInverse.h"

/*****************************************************************************/

struct instruction
{
  enum {ADD, DELETE, NOTHING, SWAP} stat;
  int i;
  int j;
  char * ai;
  char * bj;
  struct instruction * next;
};

/***************************************************************************/
struct instruction * getHead(int seuil, int lignes, int colonnes,
                             struct instruction * end, char **source,
                             char **target, int*tab1, int*tab2);

void remplir(struct instruction * current, struct instruction *next, int i, int j);

void free_instructions(struct instruction * current);

/*****************************************************************************/

#endif
