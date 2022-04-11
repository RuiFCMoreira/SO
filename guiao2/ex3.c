#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){


	for (int i = 1 ; i <= 10; i++){
		if (fork() == 0){
			printf("[child nº%d] child pid : %d\n",i,getpid());
			printf("[child nº%d] parent pid: %d\n",i,getppid());
			_exit(i);
		}
		else{
			int status;
			int terminated_pid = wait(&status); 
			printf("[parent] child pid %d, exit code: %d\n", terminated_pid,WEXITSTATUS(status));
		}
	}

	return 0;
}