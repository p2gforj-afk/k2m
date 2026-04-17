#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<time.h>

int main(int argc, char * argv[]){
    unsigned int sommei(unsigned int), sommer(unsigned int);
    clock_t t1,t2;
    if (argc < 2) {
        printf("sale sinje\n");
        return 0;
    }
    unsigned int N,i,r;
    sscanf(argv[1],"%u", &N);
    t1 = clock();
    i = sommei(N);
    t2 = clock();
    printf("Calcul de sommei(%u)=%u en %f s\n",N,i,(float)(t2 - t1)/CLOCKS_PER_SEC);
    t1 = clock();
    r = sommer(N);
    t2 = clock();
    printf("Calcul de sommer(%u)=%u en %f s\n",N,r,(float)(t2 - t1)/CLOCKS_PER_SEC);
    return 0;
}

unsigned int sommei(unsigned int N){
    int res = 0;
    for(int i = 1; i<=N ; i++) res += i; 
    return res;
}
unsigned int sommer(unsigned int N){
    if(N == 1) return 1;
    else return N+sommer(N-1);
}