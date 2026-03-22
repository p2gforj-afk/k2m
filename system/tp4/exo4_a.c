#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){

  int tub_nomme; 

  if (mkfifo("ma_pipe", 0600) ==-1){printf("tube existant : on va travailler avec le tube existant\n");} 
  else {printf("tube cree dans le processus ecrivain\n");}

  /* Ouverture du tube pour ecriture */
  tub_nomme = open("ma_pipe", O_WRONLY);
  if(tub_nomme == -1){printf("ouverture tube impossible dans le processus ecrivain\n");return EXIT_FAILURE;}

  /* Ecriture dans le tube */
  printf("ecriture 1\n"); write(tub_nomme, "Tous les matins il achetait ", 28);
  sleep(10);
  printf("ecriture 2\n"); write(tub_nomme, "son petit pain au chocolat la la la la", 38);

  /* Fermeture du tube */
  close(tub_nomme);

  /* Suppression du tube */
  /* unlink = demande de suppression du tube, si on le désire (sinon reste
     sur le système mais ne contient pas de données (point de rencontre) ) */
  unlink("ma_pipe");

  return EXIT_SUCCESS;
}
