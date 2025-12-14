/* ==================================== Include    =================================== */
#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

/* ==================================== Functions and procedures =================================== */

T_liste creer_liste(){
    return NULL;
}

void ajout_entete_liste(T_liste * l, int element){
    T_liste liste = malloc(sizeof(struct list));
    liste->elt = element;
    liste->svt = *l;
    *l = liste;
}

T_liste ajouter_entete_fonc(T_liste * l, int element){
    T_liste liste = malloc(sizeof(struct list));
    liste->elt = element;
    liste->svt = *l;
    return liste;
}
void afficher_liste(T_liste * l){
    T_liste p = *l;
    while(p != NULL){
        printf("%d -> ", p->elt);
        p = p->svt;
    }
    printf("NULL\n");

}

void fafficher_dir_liste(T_liste * l){
    T_liste p = *l;
    if (p == NULL) printf("NULL\n");
    else {
        printf("%d -> ", p->elt);
        fafficher_dir_liste(&(p->svt));
    }
}

void fafficher_inv_liste(T_liste * l){
    T_liste p = *l;
    if (p == NULL) printf("NULL");
    else {
        fafficher_inv_liste(&(p->svt));
        printf(" <- %d", p->elt);
    }
}

void inv_mis_liste(T_liste * l){
    T_liste p = *l;
    while ((p->svt)!= NULL){
        p = p->svt;
    }
    T_liste q = p;
    while(q != *l){
        T_liste r = *l;
        while(r->svt != q){
            r = r->svt;
        }
        q->svt = r;
        q = r;
    }
    q->svt = NULL;
    *l = p;
}

T_liste inv_fonc_liste(T_liste l){
    T_liste new = creer_liste();
    T_liste p = l;
    while(p != NULL){
        ajout_entete_liste(&new, p->elt);
        p = p->svt; 
    }
    return new;
}

int long_env(T_liste l){
    if(l == NULL){
        return 0;
    }
    return(1 + long_env(l->svt));
}

int long_ter(T_liste l, int aux){
    if(l == NULL){
        return aux;
    }
    return(long_ter(l->svt, aux+1));
}

T_liste inversion_rec_env(T_liste l, T_liste q){
    if(l == NULL){
        return q;
    }
    ajout_entete_liste(&q, l->elt);
    return inversion_rec_env(l->svt, q);
}

T_liste inversion_rec_term(T_liste l, T_liste q){
    if(l == NULL){
        return q;
    }
    return inversion_rec_term(l->svt, ajouter_entete_fonc(&q, l->elt));
}   

void liberer_liste(T_liste * l){
    T_liste p =*l;
    while(p != NULL){
        T_liste q = p;
        p = p->svt;
        free(q);
    }
}

int max(int a, int b){
    if(a<b){
        return b;
    }
    return a;
}

int max_env(T_liste l){
    if(l->svt == NULL){
        return l->elt; 
    }
    return max((l->elt), max_env(l->svt));
}

int max_ter(T_liste l,int aux){
    if(l->svt == NULL){
        return max(l->elt , aux);
    }
    return max_ter(l->svt, max(aux, l->elt));
}



#ifdef poulet

int main(void){
    int aa = 512;
    int b = 45;

    T_liste a = creer_liste();
    ajout_entete_liste(&a, aa);
    afficher_liste(&a);

    T_liste LISTE = ajouter_entete_fonc(&a, b);
    fafficher_dir_liste(&LISTE);

    T_liste F = inversion_rec_term(LISTE, NULL);
    fafficher_dir_liste(&F);
    printf("%d\n", max_ter(F, F->elt));

    printf("\n");
    return 1; 

}
#endif