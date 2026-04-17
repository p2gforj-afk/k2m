#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * codeThread(void * arg);

int main(void){
  pthread_t thr1, thr2, thr3;
  int i;
    if (pthread_create(&thr1, NULL, codeThread, (void *)1L) != 0) { 
        fprintf(stderr, "Erreur pthread_create premier thread\n");
    }

    if (pthread_create(&thr2, NULL, codeThread, (void *)2L) != 0) { 
        fprintf(stderr, "Erreur pthread_create premier thread\n");
    }

    if (pthread_create(&thr3, NULL, codeThread, (void *)3L) != 0) { 
        fprintf(stderr, "Erreur pthread_create premier thread\n");
    }

  for(i=1;i<=4;i++){
    printf("Thread principal : Affichage %d/4\n",i);
    sleep(1);
  }
  pthread_exit(EXIT_SUCCESS);
}

void * codeThread(void * arg){
    long int num = (long) arg;
    for(int i = 1;i<= 6; i++){
        printf("Thread %ld : Affichage %d/6\n",num, i);
        sleep(1);
    }
  exit(EXIT_SUCCESS);
}
