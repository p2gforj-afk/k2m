#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct snode Tnode;
typedef Tnode * TTrie;
// strucutre noeud
struct snode{
    char val;
    bool m;
    TTrie fi; // meme ligne
    TTrie fr; // DESCEND
};

void ajout(TTrie * figure2, char * mot){
    int len = strlen(mot);
    if(len > 0){
        TTrie figure1 = * figure2;
        if(figure1 == NULL){
            figure1 = malloc(sizeof(Tnode));
            figure1->val = mot[0];
            TTrie p = figure1;
            for(int i = 1; i<len; i++){
                TTrie new = malloc(sizeof(Tnode));
                new->val = mot[i];
                p->fr = new;
                p->m = false;
                p->fi = NULL;
                p = p->fr;
            }
            p->fr = NULL;
            p->fi = NULL;
            p->m = true;

        }
        else if(figure1->val == mot[0]){
           ajout(&figure1->fr, mot + sizeof(char));
        }
        else if(figure1->fi != NULL && figure1->fi->val > mot[0] && figure1->val < mot[0]){
            TTrie temp1 = figure1->fi;
            figure1->fi = NULL;
            ajout(&figure1->fi, mot);
            figure1->fi->fi = temp1; 
        }
        else if(figure1->val > mot[0]){
            TTrie temp1 = figure1;
            figure1 = NULL;
            ajout(&figure1, mot);
            figure1->fi = temp1; 
        }
        else{
           ajout(&figure1->fi, mot);

        }
        * figure2 = figure1;
    }
}


void faffichage(TTrie * figure,int i){
    TTrie figure3 = * figure;
    if(figure3 != NULL){
        for (int k = 0; k < i; k++) {
            printf("         ");
        }
        printf("%c(%d)-> ",figure3->val,figure3->m);
        printf("\n");
        if (figure3->fr == NULL){
            if (i > 0) i--;
        }
        faffichage(&figure3->fi, i+1);
        faffichage(&figure3->fr, i);
    }
}

int main(void){
    TTrie figure_folle = NULL;
    ajout(&figure_folle, "la");
    ajout(&figure_folle, "ma");
    ajout(&figure_folle, "me");
    ajout(&figure_folle, "mai");
    ajout(&figure_folle, "male");
    ajout(&figure_folle, "mat");
    ajout(&figure_folle, "mais");
    ajout(&figure_folle, "main");
    faffichage(&figure_folle, 0);
    printf("\n");
    return 0;
}