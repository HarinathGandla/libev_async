/*************************************************************************
	> File Name: ev_timer_test.c
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 15时14分44秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ev.h>

static void
three_second_callback(EV_P_ ev_timer *w, int revents)
{
    //这是一个三秒的定时器
    ev_timer_stop(EV_A_ w);
    printf("3秒触发器\n");
    ev_timer_set(w, 3, 0);
    ev_timer_start(EV_A_ w);
}

static void 
five_second_callback(EV_P_ ev_timer *w, int revents)
{
    //这是一个五秒的定时器
    ev_timer_stop(EV_A_ w);
    printf("5秒触发器\n");
    ev_timer_set(w, 5, 0);
    ev_timer_start(EV_A_ w);
}

static void
ten_second_callback(EV_P_ ev_timer *w, int revents)
{
    //这是一个十秒定时器
    ev_timer_stop(EV_A_ w);
    printf("10秒定时器\n");
    ev_timer_set(w, 10, 0);
    ev_timer_start(EV_A_ w);
}

int
main(int argc, char argv[])
{
    EV_P = ev_loop_new(0);

    ev_timer mytimer_watcher3;
    ev_timer mytimer_watcher5;
    ev_timer mytimer_watcher10;

    ev_init(&mytimer_watcher3, three_second_callback);
    ev_timer_set(&mytimer_watcher3, 0, 0);
    ev_timer_start(EV_A, &mytimer_watcher3);
//    ev_run(main_loop, 0);
//    ev_loop(EV_A, 0);

    ev_init(&mytimer_watcher5, five_second_callback);
    ev_timer_set(&mytimer_watcher5, 0, 0);
    ev_timer_start(EV_A, &mytimer_watcher5);
//    ev_run(main_loop, 0);
//    ev_loop(EV_A, 0);

    ev_init(&mytimer_watcher10, ten_second_callback);
    ev_timer_set(&mytimer_watcher10, 0, 0);
    ev_timer_start(EV_A, &mytimer_watcher10);
//    ev_run(main_loop, 0);
    ev_loop(EV_A, 0);

    return 0;
}


