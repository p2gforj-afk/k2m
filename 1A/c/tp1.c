#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define BUFFER_SIZE 30
// #define poulet

int main(void){
#ifdef poulet
    char buffer[BUFFER_SIZE];
    float f1,f2 ;
    char op;

    printf("Operande 1 : ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer,"%f",&f1);

    printf("Operande 2 : ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer,"%f",&f2);

    printf("Operation (+,-,*,/) : ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer,"%c",&op);

        if(op == '*'){
            printf("%f %c %f = %f \n",f1,op,f2,f1*f2);
            return EXIT_SUCCESS;
        }
        else if(op == '+'){
            printf("%f %c %f = %f \n",f1,op,f2,f1+f2);
            return EXIT_SUCCESS;
        }
        else if(op == '/'){
            printf("%f %c %f = %f \n",f1,op,f2,f1/f2);
            return EXIT_SUCCESS;
        }
        else if(op == '-'){
            printf("%f %c %f = %f \n",f1,op,f2,f1-f2);
            return EXIT_SUCCESS;
        }
        else return EXIT_FAILURE;

#else
    char buffer[50];
    srand(time(NULL));
    int vic = rand()%100 + 1;
    int sol = 0;
    while(sol != vic){
        printf("Entrez un nombre entre 1 et 100 : ");
        fgets(buffer, 50, stdin);
        if(sscanf(buffer, "%d", &sol) != 1) {
            printf("Saisie invalide !\n");
            continue;
        }
        if(sol<vic) printf("Plus !\n");
        else if(sol>vic) printf("Moins !\n");     
    }
    printf("Gagne !\n");
    return EXIT_SUCCESS;

#endif
}