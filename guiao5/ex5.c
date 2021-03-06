#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h>   

#define MAX 100


int main (int argc, char * args[]){
	/*
     * Este array tem os nomes dos comandos a executar
     * Estamos a assumir numero maximo de argumentos (poderia ser melhorado com realloc)
     * */
    char* exec_args[10][10];
    char* string;
    int i, c, a;
    int number_of_commands;
    char* command;
    int pid;
    int status;
    /*
     * Separar os argumentos e os comandos por um array com 2 dimensões: dimensão 1 -> comando; dimensão 2 -> argumentos do comando
     * */
    a = 0;
    while( args[a] ){
        /*
         * Copiar a string com os comandos recebida por parâmetro nesta função
         * */
        command = strdup(args[a]);

        /*
         * Fazer o parsing da string
         * Colocar num array os vários comandos a executar
         * */
        string = strtok(command," ");
        i = 0;
        while(string != NULL){
            exec_args[a][i] = string;
            string = strtok(NULL," ");
            i++;
        }
        a++;

        /*
         * No final preciso de colocar o NULL pois é assim que esta formatado o parâmetro do execvp com o s argumentos do executável
         * */
        exec_args[a][i] = NULL;
    }

    number_of_commands = a;
    /*
     * Vamos ter N comandos, por isso temos N-1 pipes e cada pipe tem 2 descritores(leitura e escrita)
     * */
    int pipes[number_of_commands-1][2];

    /*
     * Para cada comando tenho de criar um processo filho
     * iterar sobre os comandos a executar
     * */
    for( c=0; c<number_of_commands; c++ ){
        //primeiro comand(não redir stdin)
        if( c == 0 ){
            /*
             * Criar os pipe necessário para fazer a comunicação entre o comando c e o comando c+1
             * */
            pipe(pipes[c]);

            switch( ( pid = fork() ) ){
                case -1:
                    perror("fork");
                    return -1;
                case 0:
                    /*
                     * O filho só escreve no primeiro pipe por isso podemos fechar a extremidade de leitura do pipe
                     * */
                    close(pipes[c][0]);
                    /*
                     * Se fizesse já o execlp do comando o resultado da execução do comando seria impressa no stdout
                     * mas pretendemos que este resultado seja escrito no pipe, por isso temos de fazer o redirecionamento
                     * do stdout para a extremidade de escrita do pipe
                     * (ou seja, tudo o que era escrito no ecrã vai passar a ser escrito na extremidade de escrita do pipe)
                     * */
                    dup2(pipes[c][1],1);
                    /*
                     * Já fizemos o redirectionamento por isso podemos apagar o descriptor p[1]
                     * */
                    close(pipes[c][1]);
                    execvp(exec_args[c][0],exec_args[c]);
                    _exit(0);
                default:
                    /*
                     * O pai não vai usar a extremidade de leitura do pipe c (que é zero porque estamos dentro do if(c==0)) por isso temos de fechar essa parte
                     * Não deveremos fechar a extremidade de leitura do pipe no pai neste momento pois caso o fizessemos e o comando executado escrevesse na extremidade de escrita
                     * como as extremidades de leitura estariam todas fechadas receberíamos um sinal SIGPIPE
                     * */
                    close(pipes[c][1]);
                    /*
                     * O processo pai continua para criar as ligações entre os comandos restantes
                     * */
            }
        }
        else if( c == number_of_commands-1 ){
            /*
             * Não é necessário criar pois este comando apenas interage com 1 pipe que já foi criado (pipe(number_of_commands-2))
             * ou seja, o ultimo pipe da sequencia de pipes
             * */
            switch( ( pid = fork() ) ){
                case -1:
                    perror("fork");
                    return -1;
                case 0:
                    /*
                     * O filho só lê no último pipe por isso podemos redicionar o stdin para a extremidade de leitura do pipe
                     * */
                    dup2(pipes[c-1][0],0);
                    close(pipes[c-1][0]);
                    execvp(exec_args[c][0],exec_args[c]);
                    _exit(0);
                default:
                    /*
                     * Fechar a extremidade de leitura que estava aberta no pai desde a última iteração
                     * */
                    close(pipes[c-1][0]);
                    /*
                     * O processo pai já não vai criar mais processos filhos nem pipes
                     * */
            }

        }
        else{
            pipe(pipes[c]);

            switch( ( pid = fork() ) ){
                case -1:
                    perror("fork");
                    return -1;
                case 0:
                    /*
                     * Não preciso de fechar a extremidade de escrita do pipe c-1 pois esta operação já foi feita na iteração anterior no código do pai
                     * De lembrar que ao fazer fork é copiado o estado do pai para o filho
                     * */

                    /*
                     * Necessário redirecionar o stdin para a extremidade de leitura do pipe c-1 (pipe atrás desse processo que liga com o stdin do processo filho)
                     * */
                    dup2(pipes[c-1][0],0);
                    close(pipes[c-1][0]);
                    /*
                     * Também não preciso da extremidade de leitura do pipe c aberta
                     * */
                    close(pipes[c][0]);
                    /*
                     * Necessário redirecionar o stdout para a extremidade de escrita do pipe c
                     * */
                    dup2(pipes[c][1],1);
                    close(pipes[c][1]);
                    execvp(exec_args[c][0],exec_args[c]);
                    _exit(0);
                default:
                    /*
                     * Fechar a extremidade de leitura do pipe c-1, que não tinhamos fechado na iteração anterior.
                     * Só fechamos aqui pois o filho já redirecionou a extremidade de leitura do pipe e então já não há possibilidade de causar SIGPIPE
                     * */
                    close(pipes[c-1][0]);
                    /*
                     * Fechar a extremidade de escrita do pipe pois já temos esta extremidade aberta no processo filho que acabamos de criar
                     * */
                    close(pipes[c][1]);
                    /*
                     * O processo pai continua para criar as ligações entre os comandos restantes
                     * */
            }

        }
    }
    /*
     * Esperar que os filhos terminem antes de terminar o programa
     * */
    for( i=0; i<number_of_commands ;i++){
        wait(&status);
    }

    return 0;
}
