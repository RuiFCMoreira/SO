…#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){
	execl("ex3PrintArgs","ls","arg1","arg2","arg3",NULL);
	perror("exec");
	
	return 0;
}