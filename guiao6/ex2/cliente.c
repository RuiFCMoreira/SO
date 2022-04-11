#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main (int argc, char * argv[]){

	int fd = open("fifo",O_WRONLY);
	if (fd < 0){
		perror("open");
		return -1;
	}

	int bytesRead = 0;
	char buffer[1024];
	while((bytesRead = read(0, buffer, 1024)) > 0) {
        write(fd, buffer, bytesRead);
    }
    
    close(fd);

	return 0;
}