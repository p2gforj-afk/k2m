#include <stdio.h> // stderr, stdout, fprintf, perror
#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h> // exit

int main(void){
    int i;
    for (i = 1;i<3000; i++){
        printf("(%d) %dkm..., %d km a pied, ca use les souliers. \n",getpid(),i,i);
    }
    return(EXIT_SUCCESS);
}