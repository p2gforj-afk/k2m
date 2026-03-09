#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

//#define rec

int main(void){
    int pr(int, int), pi(int, int);
    int x,y,z;
    printf("x = ");
    scanf("%d", &x);
    while(getchar()!='\n');
    printf("y = ");
    scanf("%d", &y);
#ifdef rec
    z = pr(x, y);
#else
    z = pi(x, y);
#endif
    printf("%d^%d = %d\n",x,y,z);
    return 0;
}

int pr (int x, int y){
    if(y == 0) return 1;
    else return x*pr(x,y-1);
}

int pi (int x, int y){
    int res = 1;
    for(int i=0; i<y; i++) res = res*x;
    return res;
}

