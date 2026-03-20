#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
  shm_unlink("compteur");
  exit(EXIT_SUCCESS);
}  