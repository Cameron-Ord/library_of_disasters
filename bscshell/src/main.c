#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "include/main.h"

#define MAX_COMMAND_LENGTH 100

int main(){
    char command[MAX_COMMAND_LENGTH];
    while(1){
        printf("[CMD]>> ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        if(strncmp(command, "exit", 4)==0){
            break;
        } else if(strncmp(command, "cd", 2) == 0){
            char *path = strtok(command + 3, " \n");
            if (path != NULL){
                if(chdir(path) != 0){
                    perror("CHDIR failed");
                }
            } else {
                printf("Invalid syntax for CD\n");
            }
        } else {
            execute_command(command);
        }
    }

    return 0;
}

void execute_command(char *command){
    char *args[MAX_COMMAND_LENGTH];
    char *token = strtok(command, " \n");
    int i=0;

    while(token != NULL){
        args[i] = token;
        token = strtok(NULL, " \n");
        i++;
    }
    args[i] = NULL;

    pid_t pid = fork();

    if(pid<0){
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        if (execvp(args[0],args)==-1){
            perror("Invalid command");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);
    }
}