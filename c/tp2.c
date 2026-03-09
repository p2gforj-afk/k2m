#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

#define BS 30

int main(int argc, char * argv[]){
    if (argc < 2) {
        printf("ya pas de mot la enfaite sinje\n");
        return EXIT_FAILURE;
    }
    bool T = true;
    int j = 0;
    int len;
    char mot[BS];
    sscanf(argv[1],"%s",mot);
    len = strlen(mot);
    while(T && j<(len/2)){
        if(tolower(mot[j]) == tolower(mot[len - j - 1])) j++;
        else T = false;
    }
    if(T == true) printf("%s est un mot palindrome.\n",mot);
    else printf("%s n'est pas un mot palindrome.\n",mot);
    return EXIT_SUCCESS;
}