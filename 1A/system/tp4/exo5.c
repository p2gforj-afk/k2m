#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){

  int tub_aller; 
  int tub_retour;

  if (mkfifo("aller", 0600) ==-1){printf("tube existant : on va travailler avec le tube existant\n");} 
  else {printf("tube cree dans le processus ecrivain\n");}

  if (mkfifo("retour", 0600) ==-1){printf("tube existant : on va travailler avec le tube existant\n");} 
  else {printf("tube cree dans le processus ecrivain\n");}


  /* Ouverture du tube pour ecriture */
  tub_aller = open("aller", O_WRONLY);
  if(tub_aller == -1){printf("ouverture tube impossible dans le processus ecrivain\n");return EXIT_FAILURE;}

  /* Ecriture dans le tube */
  int ent1 = 12;
  int ent2 = 2;
  printf("2 entier a additioner\n"); write(tub_aller,&ent1, sizeof(int)); write(tub_aller, &ent2, sizeof(int));

  /* Fermeture du tube */
  close(tub_aller);


  tub_retour = open("retour", O_RDONLY);
  if(tub_retour == -1){perror("ouverture tube impossible dans le processus lecteur\n");return EXIT_FAILURE;}
  int gwer;
  read(tub_retour, &gwer, sizeof(int));
  printf("resultat de l'addriotn : %d\n",gwer);sleep(1);

  close(tub_retour);

  unlink("aller");
  unlink("retour");

  return EXIT_SUCCESS;
}
