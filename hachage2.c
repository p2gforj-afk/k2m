#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define taille 11

/*===== Types =====*/
typedef struct _elmt{
    bool est_vide; /*< marque une entree vide*/
    int clef; /*< la clef de l'element*/
    char elt; /*< l'element lui-meme represente ici par un caractere*/
} elmt;

typedef elmt *hashtable;

/*===== Fucntions =====*/
void start(hashtable * ptab, unsigned int nb_cases){ // creation et initialisation de la table
    *ptab = malloc(nb_cases*sizeof(elmt));
    for (int i=0; i<nb_cases;i++)
        (*ptab)[i].est_vide = true;
}
void insert_elt(hashtable tab, elmt e){ //insertion de l'element dans la table
    int e1 = (e.clef) % 10;
    int e2 = (e.clef/10) % 10;
    int e3 = (e.clef/100) % 10;
    int e4 = (e.clef/1000) % 10;
    int h1 = (e4 + e3) % taille;
    int h2 = ((e2+e1)%(taille-2))+1;
    printf("\n(%d,%c)     h1 = %d, h2 = %d\n", e.clef, e.elt,h1, h2);
    int p;
    int i = 0;
    do{
        p = (h1 + i*h2) % taille;
        printf("i = %d, p = %d\n" ,i,p);
        i++;
    } while(!tab[p].est_vide);
    tab[p].clef = e.clef;
    tab[p].elt = e.elt;
    tab[p].est_vide = false;
}
char recherche(hashtable tab, int clef){ // recherche de l'infromation associee a la clef
    for(int i = 0; i< taille; i++){
        if(!tab[i].est_vide)
            if(tab[i].clef == clef)
                return tab[i].elt;
    }
    return '\0';
}

int main(void){
    hashtable HASH;
    start(&HASH,taille);

    elmt e1;
    e1.clef = 1015;
    e1.elt = 'a';

    elmt e2;
    e2.clef = 2192;
    e2.elt = 'z';

    elmt e3;
    e3.clef = 1419;
    e3.elt = 'a';
        
    elmt e4;
    e4.clef = 3517;
    e4.elt = 'b';
        
    elmt e5;
    e5.clef = 1180;
    e5.elt = 'c';
        
    elmt e6;
    e6.clef = 4186;
    e6.elt = 'x';
  
    elmt e7;
    e7.clef = 3538;
    e7.elt = 'g';

    elmt e8;
    e8.clef = 8508;
    e8.elt = 'h';

   insert_elt(HASH,e1);
        insert_elt(HASH,e2);
            insert_elt(HASH,e3);
                insert_elt(HASH,e4);
                    insert_elt(HASH,e5);
                        insert_elt(HASH,e6);
                            insert_elt(HASH,e7);
                                insert_elt(HASH,e8);
                                
    printf("\n%c , %c\n",recherche(HASH, 4186), recherche(HASH, 9999));
    return 0;
}