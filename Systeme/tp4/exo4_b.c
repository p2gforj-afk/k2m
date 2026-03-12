#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
  int tub_nomme; 
  char buffer[6]; 

  /* Ouverture du tube pour lecture */
  tub_nomme = open("ma_pipe", O_RDONLY);
  if(tub_nomme == -1){perror("ouverture tube impossible dans le processus lecteur\n");return EXIT_FAILURE;}

  /* Lecture dans le tube, par paquets de 5 octets */
  buffer[5]='\0'; // Ajout caractère de fin de chaîne en position 5 du buffer (pour affichages).
  while (read(tub_nomme, buffer, 5)){printf("Je viens de lire : %s\n",buffer);sleep(1);}

  /* Fermeture du tube */
  close(tub_nomme);

  return EXIT_SUCCESS;
}
