#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main (int argc, char * argv[]){


	if (mkfifo("fifo",0666) == -1){
		perror("mkfifo");
		return -1;
	} 

	return 0;
}