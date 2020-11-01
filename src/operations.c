/**
  *\file operations.c
  *\brief les opérations nécessaires pour faire le calcul
*/
#include "../include/operations.h"
#include <stdlib.h>
/********************* remplir une instruction *******************************/


/******************* l'indice du minumum dans une liste donnée ***************/
/**
  *\fn int indexMin(int *tab, int tabSize)
  *\brief renvoie l'indice du minimum
*/
int indexMin(int *tab, int tabSize)
{
  int min = tab[0];
  int index_min = 0;
  for (int i = 1; i < tabSize; i++)
  {
    if (tab[i] < min)
    {
      min = tab[i];
      index_min = i;
    }
  }
  return index_min;
}

/************* le minimum des trois nombres donnés en paramètres *************/
/**
  *\fn int min(int i, int j, int k)
  *\brief renvoie le minimum
*/
int min(int i, int j, int k)
{
  int a = i;
  if (i > j)
  {
    a = j;
  }
  if (a <= k) {
    return a;
  }
  return k;
}

/********************** le maximum entre deux nombres ************************/
/**
  *\fn int max(int i, int j)
  *\brief renvoie le maximum
*/
int max(int i, int j)
{
  if (i > j)
  {
    return i;
  }
  return j;
}

/*****************************************************************************/
