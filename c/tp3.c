#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<time.h>

struct temperature {
    float c; 
    float f; 
    float k;
};

int main(void) {
    bool saisie(float *);
    void conversion(struct temperature *);
    void affiche(struct temperature *);
    struct temperature t;
    if (saisie(&t.c)) {
        conversion(&t);
        affiche(&t);
    }
    else printf("Erreur de saisie.\n");
    return EXIT_SUCCESS;
}

bool saisie(float * p) {
    printf("Temperature en Celsius ? ");
    if (scanf("%f", p) == 1) return true;
    else return false;
}

void conversion(struct temperature *p) {
    float c2f(float);
    float c2k(float);
    p->f = c2f(p->c);
    p->k = c2k(p->c);
}

float c2f(float c) {
    return (c*1.8)+32;
}

float c2k(float c) {
    return c+273.15;
}

void affiche(struct temperature *p) {
    printf("Corespondances : %.2fC = %.2fF = %.2fK\n",p->c,p->f,p->k);
}