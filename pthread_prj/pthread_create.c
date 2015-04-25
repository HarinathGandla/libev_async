/*************************************************************************
	> File Name: pthread_create.c
	> Author: 
	> Mail: 
	> Created Time: 2015年03月24日 星期二 16时47分29秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *thrd_func(void *arg);
pthread_t tid;

int main(void)
{
    if (pthread_create(&tid, NULL, thrd_func, NULL) != 0) {
        printf("Create thread error!\n");
        exit(1);
    }

    printf("TID in pthread_create function:%lu.\n", tid);
    printf("Main process: PID:%d, TID:%lu.\n", getpid(), pthread_self());

    sleep(1);
    return 0;
}

void *thrd_func(void *arg)
{
    printf("New process: PID:%d, TID:%lu.\n", getpid(), pthread_self());//why pthread_self
    printf("New process: PID:%d, TID:%lu.\n", getpid(), tid);

    pthread_exit(NULL);//退出线程
}


