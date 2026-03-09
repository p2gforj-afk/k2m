
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 5

unsigned int result;

void MyG(int sig){
    printf("signal : %d\n", sig);
}


int main(void){
    pid_t pid_fils = -1; //valeur de retour du fork
    pid_fils = fork();
    if (pid_fils == -1){//pcb tout plein de soupe
        perror("Echec du fork \n");
        exit(EXIT_FAILURE);
    }

    if (pid_fils != 0){ //code du pere
        for(int i = 1; i<= 32; i++){
            signal(i,MyG);
        }
        printf("pid pere : %d\n", getpid());
        while(1){};
    }
    else{ //code du fils
        srand(time(NULL)*getpid()*rand());
        for(int j = 0; j<50; j++){
            sleep(1);
            kill(getppid(), 1+rand()%31);
            printf("%d\n", getppid());
        }
    }
    return 0;
}
