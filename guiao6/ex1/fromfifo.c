#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 1024

int main(int argc, char * argv[]){
	char buffer[MAX];

	int fd = open("fifo",O_RDONLY);
	if (fd < 0){
		perror("open");
		return -1;
	}

	int read_bytes ;
	while ((read_bytes = read(fd,buffer,MAX)) > 0){
		write(1,buffer,read_bytes);
	}

	close(fd);
}