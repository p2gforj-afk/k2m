
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int tube[2];
  char buffer1;
  char buffer2;

  /* Creation du tube */
  if (pipe(tube) != 0) {
    printf("creation du tube impossible");
    return EXIT_FAILURE;
  }

  pid_t pid_fils_1 = -1; // valeur de retour du fork
  pid_t pid_fils_2 = -1; // retour fork fils 2

  pid_fils_1 = fork();
  if (pid_fils_1 == -1) { // pcb tout plein de soupe
    perror("Echec du fork \n");
    exit(EXIT_FAILURE);
  }

  if (pid_fils_1 == 0) { // code du fils 1
    close(tube[1]);
    while (read(tube[0], &buffer1, 1) > 0) {
      printf("%c", buffer1);
    }
    exit(EXIT_SUCCESS);
  } else {
    pid_fils_2 = fork();
    if (pid_fils_2 == -1) { // pcb tout plein de soupe
      perror("Echec du fork \n");
      exit(EXIT_FAILURE);
    }

    if (pid_fils_2 == 0) { // code du fils 2
      close(tube[1]);
      while (read(tube[0], &buffer2, 1) > 0) {
        printf("%c", buffer2);
      }
      exit(EXIT_SUCCESS);
    } else { // code du pere
      fprintf(stdout,
              "Ecriture de \"un texte dans le tube\" (21 char + \'\\0\')\n");
      write(tube[1], "un texte dans le tube", 22);
      close(tube[1]);
      wait(NULL);
      wait(NULL);
      printf("\n");
    }
  }
  return 0;
}
