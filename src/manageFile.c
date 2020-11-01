/**
  *\file manageFile.c
  *\brief les outils nécessaires pour calculer le coût
*/
#include "../include/manageFile.h"
#include "../include/operations.h"
#include <stdlib.h>
#include <string.h>

/****************** nombre de lignes dans un fichier ************************/
/**
  *\fn int nbLine(char *file, int size)
  *\brief renvoie le nombre de ligne dans un fichier.
*/
int nbLine(char *file, int size)
{
  int number = 0;
  char *c = malloc(sizeof(char));
  for (int i = 0; i < size; i++)
  {
    strncpy(c, file + i, 1);
    if ( strcmp(c, "\n") == 0)
    {
      number += 1; // si on arrive à la fin d'une ligne on incrémente par 1;
    }
  }
  free(c);
  return number;
}

/************** le coût d’une substitution de la ligne Ai en Bj ************/
/**
  *\fn int cout(int i, int j, char **source, char **target,
                      *int*tab1, int*tab2)
  *\brief calcul le coût (i,j)
*/
int cout(int i, int j, char **source, char **target,
                    int*tab1, int*tab2)
{
  char *ai = source[i];
  char *bj = target[j];
  int maxi = max(tab1[i], tab2[j]);

  if (tab1[i] == 0 || tab2[j] == 0)
  {
    return 0; // si la chaine est vide on évite la comparaison.
  }
  if (!strncmp(ai, bj, maxi))
  {
    return 0; // le cas d'égalité
  }
  else
  {
    return (unsigned short)(10 +  tab2[j]);
  }
}

/********** liste des tailles des lignes d'un fichier en paramètres **********/
/**
  *\fn int *longeurFile(char *file, int size, int lineNb)
  *\brief liste des tailles des lignes d'un fichier en paramètres
*/
int *longeurFile(char *file, int size, int lineNb)
{
  int *tailles = malloc(lineNb * sizeof(int));
  int sum = 0;
  int j = 0;
  char *c = malloc(sizeof(char));
  for (int i = 0; i < size; i++)
  {
    sum += 1;
    strncpy(c, file + i, 1);
    if (strcmp(c, "\n") == 0)
    {
      /* on ajoute le nombre des caractères de chaque ligne et on réinitialise
         le contour à zéro
      */
      tailles[j] = sum;
      j += 1;
      sum = 0;
    }
  }
  free(c);
  return tailles;
}

/************* liste des pointeurs sur chaque début de ligne *****************/
/**
  *\fn char **pointeurLigne(char *file, int * tab, int len)
  *\brief liste des pointeurs sur chaque début de ligne
*/
char **pointeurLigne(char *file, int * tab, int len)
{
  char ** lignes = malloc(len * sizeof(char *));
  int sum = 0;
  for (int i = 0; i < len; i++)
  {
    lignes[i] = file + sum;
    sum += tab[i];
  }
  return lignes;
}

/******************************************************************************/
