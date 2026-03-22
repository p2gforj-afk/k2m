
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char* argv[]){

    int tube[2];
    int ent;

    /* Creation du tube */
    if (pipe(tube) != 0) { printf("creation du tube impossible"); return EXIT_FAILURE;}

    pid_t pid_fils = -1;
    pid_fils = fork();
    if (pid_fils == -1){ //pcb tout plein de soupe
        perror("Echec du fork \n");
        exit(EXIT_FAILURE);
    }

    if (pid_fils == 0){ //code du fils
        int entf;
        read(tube[0], &entf, 1);
        printf("%d\n", entf*entf);
    }
    else{ //code du pere
        scanf("%d", &ent);
        write(tube[1], &ent, 2); 
        wait(NULL);
    }
    return 0;
}

