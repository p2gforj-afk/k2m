
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 5

unsigned int result;

void MyG(int sig){
    printf("Le resultat etait %d, essaie encore\n",result);
    kill(getpid(),SIGTERM);
}

int main(int argc, char* argv[]){
    signal(SIGINT,MyG);
    signal(SIGALRM, MyG);
    unsigned int tempsReponse;
    if (sscanf(argv[1],"%u", &tempsReponse) == 0){
        printf("Error in argument\n");
        return EXIT_FAILURE;
    }
    char buffer[BUFFER_SIZE];
    srand(time(NULL)*getpid()*rand());
    unsigned int n1 = rand() % 13;
    unsigned int n2 = rand() % 13;
    result = n1*n2;
    printf("%d x %d = ??\n", n1, n2);
    if (tempsReponse != 0){
        alarm(tempsReponse);
        unsigned int answer;
        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer,"%u",&answer);
        if (answer == result){
            printf("%d est la bonne reponse, felicitation pd\n", result);
            return EXIT_SUCCESS;
        }
        else{
            printf("T'es mauvais... tu etait a %d unite(s) de ne pas etre mauvais\n", abs(result - answer));
            return EXIT_FAILURE;
        }
    }
    else printf("Le resultat etait %d, essaie encore\n",result);
    return EXIT_FAILURE;
}

