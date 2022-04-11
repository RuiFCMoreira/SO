#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define MAX_BUF 1024

int mycp (int argc, char * argv[]){
	int fd_origem = open (argv[1],O_RDONLY);
	if (fd_origem < 0){
		perror ("erro abrir ficheiro");
		return -1;
	} 

	int fd_destino = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_destino < 0){
		perror ("erro criar ficheiro");
		return -1;
	} 

	int read_bytes = 0;
	int write_bytes = 0;
	char buffer[MAX_BUF];
	while ((read_bytes = read(fd_origem,buffer,MAX_BUF)) > 0){
		write_bytes += write(fd_destino,buffer,read_bytes);
	}

	close (fd_origem);
	close (fd_destino);
	return write_bytes;
}

void mycat (){
	int read_bytes = 0;
	
	char buffer[MAX_BUF];
	while ((read_bytes = read(0,buffer,MAX_BUF)) > 0){
		write(1,buffer,read_bytes);
	}

}


// EXERCICIO 3 E 4
// isto ou por static dentro das funçoes onde utilizamos isto
char file_buffer[100];
int next_pos = 0;
int last_read_bytes = 0; 

int readch(int fd,char * buf){
	// se nao tiver mais dados disponiveis -> ler bytes do ficheiro (disco)
	if (next_pos == last_read_bytes){
		
		int n_bytes = 0;
		if ((n_bytes = read(fd,file_buffer,100)) < 1){
			return 1;
		}
		next_pos = 0;
		last_read_bytes = n_bytes;
	}
	
	// caso contrario -> escrever 1 caracter no buffer
	*buf = file_buffer[next_pos];
	next_pos++;
	return 1;

}

ssize_t readln(int fd, char *line, size_t size){

	int read_bytes = 0;
	int next_pos = 0;

	while (next_pos < size && readch(fd,line + next_pos)){
		read_bytes++;

		if (line[next_pos] == '\n')
			break;

		next_pos++;
	}

	return read_bytes;
}




int main(int argc, char * argv[]){
	/* exercicio 1
	clock_t begin = clock();
	int x = mycp(argc,argv);
	clock_t end = clock();
	double time_spent = (double)(end - begin);
	printf("foram copiados %d bytes em %f segundos\n", x, time_spent); 
	*/


	/* exercicio 2
	mycat(); */

	/* exercicio 3*/
	int fd = open(argv[1],O_RDONLY);
	char buffer[10];

	int line_bytes = 0;
	int n_line = 1;
	while ((line_bytes = readln(fd,buffer,10)) > 0){
		//printf("%s",buffer );
		write(1,buffer,line_bytes);
	}

}




