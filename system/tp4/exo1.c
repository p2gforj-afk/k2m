
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int tube[2];
  char buffer;
  char tab[40];

  /* Creation du tube */
  if (pipe(tube) != 0) {
    printf("creation du tube impossible");
    return EXIT_FAILURE;
  }

  pid_t pid_fils = -1;
  pid_fils = fork();
  if (pid_fils == -1) { // pcb tout plein de soupe
    perror("Echec du fork \n");
    exit(EXIT_FAILURE);
  }

  if (pid_fils == 0) { // code du fils
    int i = 0;
    bool flag = true;
    while (flag && (read(tube[0], &tab[i], 1) != 0)) {
      if (tab[i] == '\0') {
        flag = false;
      }
      i++;
    }
    fprintf(stdout, "%s\n", tab);
  } else { // code du pere
    fprintf(stdout,
            "Ecriture de \"un texte dans le tube\" (21 char + \'\\0\')\n");
    sleep(10);
    write(tube[1], "un texte dans le tube", 22);
    wait(NULL);
  }
  return 0;
}
