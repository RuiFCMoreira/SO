#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h>   

#define MAX 100


ssize_t readln(int fildes, void *buf, size_t nbyte){
    ssize_t res = 0;
    int i = 0;

    while(i<nbyte && (res = read(fildes,&buf[i],1)) > 0 ){
        if( ((char*) buf)[i]=='\n' ){ return i+1; }
        i += res;
    }
    return i;
}

// escrevo no teclado o pai le e manda ao filho pelo pipe e o filho imprime
// no teclado o que recebeu
int main (int argc, char * argv[]){
	int p[2];
	if (pipe(p) == -1){
		perror("pipe error");
        return -1;
	}

	int l;
	char buf[MAX];
	int pid;
	int status;
	int res = 0;
	//getchar();

	if ((pid = fork()) == 0){
		// codigo filho
		close(p[1]);
		dup2(p[0],0);
		close(p[0]);
		res = execlp("wc","wc",NULL);
		_exit(0);
	}
	else if (pid == -1){
			perror("fork");
			return -1;
		} else {
			//codigo pai
			close(p[0]);

		
			while((l = read(0,buf,MAX)) > 0)
				write(p[1],buf,l);

			close(p[1]);
			wait(&status);

			if(WIFEXITED(status)){
                printf("PAI: filho terminou com %d\n",WEXITSTATUS(status));
            }
		}



	return 0;
}
