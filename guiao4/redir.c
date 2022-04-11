#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

	int fde, fds;
	char ** exec_args = argv + 1;
	if (strcmp(argv[1],"-i") == 0){
		fde = open(argv[2],O_RDONLY);
		dup2(fde,0);
		exec_args = exec_args + 2;
	}
	if (strcmp(argv[1],"-o") == 0){
		fds = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY, 0666);
		dup2(fds,1);
		exec_args = exec_args + 2;
	}
	

	if (strcmp(argv[3],"-i") == 0){
		fde = open(argv[4],O_RDONLY);
		dup2(fde,0);
		exec_args = exec_args + 2;
	}
	if (strcmp(argv[3],"-o") == 0){
		fds = open(argv[4],O_CREAT | O_TRUNC | O_WRONLY, 0666);
		dup2(fds,1);
		exec_args = exec_args + 2;
	}

	close(fde);
	close(fds);

	if(fork() == 0){
        execvp(exec_args[0], exec_args);
        _exit(0);
    
    }else{
    
        wait(NULL);
    
    }



	return 0;
}