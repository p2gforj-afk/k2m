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
    else if (cmp > 0){
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
                if (strcmp(l->cur, mot) > 0){
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
                    l2 =(strcmp(l2->cur, mot) > 0) ? l2->l
                                                   : l2->r;
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

bool D_appartient_a (T_dico p, char * mot){
    if(p == NULL){
        return false;
    }
    int cmp = strcmp(p->mot, mot);
    if(cmp == 0){
        return true;
    }
    else if (cmp < 0){
        return(D_appartient_a(p->l, mot));
    }
    else {
        return(D_appartient_a(p->r, mot));
    }
} 
int D_hauteur(T_dico p){
    if (p == NULL){
        return -1;
    }
    return(D_hauteur(p->l) > D_hauteur(p->r)) ? 1 + D_hauteur(p->l)
                                              : 1 + D_hauteur(p->r);
}
void D_equilibre(T_dico * p){
    if (*p != NULL) 
        (*p)->eq = (D_hauteur((*p)->l) - D_hauteur((*p)->r));
}
void D_Rr(T_dico * p){
    T_dico  aux = (*p)->l;
    (*p)->l = aux->r;
    aux->r = *p;
    *p = aux;
}
void D_Lr(T_dico * p){
    T_dico aux = (*p)->r;
    (*p)->r = aux->l;
    aux->l = *p;
    *p = aux;
}
void D_LRr(T_dico *p){
    D_Lr(&(*p)->l);
    D_Rr(&(*p));
}
void D_RLr(T_dico *p){
    D_Rr(&(*p)->r);
    D_Lr(&(*p));
}

void D_ajout_entree (T_dico * p, char * mot, T_syn s){
    if(!D_appartient_a(*p,mot)){
        if (*p == NULL){
            *p = malloc(sizeof(**p));
            (*p)->mot = mot;
            (*p)->s = s;
            (*p)->r = NULL;
            (*p)->l = NULL;

        }
        else{
            T_dico l = *p;
            int menma = 0;
            while(!menma){
                if (strcmp(l->mot, mot) > 0){
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
            T_dico new = malloc(sizeof(*new));
            new->mot = mot;
            new->s = s;
            new->l = NULL;
            new->r = NULL;
            if(menma == 1){
                l->l = new;
            }
            else{
                l->r = new;
            }
            T_dico l2;
            T_dico elec = *p;
            while(elec != NULL){
                l2 = *p;
                elec = NULL;
                while(l2 != new){
                    D_equilibre(&l2);
                    if(l2->eq > 1 || l2->eq < -1){
                        elec = l2;
                    }
                    l2 =(strcmp(l2->mot, mot) > 0) ? l2->l
                                                   : l2->r;
                }
                if(elec != NULL){
                    if (elec->eq == 2)
                        (D_hauteur(elec->r) > D_hauteur(elec->l))
                            ? D_LRr(&elec)
                            : D_Rr(&elec);
                    else
                        (D_hauteur(elec->l) > D_hauteur(elec->r))
                            ? D_RLr(&elec)
                            : D_Lr(&elec);
                }
            }
        }
    }
}

void charger_dico(T_dico *p){
//4h pour ca + debug
}

T_syn liste_syn(T_dico p,char * mot){
    while(p != NULL) {
        int cmp = strcmp(p->mot,mot);
        if (cmp == 0)
            return p->s;
        p = (cmp>0) ? p->l
                    : p->r;
    }
    return NULL;
}

bool est_synonyme_de(T_dico p, char*mot1, char*mot2){
    return appartient_a(liste_syn(p,mot1),mot2);
}

void scr(T_dico p,T_syn s1,char*mot2, T_syn * l){
    if(s1 == NULL)
        return;
    if(est_synonyme_de(p,s1->cur,mot2))
        ajout_synonyme(l,s1->cur);
    scr(p,s1->l,mot2,l);
    scr(p,s1->r,mot2,l);
}

T_syn synonymes_communs(T_dico p, char*mot1, char*mot2){
    T_syn ussr = NULL;
    T_syn s1 = liste_syn(p,mot1);
    if(s1 == NULL)
        return ussr;
    scr(p,s1,mot2,&ussr);
    return ussr;
}

void fafficher(T_syn p){
    if(p == NULL)
        return;
    printf("%s\n",p->cur);
    fafficher(p->l);
    fafficher(p->r);
}
int main(void){
    T_dico DICO = NULL; 

    fafficher(liste_syn(DICO,"savon"));
    if (est_synonyme_de(DICO,"dragon","argoulet"))
        printf("BO LE SYNONYME\n");
    fafficher(synonymes_communs(DICO,"rouge","jaune"));
    return 0;
}