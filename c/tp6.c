#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<time.h>

// #define write

int main(void){
    FILE * file;
    float temp;
    char filename[21];
    printf("Nom du fichier(20 caracteres max) : ");
    scanf("%s", filename);
#ifdef write
    file = fopen(filename, "w");
    if (file != NULL){
        printf("Temperature Celsius a enregistrer : ");
        while (scanf("%f",&temp) == 1) {
            fwrite(&temp, sizeof(float), 1, file);
            printf("Temperature Celsius a enregistrer : ");
        }
        fclose(file);
    }   
#else
    file = fopen(filename, "r");
    int a,b;
    if(file != NULL){
        printf("Intervalle de lecture (DEBUT FIN) : ");
        scanf("%d %d",&a,&b);
        if(b < a || a < 1){
            printf("Intervalle non valide.");
            return EXIT_FAILURE;
        }
        fseek(file, (a-1) * sizeof(float),SEEK_SET);
        for(; a<=b; a++){
            if (fread(&temp, sizeof(float),1,file) == 1) printf("%.6f ",temp);
        }
    }
#endif    
    return EXIT_SUCCESS;
}