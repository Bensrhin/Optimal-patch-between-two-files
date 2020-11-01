/**
  *\file writePatch.c
  *\brief le fichier prend les arguments nécessaires pour écrire le patch
*/
#include "../include/writePatch.h"
#include <stdlib.h>

/***************************************************************************/
void print_string(FILE * file, char * s, int len)
{
  for (int k = 0; k<len; k++)
  {
    fprintf(file, "%c", s[k]);
  }
}
/***************************************************************************/
/**
  *\fn void write_patch(FILE* file, struct instruction * instruction, int *tab1, int*tab2)
  *\brief la fonction écrire l'instruction donnée en parametre
  *\param file le fichier surlequelle on écrit
  *\param instruction c'est l'insruction donnée
  *\param tab1 tableau contenant les tailles du fichier f1
  *\param tab2 tableau contenant les tailles du fichier f2

*/
void write_patch(FILE* file, struct instruction * instruction, int *tab1, int*tab2)
{
  while (instruction != NULL)
  {
    if (instruction->stat == ADD)
    {
      fprintf(file, "+ %i\n", instruction->i);
      int j = tab2[instruction->j - 1];
      print_string(file, instruction->bj, j);
    }
    else if (instruction->stat == DELETE)
    {
      fprintf(file, "- %i\n", instruction->i);
      int i = tab1[instruction->i - 1];
      print_string(file, instruction->ai, i);
    }
    else if (instruction->stat == SWAP)
    {
      fprintf(file, "= %i\n", instruction->i);
      int i = tab1[instruction->i - 1];
      print_string(file, instruction->ai, i);
      int j = tab2[instruction->j - 1];
      print_string(file, instruction->bj, j);
    }
    instruction = instruction->next;
  }
}
/***************************************************************************/
