#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_systemV(char * argv[]){
	int pid;
	if ((pid = fork()) == 0){
		execvp(argv[0],argv);
		perror("execvp");
		_exit(255);
	}
	
	// check fork 
	if (pid < 0)
		return -1;
		
	int status;

	// check wait
	if (waitpid(pid,&status,0) < 0){
		return -1;
	}

	return WEXITSTATUS(status);

}

int my_system(char * command){
	// separar comando por espaço
	// construir execv_args
	char * execv_args[20];
	char* exec_args[20];
	char * string;
    string = strtok(command," ");

    int i = 0;
    while(string != NULL){
        exec_args[i] = string;
        string = strtok(NULL," ");
        i++;
    }

    exec_args[i] = NULL;


	return my_systemV(execv_args);
}



int main (int argc,char * argv[]){

	my_system("ls -l");
	/*char * exec_args_ls[] = {
		"ls",
		"-l",
		NULL,
	};
	my_systemV(exec_args_ls);*/

	my_system("./ex3PrintArgs");
	/*char * exec_args_printArgs[] = {
		"./ex3PrintArgs",
		NULL,
	};
	my_systemV(exec_args_printArgs);  */

	return 0;
}