
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int i = 0;

void MyG(int sig){
    i ++;
}

int main(int argc, char* argv[]){
    signal(SIGINT,MyG);
    while (i<3){
        pause();
    }
    printf("\net de 3 SIGINT\n");
    return 0;
}
