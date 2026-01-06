#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct sdd_synonymes * T_syn;
struct sdd_synonymes{
    char * cur; // synonyme actuel
    int eq;     // hauteur du noeud
    T_syn l;    // sous-arbre gauche
    T_syn r;    // sous-arbre droit
};

typedef struct sdd_dico * T_dico;
struct sdd_dico{
    char * mot; 
    int eq;     // hauteur du noeud
    T_syn s;    // arbre des synonymes
    T_dico l;   // sous-arbre gauche
    T_dico r;   // sous-arbre droit
};

// ============ FONCTIONS POUR T_syn ============

void S_init_vide(T_syn * p){
    *p = NULL;
}

bool appartient_a(T_syn p, char * mot){
    if(p == NULL){
        return false;
    }
    int cmp = strcmp(p->cur, mot);
    if(cmp == 0){
        return true;
    }
    else if (cmp > 0){
        return appartient_a(p->l, mot);
    }
    else {
        return appartient_a(p->r, mot);
    }
} 

int hauteur(T_syn p){
    return (p == NULL) ? -1 : p->eq;
}

void maj_hauteur(T_syn p){
    if (p != NULL) {
        int hl = hauteur(p->l);
        int hr = hauteur(p->r);
        p->eq = 1 + (hl > hr ? hl : hr);
    }
}

int facteur_equilibre(T_syn p){
    return (p == NULL) ? 0 : hauteur(p->l) - hauteur(p->r);
}

T_syn Rr(T_syn p){
    T_syn aux = p->l;
    p->l = aux->r;
    aux->r = p;
    maj_hauteur(p);
    maj_hauteur(aux);
    return aux;
}

T_syn Lr(T_syn p){
    T_syn aux = p->r;
    p->r = aux->l;
    aux->l = p;
    maj_hauteur(p);
    maj_hauteur(aux);
    return aux;
}

T_syn equilibrer(T_syn p){
    if (p == NULL) return NULL;
    
    maj_hauteur(p);
    int fe = facteur_equilibre(p);
    
    // Cas gauche-gauche
    if (fe > 1 && facteur_equilibre(p->l) >= 0)
        return Rr(p);
    
    // Cas gauche-droite
    if (fe > 1 && facteur_equilibre(p->l) < 0){
        p->l = Lr(p->l);
        return Rr(p);
    }
    
    // Cas droite-droite
    if (fe < -1 && facteur_equilibre(p->r) <= 0)
        return Lr(p);
    
    // Cas droite-gauche
    if (fe < -1 && facteur_equilibre(p->r) > 0){
        p->r = Rr(p->r);
        return Lr(p);
    }
    
    return p;
}

T_syn ajout_synonyme_rec(T_syn p, char * mot){
    // Cas de base : arbre vide
    if (p == NULL){
        T_syn new = malloc(sizeof(*new));
        new->cur = mot;
        new->l = NULL;
        new->r = NULL;
        new->eq = 0;
        return new;
    }
    
    int cmp = strcmp(p->cur, mot);
    
    // Mot déjà présent
    if (cmp == 0)
        return p;
    
    // Insertion récursive
    if (cmp > 0)
        p->l = ajout_synonyme_rec(p->l, mot);
    else
        p->r = ajout_synonyme_rec(p->r, mot);
    
    // Équilibrage
    return equilibrer(p);
}

void ajout_synonyme(T_syn * p, char * mot){
    *p = ajout_synonyme_rec(*p, mot);
}

// ============ FONCTIONS POUR T_dico ============

void D_init_vide(T_dico *p){
    *p = NULL;
}

bool D_appartient_a(T_dico p, char * mot){
    if(p == NULL){
        return false;
    }
    int cmp = strcmp(p->mot, mot);
    if(cmp == 0){
        return true;
    }
    else if (cmp > 0){
        return D_appartient_a(p->l, mot);
    }
    else {
        return D_appartient_a(p->r, mot);
    }
} 

int D_hauteur(T_dico p){
    return (p == NULL) ? -1 : p->eq;
}

void D_maj_hauteur(T_dico p){
    if (p != NULL) {
        int hl = D_hauteur(p->l);
        int hr = D_hauteur(p->r);
        p->eq = 1 + (hl > hr ? hl : hr);
    }
}

int D_facteur_equilibre(T_dico p){
    return (p == NULL) ? 0 : D_hauteur(p->l) - D_hauteur(p->r);
}

T_dico D_Rr(T_dico p){
    T_dico aux = p->l;
    p->l = aux->r;
    aux->r = p;
    D_maj_hauteur(p);
    D_maj_hauteur(aux);
    return aux;
}

T_dico D_Lr(T_dico p){
    T_dico aux = p->r;
    p->r = aux->l;
    aux->l = p;
    D_maj_hauteur(p);
    D_maj_hauteur(aux);
    return aux;
}

T_dico D_equilibrer(T_dico p){
    if (p == NULL) return NULL;
    
    D_maj_hauteur(p);
    int fe = D_facteur_equilibre(p);
    
    // Cas gauche-gauche
    if (fe > 1 && D_facteur_equilibre(p->l) >= 0)
        return D_Rr(p);
    
    // Cas gauche-droite
    if (fe > 1 && D_facteur_equilibre(p->l) < 0){
        p->l = D_Lr(p->l);
        return D_Rr(p);
    }
    
    // Cas droite-droite
    if (fe < -1 && D_facteur_equilibre(p->r) <= 0)
        return D_Lr(p);
    
    // Cas droite-gauche
    if (fe < -1 && D_facteur_equilibre(p->r) > 0){
        p->r = D_Rr(p->r);
        return D_Lr(p);
    }
    
    return p;
}

T_dico D_ajout_entree_rec(T_dico p, char * mot, T_syn s){
    // Cas de base : arbre vide
    if (p == NULL){
        T_dico new = malloc(sizeof(*new));
        new->mot = mot;
        new->s = s;
        new->l = NULL;
        new->r = NULL;
        new->eq = 0;
        return new;
    }
    
    int cmp = strcmp(p->mot, mot);
    
    // Mot déjà présent
    if (cmp == 0)
        return p;
    
    // Insertion récursive
    if (cmp > 0)
        p->l = D_ajout_entree_rec(p->l, mot, s);
    else
        p->r = D_ajout_entree_rec(p->r, mot, s);
    
    // Équilibrage
    return D_equilibrer(p);
}

void D_ajout_entree(T_dico * p, char * mot, T_syn s){
    *p = D_ajout_entree_rec(*p, mot, s);
}

// ============ CHARGEMENT DU DICTIONNAIRE ============

void charger_dico(T_dico *p){
    FILE *stream = fopen("base_synonymes.txt", "r"); 
    char s[100];
    char * mot = NULL;
    T_syn smot = NULL;
    int flag = 1; 
    
    if (stream != NULL) { 
        while (fgets(s, sizeof(s), stream) != NULL) {
            // Retirer le retour à la ligne
            s[strcspn(s, "\n")] = 0;
            
            if (strcmp(s, "N_ENT") != 0){
                if (flag){
                    // Allouer et copier le mot principal
                    mot = malloc(strlen(s) + 1);
                    strcpy(mot, s);
                    flag = 0;
                }
                else{
                    // Allouer et copier le synonyme
                    char * syn = malloc(strlen(s) + 1);
                    strcpy(syn, s);
                    ajout_synonyme(&smot, syn);
                }
            }
            else {
                // On a atteint N_ENT, ajouter l'entrée au dictionnaire
                if (mot != NULL) {
                    D_ajout_entree(p, mot, smot);
                }
                // Réinitialiser pour la prochaine entrée
                flag = 1;
                mot = NULL;
                smot = NULL;
            }
        }
        fclose(stream);
    } 
    else
        printf("il est ou le fichier...\n");
}

// ============ FONCTIONS UTILITAIRES ============

T_syn liste_syn(T_dico p, char * mot){
    while(p != NULL) {
        int cmp = strcmp(p->mot, mot);
        if (cmp == 0)
            return p->s;
        p = (cmp > 0) ? p->l : p->r;
    }
    return NULL;
}

bool est_synonyme_de(T_dico p, char*mot1, char*mot2){
    return appartient_a(liste_syn(p, mot1), mot2);
}

void scr(T_syn * u, T_syn u1, T_syn u2){
    if (u1 == NULL)
        return;
    char * mot = u1->cur;
    T_syn p = u2;
    while(p != NULL){
        int cmp = strcmp(p->cur, mot);
        if (cmp == 0){
            ajout_synonyme(u, mot);
            p = NULL;
        }
        else 
            p = (cmp > 0) ? p->l : p->r;
    }
    scr(u, u1->r, u2);
    scr(u, u1->l, u2);
}

T_syn synonymes_communs(T_dico p, char*mot1, char*mot2){
    T_syn ussr = NULL;
    T_syn s1 = liste_syn(p, mot1);
    T_syn s2 = liste_syn(p, mot2);
    scr(&ussr, s1, s2); 
    return ussr;
}

void fafficher(T_syn p){
    if(p == NULL)
        return;
    printf("%s\n", p->cur);
    fafficher(p->l);
    fafficher(p->r);
}

// ============ MAIN ============

void afficher_menu() {
    printf("\n=== DICTIONNAIRE DE SYNONYMES ===\n");
    printf("1. Afficher les synonymes d'un mot\n");
    printf("2. Tester si deux mots sont synonymes\n");
    printf("3. Trouver les synonymes communs de deux mots\n");
    printf("4. Quitter\n");
    printf("Votre choix : ");
}

int main(void){
    T_dico DICO = NULL; 
    printf("Chargement du dictionnaire...\n");
    charger_dico(&DICO);
    printf("Dictionnaire charge !\n");
    
    int choix;
    char mot1[100], mot2[100];
    
    do {
        afficher_menu();
        scanf("%d", &choix);
        getchar(); // consommer le \n
        
        switch(choix) {
            case 1:
                printf("Entrez un mot : ");
                fgets(mot1, 100, stdin);
                mot1[strcspn(mot1, "\n")] = 0;
                printf("\nSynonymes de '%s' :\n", mot1);
                fafficher(liste_syn(DICO, mot1));
                break;
                
            case 2:
                printf("Premier mot : ");
                fgets(mot1, 100, stdin);
                mot1[strcspn(mot1, "\n")] = 0;
                printf("Deuxieme mot : ");
                fgets(mot2, 100, stdin);
                mot2[strcspn(mot2, "\n")] = 0;
                
                if (est_synonyme_de(DICO, mot1, mot2))
                    printf("'%s' et '%s' sont synonymes !\n", mot1, mot2);
                else
                    printf("'%s' et '%s' ne sont PAS synonymes.\n", mot1, mot2);
                break;
                
            case 3:
                printf("Premier mot : ");
                fgets(mot1, 100, stdin);
                mot1[strcspn(mot1, "\n")] = 0;
                printf("Deuxieme mot : ");
                fgets(mot2, 100, stdin);
                mot2[strcspn(mot2, "\n")] = 0;
                
                printf("\nSynonymes communs :\n");
                fafficher(synonymes_communs(DICO, mot1, mot2));
                break;
                
            case 4:
                printf("Au revoir !\n");
                break;
                
            default:
                printf("Choix invalide !\n");
        }
    } while(choix != 4);
    
    return 0;
}