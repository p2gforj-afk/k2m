#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
  int tub_aller; 
  int tub_retour; 

  /* Ouverture du tube pour lecture */
  tub_aller = open("aller", O_RDONLY);
  if(tub_aller == -1){perror("ouverture tube impossible dans le processus lecteur\n");return EXIT_FAILURE;}

  int a;
  int b;
  read(tub_aller, &a, sizeof(int));
  read(tub_aller, &b, sizeof(int));

  close(tub_aller);

  tub_retour = open("retour", O_WRONLY);
  int ahsduifhaiul = a+b;
  write(tub_retour,&ahsduifhaiul, sizeof(a));

  close(tub_retour);
  return EXIT_SUCCESS;
}
