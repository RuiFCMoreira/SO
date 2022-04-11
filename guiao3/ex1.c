#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// exercicios 1 e 2
int main(int argc, char * argv[]){
	char * exec_args[] = {"ls","-l",NULL};
	if (fork() == 0){
		//execl("/bin/ls","ls","-l",NULL);
		execv("/bin/ls",exec_args);
		perror("exec");
		_exit(0);
	}

	int status;
	wait(&status);
	printf("fork + exec done\n");
	return 0;
}