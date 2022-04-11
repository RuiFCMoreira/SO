#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
	// 1 imiprimir PID processo
	printf("child pid : %d\n",getpid());

	// 2. imprimir PID do pai
	printf("parent pid: %d\n",getppid());

	return 1;
}