/*************************************************************************
	> File Name: exc_helloword.c
	> Author: 
	> Mail: 
	> Created Time: 2015年03月24日 星期二 15时44分49秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[], char **environ)
{
    pid_t pid;
    int stat_val;

    pid = fork();

    switch (pid) {
        case -1:
            perror("Process Creation failed\n");
            exit(-1);
        case 0:
            execve("helloworld", argv, environ);
            exit(0);
        default:
            break;
    }

    wait(&stat_val);
    exit(0);
}
