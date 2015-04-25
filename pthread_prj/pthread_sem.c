/*************************************************************************
	> File Name: pthread_sem.c
	> Author: 
	> Mail: 
	> Created Time: 2015年03月25日 星期三 12时33分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define THREAD_NUM 3
#define REPEAT_TIMES 5
#define DELAY 4

sem_t sem[THREAD_NUM];

void *thrd_func(void *arg);

int main(void)
{
    pthread_t thread[THREAD_NUM];
    int no;
    void *tret;

    srand((int)time(0));

    //初始化THREAD_NUM-1个信号量，均初始化为0
    for (no = 0; no < THREAD_NUM; no++) {
        sem_init(&sem[no], 0, 0);
    }

    //sem[2]信号量初始化为1,即sem数组中最后一个信号量
    sem_init(&sem[2],0,1);

    //创建THREAD_NUM个线程，入口含素均为thrd_func，参数为(void *)no
    for (no = 0; no < THREAD_NUM; no++) {
        if(pthread_create(&thread[no], NULL, thrd_func, (void *)no) != 0) {
            printf("Create thread %d error!\n", no);
            exit(1);
        } else
            printf("Create thread %d success!\n", no);
    }

    //逐个join掉THREAD_NUM个线程
    for (no = 0; no < THREAD_NUM; no++) {
        if (pthread_join(thread[no], &tret) != 0) {
            printf("Join thread %d error!\n", no);
            exit(1);
        } else 
            printf("Join thread %d success!\n", no);
    }

    //逐个取消信号量
    for (no = 0; no < THREAD_NUM; no++) {
        sem_destroy(&sem[no]);
    }

    return 0;
}

void *thrd_func(void *arg) {
    int thrd_num = (void *)arg; //参数no
    int delay_time, count;

    //带有阻塞的p操作
    sem_wait(&sem[thrd_num]);

    printf("Thread %d is starting.\n", thrd_num);
    for (count = 0; count < REPEAT_TIMES; count++) {
        delay_time = (int)(DELAY*(rand()/(double)RAND_MAX)) + 1;
        sleep(delay_time);
        printf("\tThread %d:job %d delay = %d.\n", thrd_num,count, delay_time);
    }

    printf("Thread %d is exiting.\n", thrd_num);

    //对前一个信号量进行V操作
    //由于只有最后一个信号量初始化为1,其余为0
    //故线程执行的顺序为逆序
    sem_post(&sem[(thrd_num + THREAD_NUM - 1)%THREAD_NUM]);

    pthread_exit(NULL);//线程主动结束
}
