#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>

int main(void)
{
    int fork_return_value; 
    int fork_return_value2;

    do{
        fork_return_value = fork();
        fork_return_value2 = fork();
        if (fork_return_value == 0){
            printf("%d\n",getpid());
        }
        if (fork_return_value2 == 0){
            printf("%d\n", getpid());
        }
    } while(1);
}




