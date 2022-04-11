#include <unistd.h>

#define MAX 100


// escrevo no teclado o pai le e manda ao filho pelo pipe e o filho imprime
// no teclado o que recebeu
int main (int argc, char * argv[]){

	int p[2];
	pipe(p);
	int l;
	char buf[MAX];
	//getchar();

	if (fork() == 0){
		// codigo filho
		close(p[1]);

		l = read(p[0],buf,MAX);
		write(1,buf,l);
	}
	else {
		//codigo pai
		close(p[0]);

		l = read(0,buf,MAX);
		sleep(8);
		write(p[1],buf,l);

	}



	return 0;
}