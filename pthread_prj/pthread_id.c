/*************************************************************************
	> File Name: pthread_id.c
	> Author: 
	> Mail: 
	> Created Time: 2015年03月24日 星期二 16时33分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int main(void)
{
    pthread_t thread_id;

    thread_id = pthread_self();//返回调用线程的ID
    printf("Thread ID:%lu.\n", thread_id);

    if (pthread_equal(thread_id, pthread_self())) {
        printf("Equal!\n");
    } else {
        printf("Not Equal!\n");
    }

    return 0;
}
