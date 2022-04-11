#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){

	int value = atoi(argv[1]);
	int rows = 10;
	int cols = 1000;
	int matriz[rows][cols];
	int random_max = 10000;


	// preencher matriz com numeros aleatorios
	printf("preencher matriz com numeros aleatorios entre 0 e %d\n",random_max);
	for (int i = 0; i < rows; i ++){
		for (int j = 0; j < cols; j++){
			matriz[i][j] = rand() % random_max;// gera numeros entre 0 e 9999
		}
	}

	int pids[rows];
	// criar todos os processos
	for (int i = 0; i < rows; i++){
		if ((pids[i] = fork()) == 0 ){
			// percorrer a linha e ve se encontra valor 
			for (int j = 0; j < cols; j++){
				if (matriz[i][j] == value)
					_exit(i);
			}

			_exit(255);
		}
	}

	// esperar todos processos 
	int status;
	for (int i = 0; i <= rows; i++){
		//int terminated_pid = wait(&status); // é equivalente a int terminated_pid = waitpid(-1,&status,0); 
		int terminated_pid = wait(pids[i],&status,0);
		if (WIFEXITED(status)){
			if (WEXITSTATUS(status) < 255){
				printf("[pai] processo %d saiu, encontrou numero na linha: %d\n",terminated_pid,WEXITSTATUS(status));
			}else {
				printf("[pai] processo %d saiu, não encontrou numero \n",terminated_pid);

			}
		}else {
			printf("[pai] processo %d saiu, aconteceu algo de errado\n",terminated_pid);
		}
	}

	return 0;
}