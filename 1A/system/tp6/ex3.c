#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int n;
long int x;
long int * tab = NULL;

void * recherche(void * arg);

int main(int argc, char* argv[]){
    pthread_t thr1, thr2;

    if (sscanf(argv[1],"%d", &n) == 0){
        printf("Error in argument\n");
        return EXIT_FAILURE;
    }

    if (argc!= n + 3){
        printf("mauvais nombre d'arg\n");
        exit(EXIT_FAILURE);
    }

    if (sscanf(argv[2],"%ld", &x) == 0){
        printf("Error in argument\n");
        return EXIT_FAILURE;
    }

    tab = malloc(n * sizeof(long int));
    for (int i = 0; i<n; i++){
        long int tmp;
        if (sscanf(argv[3 + i],"%ld", &tmp) == 0){
            printf("Error in argument\n");
            return EXIT_FAILURE;
        }
        tab[i] = tmp;
    }

    if (pthread_create(&thr1,NULL,recherche,(void *) 0) != 0) {
        fprintf(stderr, "Erreur dans pthread_create\n");
        exit(EXIT_FAILURE);
    }

    long int offset = n/2;
    if (pthread_create(&thr2,NULL,recherche,(void *) offset) != 0) {
        fprintf(stderr, "Erreur dans pthread_create\n");
        exit(EXIT_FAILURE);
    }

    pthread_exit(EXIT_SUCCESS);
}

void * recherche(void * arg){
    long int offset = (long) arg;
    for(int i = offset; i<=(offset + n/2); i++){
        if (x == tab[i]){
            free(tab);
            printf("element trouver en postiion %d\n", i+1);
            exit(EXIT_SUCCESS);
        }
    }
    printf("le mec il a pas\n");
    pthread_exit(EXIT_SUCCESS);
}
