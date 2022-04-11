#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
	// abrir ficheiro etc/paswd
	int ifd = open("/etc/passwd",O_RDONLY);

	// abrir ficheiro saida.txt
	int ofd = open("saida.txt",O_CREAT | O_TRUNC | O_WRONLY,0644);
	
	// abrir ficheiro erros.txt
	int efd = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0644);

	dup2(ifd,0);
	dup2(ofd,1);
	dup2(efd,2);

	close(ifd);
	close(ofd);
	close(efd);

	if (fork() == 0){
		execlp("wc","wc",NULL);
		_exit(1);
	}

	int status;
	wait(&status);

	return 0;
}