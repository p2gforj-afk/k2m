#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "liste.h"

#define mod 9

typedef struct hachage T_ht;
struct hachage{
    T_liste * l;
    int n;
};

void create_ht(T_ht * pht, int k){
    pht->n = k;
    pht->l = malloc(k*sizeof(T_liste));
}
void init(T_ht * ht){
    for(int i = 0; i<ht->n; i++){
        ht->l[i] = NULL;
    }
}
void insertion(T_ht * ht, int cle){
    int m = cle%ht->n;
    T_liste new = malloc(sizeof(*new));
    new->elt = cle;
    new->svt = ht->l[m];
    ht->l[m] = new;
}

bool recherche(T_ht * ht, unsigned int cle){
    int m = cle%ht->n;
    T_liste  p = ht->l[m];
    while (p != NULL){
        if (p->elt == cle)
            return true;
        p = p->svt;
    }
    return false;
}

int main(void){
    T_ht TABLE;
    create_ht(&TABLE, mod);
    init(&TABLE);

    insertion(&TABLE, 10);
        insertion(&TABLE, 17);
            insertion(&TABLE, 12);
                insertion(&TABLE, 30);
                    insertion(&TABLE, 20);
                        insertion(&TABLE, 15);
                            insertion(&TABLE, 19);
                                insertion(&TABLE, 28);
                                    insertion(&TABLE, 5);


    if (recherche(&TABLE, 17))
        printf("ca");
    if (!recherche(&TABLE, 42))
        printf(" marche \n");
    
    for (int i = 0; i<mod; i++){
        printf("%d. ",i);
        T_liste p = TABLE.l[i];
        while (p!=NULL){
            printf("%d",p->elt);
            if (p->svt != NULL)
                printf(" -> ");
            p = p->svt;
        }
        printf("\n");
    }
    return 0;
}