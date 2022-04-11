#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 1024

int main (int argc, char * argv[]){


	if (mkfifo("fifo",0666) == -1){
		perror("mkfifo");
		return -1;
	}

	int fd = open("fifo",O_RDONLY);
	if (fd < 0){
		perror("open");
		return -1;
	}

	int fdLog = open("log.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);
	if (fdLog < 0){
		perror("open");
		return -1;
	}

	int read_bytes;
	char buffer[MAX];
	while (1){


		while ((read_bytes = read(fd,buffer,MAX)) > 0){
			write(fdLog,buffer,read_bytes);
		}
	

	}

	close(fdLog);
	close(fd);

	return 0;
}