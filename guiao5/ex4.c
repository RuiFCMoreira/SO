#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h>   

#define MAX 100


int main (int argc, char * argv[]){
	int p[2];
	if (pipe(p) == -1){
		perror("pipe error");
        return -1;
	}

	int l;
	
	int pid;
	int status;
	int res = 0;
	//getchar();

	if ((pid = fork()) == 0){
		// codigo filho
		close(p[1]);
		dup2(p[0],0);
		close(p[0]);
		res = execlp("wc","wc","-l",NULL);
		_exit(0);
	}
	else if (pid == -1){
			perror("fork");
			return -1;
		} else {
			//codigo pai
			close(p[0]);

			dup2(p[1],1);
			close(p[1]);
			res = execlp("ls","ls","/etc",NULL);
			close(p[1]);
		}



	return 0;
}
