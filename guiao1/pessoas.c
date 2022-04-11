#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

typedef struct pessoa {
	char nome[200];
	int idade;
} Person;

int main (int argc, char * argv[]){

	int fd = open ("pessoas.bin",O_CREAT | O_TRUNC | O_RDWR,0644);

	if (fd < 0){
		perror ("erro abrir ficheiro");
	}

	Person p1 ;
	strcpy(p1.nome,"Maria Mourinho");
	p1.idade = 20;

	write(fd,&p1,sizeof(Person));

	close(fd);
}