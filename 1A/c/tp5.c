#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Mauvais nombre d’arguments.\n");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("Impossible d'ouvrir le fichier.\n");
        return EXIT_FAILURE;
    }
    bool espace_avant = true;
    int ligne = 0, mot = 0, caractere = 0, current;
    while((current = fgetc(file)) != EOF){
        caractere = caractere + 1;
        if (current == '\n') ligne = ligne + 1;
        if (isspace(current)) espace_avant = true;
        else if(espace_avant){
            mot = mot + 1;
            espace_avant = false;
        }
    }
    fclose(file);
    printf("%d %d %d %s\n",ligne,mot,caractere,argv[1]);
    return EXIT_SUCCESS;
}