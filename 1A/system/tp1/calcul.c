#include <stdio.h> // stderr, stdout, fprintf, perror
#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <stdlib.h> // exit
#include <limits.h>

long factorielle(int n){
    int i;
    long result = 1;
    if (n == 0)
        return 1;
    for(i = 1; i<n && (result <LONG_MAX/i); i++){
        result = i * result;
    }
    return result;
}

int main(void){
    // Ce programme effectue un calcul sans grand interet
    int i,j;
    long f;
    for(i = 1; i<20; i++){
        for(j =1 ; j<1e7; j++){
            f=factorielle(i);
        }
        printf("factorielle de %d = %ld\n", i, f);
    }
    return EXIT_SUCCESS;
}
