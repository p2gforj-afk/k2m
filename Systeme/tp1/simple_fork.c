#include <stdio.h> // stderr, stdout, fprintf, perror
#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h> // exit

int main(void){
    pid_t pid_fils = -1; //valeur de retour du fork
    pid_fils = fork();
    if (pid_fils == -1){//pcb tout plein de soupe
        perror("Echec du fork \n");
        exit(EXIT_FAILURE);
    }
    printf("(%d) all u need is love \n", getppid());
    sleep(50);
    return EXIT_SUCCESS;
}