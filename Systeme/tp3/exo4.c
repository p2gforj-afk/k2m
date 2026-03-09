
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 5

unsigned int result;

void MyG(int sig){
    printf("un simple affichage dans l'interpreteur shell\n");
}


int main(void){
    pid_t pid_fils = -1; //valeur de retour du fork
    pid_fils = fork();

    if (pid_fils == -1){//pcb tout plein de soupe
        perror("Echec du fork \n");
        exit(EXIT_FAILURE);
    }

    if (pid_fils != 0){ //code du pere
        printf("pid pere : %d\n", getpid());
        pid_t retour;
        wait(&retour);
        printf("%d va voir la doc\n", retour);
    }
    else{ //code du fils
        signal(SIGUSR1, MyG);
        printf("pid fils : %d\n", getpid());
        pause();
    }
    return 0;
}
