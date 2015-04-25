/*************************************************************************
	> File Name: ev_child_test.c
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 16时36分10秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<ev.h>

static void
child_callback(EV_P_ ev_child *w, int revents)
{
    ev_child_stop(EV_A, w);
    printf("Process %d exited whit status %d\n", w->rpid, w->rstatus);
}

int main(int argv, char argc[])
{
    EV_P = ev_default_loop(0);
    pid_t pid;
    ev_child child_watcher;

    pid = fork();
    if (pid < 0) {
        printf("fork create failed\n");
        return -1;
    } else if (pid == 0) { //chaild
        printf("child doing...\n");
//        return 0;
        while(1);
    } else {    //father
        sleep(2);//即使让子进程先执行，最后还可以捕获
        printf("pid:%d\n", pid);
        ev_init(&child_watcher, child_callback);
        ev_child_set(&child_watcher, pid, 0);
        ev_child_start(EV_A, &child_watcher);
        ev_run(EV_A, 0);
    }

    return 0;
}
