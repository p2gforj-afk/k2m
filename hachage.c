#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "liste.h"


typedef struct hachage T_ht;
struct hachage{
    T_liste * l;
    int n;
};

void create_ht(T_ht * pht, int k){
    pht->n = k;
    pht->l = malloc(k*sizeof(T_liste ));
}
void init(T_ht * ht, int k){
    for(int i = 0; i<k; i++){
        ht->l[i] = NULL;
    }
}
void insertion(T_ht * ht, int k, int cle){
    int m = cle%k;
    T_liste new = malloc(sizeof(*new));
    new->elt = cle;
    new->svt = ht->l[m];
    ht->l[m] = new;
}

bool recherche(T_ht * ht, unsigned int k, unsigned int cle){
    int m = cle%k;
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
    create_ht(&TABLE, 9);
    init(&TABLE, 9);
    insertion(&TABLE, 9, 5);

    if (recherche(&TABLE, 9, 28))
        printf("on est laaaa\n");
    else
        printf("on est pas laaaa\n");

    if (recherche(&TABLE, 9, 5))
        printf("on est laaaa\n");
    else
        printf("on est pas laaaa\n");
    
    printf("%d", TABLE.l[5]->elt);
    return 0;
}