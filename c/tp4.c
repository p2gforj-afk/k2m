#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<time.h>

#define col 205
#define lig 55
#define xmax 10000

void initialise(char p[lig][col]);
void affiche(char p[lig][col]);
void dessine (char p[lig][col]);
float C(float);

int main(void){
    char plan[lig][col];
    initialise(plan);
    dessine(plan);
    affiche(plan);
    return 0;
}

void initialise(char p[lig][col]){
    for(int i = 0; i < lig; i++){
        for(int j = 0; j < col - 1; j++){
            p[i][j] = ' ';
        }
        p[i][col - 1] = '\0';
    }

    p[0][col/2] = '^';
    p[lig/2][col - 2] = '>'; 
    for(int i = 1; i < lig - 1; i++) p[i][col/2] = '|';
    for(int j = 0; j < col - 2; j++) p[lig/2][j] = '-';
}


void affiche(char p[lig][col]){
        for(int i=0;i<lig;i++) printf("%s\n",p[i]);
}

void dessine (char p[lig][col]){
    float pas = 2 * (xmax/(col - 2)); // pas entre chaque appel a la fonction, on fait 80 appel dans la loop
    float pas2 = (C(xmax)-C(-xmax))/lig; // affreux pas entre chaque ptn de ligne
    float poulet;
    for(int j = 0; j< col -1; j++){
        poulet = C(-xmax + j*pas);
        for(int i = lig-1; i>=0; i--){
            if(poulet >= (pas2*(lig-1-i) + C(-xmax)) && poulet < (pas2*(lig-i) + C(-xmax))) p[i][j] = '*';
        }
    }
}

float C(float x){
    return (x*x*x)/2 - 6*x*x - 13*x + 20;
}