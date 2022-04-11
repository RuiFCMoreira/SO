#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
	// criarr processo filho
	int child_pid;
	if ((child_pid = fork()) == 0){
		// se filho 
		// - imprimir PID 
		printf("[child] child pid : %d\n",getpid());
		// - imprimir PID do processo pai
		printf("[child] parent pid: %d\n",getppid());

		_exit(5);
	}else {
		// se pai
		// - imprimir PID 
		printf("[parent] pid : %d\n",getpid());
		
		//  imprimir PID do pai
		printf("[parent] parent pid: %d\n",getppid());	

		// - imprimir PID do processo filho
		printf("[parent] child pid: %d\n",child_pid); 

		int status;
		int terminated_pid = wait(&status); 
		printf("[parent] child pid %d, exit code: %d\n", terminated_pid,WEXITSTATUS(status));
	}


	return 0;
}