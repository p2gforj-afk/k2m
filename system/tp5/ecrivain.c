/********************************
 * Fichier shm-ecrivain.c
 * Livre "Programmation d'applications système sous Linux"
 *
 * P. Alain, J. Chevelu, S. Le Maguer, V. Thion, B. Vozel
 *
 ********************************/
// Processus créateur d'une zone de memoire partagee nommée shmCompteur de stockage d'un entier.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>

int main(){
  int fd, i, valRetour;
  int *compteur;
  sem_t *mutex;       
  mutex = sem_open("mmutex", O_CREAT, 0644, 1); // 1 jeton (MUTEX)
  if (mutex ==SEM_FAILED){perror("sem_open mmutex"); exit(EXIT_FAILURE);}

  valRetour = shm_unlink("shmCompteur");
  if (valRetour==0) { fprintf(stdout, "[Log] RAZ shmCompteur\n"); }
  fd = shm_open("shmCompteur", O_RDWR | O_CREAT, 0644);
  if (fd==-1){ perror("shmCompteur");exit(EXIT_FAILURE); }
  valRetour=ftruncate(fd, sizeof(int));
  if (valRetour==-1){ perror("ftruncate");exit(EXIT_FAILURE); }
  compteur = mmap(NULL,sizeof(int),PROT_WRITE,MAP_SHARED,fd,0);
  if (compteur==MAP_FAILED) { perror("mmap");exit(EXIT_FAILURE); }
  for (i = 0; i < 10; i++) {
    sem_wait(mutex);
    // Début section critique
    *compteur = i; // NE PAS MODIFIER
    fprintf(stdout, "Producteur : insertion de %d faite dans le segment partage\n",(*compteur)); // NE PAS MODIFIER
    // Fin de section critique
    sem_post(mutex);
    sleep(1);
  }
  sem_close(mutex);
  exit(EXIT_SUCCESS);
}
