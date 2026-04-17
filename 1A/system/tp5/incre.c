#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

char *chiffre_to_english(int);
char *chiffre_to_breton(int);

int main(){
  int fd;
  int *compteur;
	
  fd = shm_open("compteur", O_RDWR, 00);
  if (fd==-1) { perror("compteur"); exit(EXIT_FAILURE);}
  compteur = mmap(NULL,sizeof(int),PROT_WRITE,MAP_SHARED,fd,0);
  if (compteur == MAP_FAILED) {perror("mmap");exit(EXIT_FAILURE);}
  while (1) {
    *compteur += 1;
    printf("(PID : %d) compteur = %d\n",getpid(),*compteur);
    sleep(1);
  }
  exit(EXIT_SUCCESS);
}
