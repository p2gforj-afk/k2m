
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
	pid_t pids_fils1 = -1;
	char *param[argc];
	for(int i = 1; i<argc;i++){
		param[i-1] = argv[i];
	}
	param[argc-1] = (char *)NULL;
	
	pids_fils1 = fork();
	if (pids_fils1 == 0){
		execvp(argv[1], param);
		exit(EXIT_FAILURE); 
	}

	wait(NULL);
	execvp(argv[1], param);
	exit(EXIT_FAILURE);
}
