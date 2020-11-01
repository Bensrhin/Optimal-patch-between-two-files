/**
  *\file computePatchOpt.c
  *\brief le fichier main qui crée le patch
  *\author {BENSRHIER Nabil , YAGOUTI Redouane}
  *\date 07/11/2019
  *\version 4.0
*/
#include "../include/computePatchOpt.h"

int main(int argc, char** argv){
  if (argc != 4)
  {
      fprintf(stderr, "Usage: ./computePatchOpt F1 F2 P\n");
      return EXIT_FAILURE;
  }
  /*** Début du temps d'execution ***/
  clock_t t1, t2;
  t1 = clock();
  /*** lecture des fichiers */
  const char *f1 = argv[1];
  const char *f2 = argv[2];
  char *p = argv[3];

  int file1 = open(f1, O_RDONLY, 0);
  int file2 = open(f2, O_RDONLY, 0);

  struct stat sb1;
  struct stat sb2;

  if ((fstat(file1,&sb1) == -1) & (fstat(file2,&sb2) == -1)){
      perror("couldn't get file size.\n");
  }

  char *file1_in_memory = mmap(NULL, sb1.st_size, PROT_READ, MAP_PRIVATE, file1, 0);
  char *file2_in_memory = mmap(NULL, sb2.st_size, PROT_READ, MAP_PRIVATE, file2, 0);

  /*********** le noombre des lignes des deux fichiers **********************/
  int nbf1 = nbLine(file1_in_memory, sb1.st_size);
  int nbf2 = nbLine(file2_in_memory, sb2.st_size);
  /*********** les tailles des lignes de chauqe fichier **********************/
  int *tab1 = longeurFile(file1_in_memory, sb1.st_size, nbf1);
  int *tab2 = longeurFile(file2_in_memory, sb2.st_size, nbf2);

  /******************************************************************/
  printf("file source size is %d\n", nbf1);
  printf("file target size is %d\n", nbf2);
  /******************************************************************/
  /******************* pointeurs vers début de chaque ligne *****************/
  char ** source = pointeurLigne(file1_in_memory, tab1, nbf1);
  char ** target = pointeurLigne(file2_in_memory, tab2, nbf2);

  /************** Choix du seuil selon les perormances du PC *****************/
  int seuil = 10000;
  int lignes = nbf1;
  int colonnes = nbf2;
  printf("**********************************************\n");
  struct instruction * current = NULL;
  /* La premier structure pointe vers une strucuture null ******************/

  current = getHead(seuil, lignes, colonnes, current, source, target, tab1, tab2);

  /******* La liste chainée des instructions est maitenant disponible ********/

  /******** L'écriture du contenu des instructions dans le patch *************/
  FILE *patch = fopen(p, "w");
  write_patch(patch, current, tab1, tab2);
  fclose(patch);
  /**** L'opération est terminée, il nous reste que libérer l'espace alloué****/
  free_instructions(current);
  free(tab1);
  free(tab2);
  free(source);
  free(target);
  /*************** FIn de l'exécution ****************************************/
  t2 = clock();
  int time = (float)(t2-t1)/CLOCKS_PER_SEC;
  int temps = (int)(time);
  printf("temps : %02d:%02d:%02d  : \n", temps/3600, (temps%3600)/60, temps%60);
  return EXIT_SUCCESS;
}
