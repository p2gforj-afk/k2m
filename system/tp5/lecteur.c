#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

char *chiffre_to_english(int);
char *chiffre_to_breton(int);

int main(){
  int fd;
  int *compteur;
  sem_t *mutex; 
  mutex = sem_open("mmutex", 00); 
	
  fd = shm_open("shmCompteur", O_RDWR, 00);
  if (fd==-1) { perror("shmCompteur"); exit(EXIT_FAILURE);}
  compteur = mmap(NULL,sizeof(int),PROT_READ,MAP_SHARED,fd,0);
  if (compteur == MAP_FAILED) {perror("mmap");exit(EXIT_FAILURE);}
  while (1) {
    sem_wait(mutex);
    // Début section critique
    fprintf(stdout, "La traduction en anglais de %d est", (*compteur)); // NE PAS MODIFIER
    sleep(2);	// Instruction simulant un délai de traitement, NE PAS MODIFIER
    fprintf(stdout, " %s ", chiffre_to_english(*compteur)); // NE PAS MODIFIER
    sleep(2);	// Instruction simulant un délai de traitement, NE PAS MODIFIER
    fprintf(stdout, "et en breton %s\n", chiffre_to_breton(*compteur)); // NE PAS MODIFIER
    // Fin section critique
    sem_post(mutex);
  }
  exit(EXIT_SUCCESS);
}

char *chiffre_to_english(int chiffre){
  switch (chiffre) {
  case 0: return "zero (0)"; break;
  case 1: return "one (1)"; break;
  case 2: return "two (2)"; break;
  case 3: return "three (3)"; break;
  case 4: return "four (4)"; break;
  case 5: return "five (5)"; break;
  case 6: return "six (6)"; break;
  case 7: return "seven (7)"; break;
  case 8: return "eight (8)"; break;
  case 9: return "nine (9)"; break; // Fonction incomplète, peut être étendue
  default: return "Donnée non traitable.\n";
  };
}

char *chiffre_to_breton(int chiffre){
  switch (chiffre) {
  case 0: return "mann (0)"; break;
  case 1: return "unan (1)"; break;
  case 2: return "daou (2)"; break;
  case 3: return "tri (3)"; break;
  case 4: return "pevar (4)"; break;
  case 5: return "pemp (5)"; break;
  case 6: return "c\'hwec\'h (6)"; break;
  case 7: return "seizh (7)"; break;
  case 8: return "eizh (8)"; break;
  case 9: return "nav (9)"; break; // Fonction incomplète, peut être étendue
  default: return "Donnée non traitable.\n";
  }; }
