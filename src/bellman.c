/**
  *\file bellman.c
  *\brief la création de la matrice des coûts
*/
#include "../include/bellman.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/******************* la création de la matrice des coûts **********************/

/*********Selon la modélisation récursive par équations de Bellman ************/
/**
*\fn int ** initialiser(int depi, int depj, int n, int m,  char **source,
                  * char **target, int*lA, int*lB)
*\brief la fonction crée une matrice des coûts
 *Selon la modélisation récursive par équations de Bellman
*\param depi c'est le départ de ligne liée au fichier f1
*\param depi c'est le départ de ligne liée au fichier f2
*\param n c'est la fin de ligne liée au fichier f1
*\param m c'est la fin de ligne liée au fichier f2
*\param source pointeur sur les lignes du fichier f1
*\param target pointeur sur les lignes du fichier f2
*\param lA tableau contenant les tailles du fichier f1
*\param lB2 tableau contenant les tailles du fichier f2
*/
int ** initialiser(int depi, int depj, int n, int m,  char **source,
                   char **target, int*lA, int*lB)
{
    /* pour calculer le coût du patch, il faut juste deux colonnes */
    int *ligne1 = malloc((n+1) * sizeof(int));
    int *ligne2 = malloc((n+1) * sizeof(int));
    /* le choix de int est important dans le cas des fichiers géants,
    on a remarqué que les coûts ne dépassent pas 2**32, donc on doit les codés sur
    4 octets, d'où ce choix.
    */
    int **matrix = malloc((n-depi+1) * sizeof(int *));
    int * temp = NULL;
    int j = 0;
    bool passe = false;
    while (j < m + 1)
    {
      for (int i = 0; i < n + 1; i++) {
        if(j == depj){
          if (i > (depi - 1) && i< (n + 1))
          {
            matrix[i-depi] = malloc((m-depj+1) * sizeof(int));
            // on alloue une matrice de taille  (n-depi+1) x (m-depj+1)
            // avec n le nombre de lignes du sous fichier source
            // et m le nombre de lignes du sous fichier target
          }

          passe = true;
          /* ceci indique qu'on a atteind la position ou on peu commencer
          le sauvegarde dans la matrice des coûts*/
        }
        /*********** les conditions initiales ************/
        if (i == 0 && j == 0) {
            ligne1[0] = 0;
            if (passe)
              if (i > (depi - 1) && i< (n + 1))
                matrix[i-depi][j-depj] = 0;
        }
        else if (i == 0) {
            int sum = 0;
            for (int k = 0; k < j; k++) {
                sum += 10 + lB[k];
            }
            ligne1[0] = (int)sum ;
            if (passe)
              if (i > (depi - 1) && i< (n + 1))
                matrix[i-depi][j-depj] = sum;
        }
        else if (j == 0) {
            ligne1[i] = (int)(10 * i);
            if (passe)
              if (i > (depi - 1) && i< (n + 1))
                matrix[i-depi][j-depj] = ligne1[i];
        }
        /************* calculs récursifs ********************/
        else {
            // addition
            int a = (int)(ligne2[i] + 10 + lB[j - 1]);
            // destr
            int c = ligne1[i - 1] + 10;
            // sub ou rien
            int cost = cout(i - 1, j - 1, source, target, lA, lB);
            int b = ligne2[i - 1] + cost;
            // le min

            ligne1[i] = min(a, b, c);
            if (passe)
              if (i > (depi - 1) && i< (n + 1))
                matrix[i-depi][j-depj] = ligne1[i];
        }
      }
      /* on permute les deux colonnes pour qu'on puisse calculer les coûts de
         la colonne qui les suit */
      temp = ligne1;
      ligne1 = ligne2;
      ligne2 = temp;
      j += 1;
    }
    /* finalement on libère ces deux colonnes */
    free(ligne2);
    free(ligne1);
    return matrix;
}
