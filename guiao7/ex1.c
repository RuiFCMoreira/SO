#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int stop = 1;
int ctrl_c_counter = 0;
int seconds = 0;

void ctrl_c_handler(int signum){
	printf("tempo passado: xxx\n");
	ctrl_c_counter++;
}

void ctrl_barra_handler(int signum){
	printf("Nº de vezes que o utilizador carregou em Ctrl+C: %d\n",ctrl_c_counter);
	stop = 0;
}

void sigalarm_handler(int signum){
	seconds++;
    alarm(1);
    pause();
}



int main (int argc, char * argv[]){

	if(signal(SIGINT,ctrl_c_handler) == SIG_ERR){
		perror("SIGINT failed");
	}

	if(signal(SIGQUIT,ctrl_barra_handler) == SIG_ERR){
		perror("SIGQUIT failed");
	}

	while(stop){
		printf("Working...\n");
		sleep(1);
	}

	return 0;
}