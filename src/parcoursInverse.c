/**
  *\file parcoursInverse.c
  *\brief Création d'une liste chainée des instructions du patch
*/
#include "../include/parcoursInverse.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
/************* Création d'une liste chainée des instruction du patch ********/

/*  l'idée est de parcourir la matrice des coûts tout en enregistrant les
    instructions à faire pour la ligne i et la coolonne j dans une structure.
    l'idée ici est aussi le fait de créer une liste chainée :
      chaque instruction à un suivant vers l'instruction qui la suive.
      c'est-à-dire qui la précède en remontant dans la matrice des coûts
*/

/**
  *\fn struct instruction *courtChemin(int depi, int depj, struct instruction * end,
                                  *int n, int m, int ** matrix, char ** pA,
                                  *char **pB, int * lA, int * lB)
  *\brief la fonction crée une liste chainée des instructions à faire
  * à travers la matrice des coûts passée en paramètre
  *\param depi c'est le départ de ligne liée au fichier f1
  *\param depi c'est le départ de ligne liée au fichier f2
  *\param end c'est l'insruction donnée de la derniere opération du cour chemin
  *\param n c'est la fin de ligne liée au fichier f1
  *\param m c'est la fin de ligne liée au fichier f2
  *\param pA pointeur sur les lignes du fichier f1
  *\param pB pointeur sur les lignes du fichier f2
  *\param lA tableau contenant les tailles du fichier f1
  *\param lB2 tableau contenant les tailles du fichier f2
*/

struct instruction *courtChemin(int depi, int depj, struct instruction * end,
                                int n, int m, int ** matrix, char ** pA,
                                char **pB, int * lA, int * lB)
{
    /***** initailisation des variables *****/
    int i = n;
    int j = m;
    struct instruction * next = end;
    int operation[3];
    /*** on parcourt la matrice des coûts du dernier élément jusqu'au seuil ***/
    while (i > depi && j > depj) {

        /* les lignes Ai et Bj */
        char *ai = pA[i - 1];
        char *bj = pB[j - 1];
        /* la création de l'instruction */
        struct instruction * current = malloc(sizeof(struct instruction));
        remplir(current, next, i, j);
        /* les coûts des voisins */
        operation[0] = matrix[i-depi][j-depj - 1] + 10 + lB[j - 1];
        operation[1] = matrix[i-depi - 1][j-depj] + 10;
        int cost = cout(i - 1, j - 1, pA, pB, lA, lB);
        operation[2] = matrix[i-depi - 1][j-depj - 1] + cost;

        int nextStep = indexMin(operation, 3);

        if (nextStep == 0)
        {

          current->stat = ADD;
          current->bj = bj;
          j -= 1;
        }
        else if (nextStep == 2)
        {
          if (cost == 0)
          {
              current->stat = NOTHING;
          }
          else
          {
            current->stat = SWAP;
            current->bj = bj;
            current->ai = ai;
          }
          free(matrix[i-depi]);
          i -= 1;
          j -= 1;
        }
        else if (nextStep == 1)
        {
            current->ai = ai;
            free(matrix[i-depi]);
            i -= 1;
            current->stat = DELETE;
        }
        next = current;

    }
    // sinon on respecte bien la ram : donc on continue vers le zero.

    /**  si on finit les éléments du fichier target
          on détruit le reste du fichier source
    */

    /**  par contre si on finit les éléments du fichier source
          on ajoute le reste du fichier target
    */
    while (i>depi)
    {
      if (j == 0)
      {
        char *ai = pA[i - 1];
        struct instruction * current = malloc(sizeof(struct instruction));
        current->ai = ai;
        remplir(current, next, i, j);
        current->stat = DELETE;
        next = current;
      }
      free(matrix[i-depi]);
      i -= 1;
    }
    if (i != 0)
    {
      free(matrix[i-depi]);
      free(matrix);
      return next;
    }
    /**  par contre si on finit les éléments du fichier source
          on ajoute le reste du fichier target
    */
    while (j>depj)
    {
      if ( i == 0)
      {
        char *bj = pB[j - 1];
        struct instruction * current = malloc(sizeof(struct instruction));
        remplir(current, next, i, j);
        current->bj = bj;
        current->stat = ADD;
        next = current;
      }

      j -= 1;
      /* ici on libère pas puisqu'on reste sur la même ligne*/
    }
    /* finalement on libère la dernière ligne et puis la matrice */
    free(matrix[i-depi]);
    free(matrix);
    return next;


}
