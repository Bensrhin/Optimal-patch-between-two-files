/**
  *\file instruction.c
  *\brief le fichier contenant la structure sur laquelle
  *on sauvegarde une instruction
*/
#include "../include/instruction.h"
#include <stdlib.h>
#include <stdio.h>

/******************************************************************************/
/**
  *\fn struct instruction * getHead(int seuil, int lignes, int colonnes,
                              *struct instruction * end, char **source,
                              *char **target, int*tab1, int*tab2)
  *\brief la fonction renvoie un pointeur vers l'instruction finale
  * pour la ligne (0,0)
  *\param seuil la taille de ligne et colonne que la mémoire peut supporter
  *\param lignes nombre de lignes du fichier f1
  *\param colonnes nombre de lignes du fichier f2
  *\param *end un pointeur vers une instruction
  *\param sources pointeur sur les lignes du fichier f1
  *\param target pointeur sur les lignes du fichier f2
  *\param tab1 tableau contenant les tailles du fichier f1
  *\param tab2 tableau contenant les tailles du fichier f2

*/
struct instruction * getHead(int seuil, int lignes, int colonnes,
                             struct instruction * end, char **source,
                             char **target, int*tab1, int*tab2)
{
  int depi = (lignes >= seuil) ? lignes - seuil : 0;
  int depj = (colonnes >= seuil) ? colonnes - seuil : 0;
  struct instruction * current = end;
  int ** bellman_matrix;
  while (depi > 0 || depj > 0){
    bellman_matrix = initialiser(depi, depj, lignes, colonnes, source, target,
                                 tab1, tab2);
    current = courtChemin(depi, depj, current, lignes, colonnes, bellman_matrix,
                          source, target, tab1, tab2);
    if (current->stat == DELETE)
    {
      colonnes = current->j;
      lignes = current->i - 1;
    }
    else if (current->stat == ADD){
      colonnes = current->j - 1;
      lignes = current->i;
    }
    else
    {
      lignes = current->i - 1;
      colonnes = current->j - 1;
    }
    depi = (lignes > seuil) ? lignes - seuil : 0;
    depj = (colonnes > seuil) ? colonnes - seuil : 0;

  }
  bellman_matrix = initialiser(depi, depj, lignes, colonnes, source, target,
                               tab1, tab2);
  current = courtChemin(depi, depj, current, lignes, colonnes, bellman_matrix,
                        source, target, tab1, tab2);
  return current;
}

/***************************************************************************/

void remplir(struct instruction * current, struct instruction *next, int i, int j)
{
  current->i = i;
  current->j = j;
  current->next = next;
}

/***************************************************************************/
/**
* \fn void free_instructions(struct instruction * current)
* \brief libere la liste chainée des instructions.
*\param *current l'instruction courante
*/
void free_instructions(struct instruction * current)
{
  if (current == NULL)
  {
    return;
  }
  free_instructions(current->next);
  free(current);
}

/***************************************************************************/
