#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct sdd_synonymes * T_syn;
struct sdd_synonymes{
    char * cur; // synonyme actuel
    int eq;
    T_syn l; //sag
    T_syn r; //sad

};

void S_init_vide(T_syn * p){
    *p = NULL;
}

bool appartient_a (T_syn p, char * mot){
    if(p == NULL){
        return false;
    }
    int cmp = strcmp(p->cur, mot);
    if(cmp == 0){
        return true;
    }
    else if (cmp < 0){
        return(appartient_a(p->l, mot));
    }
    else {
        return(appartient_a(p->r, mot));
    }
} 

int hauteur(T_syn p){
    if (p == NULL){
        return -1;
    }
    return(hauteur(p->l) > hauteur(p->r)) ? 1 + hauteur(p->l)
                                          : 1 + hauteur(p->r);
}

void equilibre(T_syn * p){
    if (*p != NULL) 
        (*p)->eq = (hauteur((*p)->l) - hauteur((*p)->r));
}

void Rr(T_syn * p){
    T_syn  aux = (*p)->l;
    (*p)->l = aux->r;
    aux->r = *p;
    *p = aux;
}
void Lr(T_syn * p){
    T_syn aux = (*p)->r;
    (*p)->r = aux->l;
    aux->l = *p;
    *p = aux;
}
void LRr(T_syn *p){
    Lr(&(*p)->l);
    Rr(&(*p));
}
void RLr(T_syn *p){
    Rr(&(*p)->r);
    Lr(&(*p));
}


void ajout_synonyme (T_syn * p, char * mot){
    if(!appartient_a(*p,mot)){
        if (*p == NULL){
            *p = malloc(sizeof(**p));
            (*p)->cur = mot;
            (*p)->r = NULL;
            (*p)->l = NULL;

        }
        else{
            T_syn l = *p;
            int menma = 0;
            while(!menma){
                if (strcmp(l->cur, mot) < 0){
                    if (l->l == NULL){
                        menma = 1;
                    }
                    else{
                    l = l->l;
                    }
                }
                else {
                    if (l->r == NULL){
                        menma = 0xFF;
                    }
                    else{
                    l = l->r;
                    }
                }   
            }
            T_syn new = malloc(sizeof(*new));
            new->cur = mot;
            new->l = NULL;
            new->r = NULL;
            if(menma == 1){
                l->l = new;
            }
            else{
                l->r = new;
            }
            T_syn l2;
            T_syn elec = *p;
            while(elec != NULL){
                l2 = *p;
                elec = NULL;
                while(l2 != new){
                    equilibre(&l2);
                    if(l2->eq > 1 || l2->eq < -1){
                        elec = l2;
                    }
                    if (strcmp(l2->cur, mot) < 0){
                        l2 = l2->l;
                    }
                    else{
                        l2 = l2->r;
                    }
                }
                if(elec != NULL){
                    if (elec->eq == 2)
                        (hauteur(elec->r) > hauteur(elec->l))
                            ? LRr(&elec)
                            : Rr(&elec);
                    else
                        (hauteur(elec->l) > hauteur(elec->r))
                            ? RLr(&elec)
                            : Lr(&elec);
                }
            }
        }
    }
}

typedef struct sdd_dico * T_dico;
struct sdd_dico{
    char * mot; 
    int eq;
    T_syn s;
    T_dico l; //sag
    T_dico r; //sad
};

void D_init_vide(T_dico *p){
        *p = NULL;
}

int main(void){
    return 0;
}