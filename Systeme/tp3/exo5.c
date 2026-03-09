
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>



void MyG(int sig){
    printf("element trouver\n");
}

int main(int argc, char* argv[]){
    signal(SIGUSR1, MyG);
    int tab[10];
    int x;
    for (int i = 1; i<=10; i++){
        sscanf(argv[i], "%d", &x);
        tab[i-1] = x;
    }
    sscanf(argv[argc-1], "%d", &x);

    pid_t pid_fils_1 = -1; //valeur de retour du fork
    pid_t pid_fils_2 = -1; //retour fork fils 2
    
    pid_fils_1 = fork();
    if (pid_fils_1 == -1){//pcb tout plein de soupe
        perror("Echec du fork \n");
        exit(EXIT_FAILURE);
    }

    if (pid_fils_1 == 0){ //code du fils 1
        for (int i = 0; i<5; i++){
            if (tab[i] == x){
                kill(getppid(),SIGUSR1);
            }
        }
    }
    else{
    pid_fils_2 = fork();
    if (pid_fils_2 == -1){//pcb tout plein de soupe
        perror("Echec du fork \n");
        exit(EXIT_FAILURE);
    }

    if (pid_fils_2 == 0){ //code du fils 1
        for (int i = 5; i<10; i++){
            if (tab[i] == x){
                kill(getppid(),SIGUSR1);
            }
        }
    }
    else{ //code du pere
        pause();
        kill(pid_fils_1,9);
        kill(pid_fils_2,9);
    }
    }
    return 0;
}
