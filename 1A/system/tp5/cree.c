#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
  int fd, valRetour;
  int *compteur;

  valRetour = shm_unlink("compteur");
  if (valRetour==0) { fprintf(stdout, "[Log] RAZ compteur\n"); }
  fd = shm_open("compteur", O_RDWR | O_CREAT, 0644);
  if (fd==-1){ perror("compteur");exit(EXIT_FAILURE); }
  valRetour=ftruncate(fd, sizeof(int));
  if (valRetour==-1){ perror("ftruncate");exit(EXIT_FAILURE); }
  compteur = mmap(NULL,sizeof(int),PROT_WRITE,MAP_SHARED,fd,0);
  if (compteur==MAP_FAILED) { perror("mmap");exit(EXIT_FAILURE); }
  
  *compteur = 0; 

  exit(EXIT_SUCCESS);
}  
