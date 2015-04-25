/*************************************************************************
	> File Name: ev_periodic_test.c
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 15时56分54秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ev.h>

static void
periodic_callback(EV_P_ ev_periodic *w, int revents)
{
    printf("每3秒执行一次\n");
}

static 
ev_tstamp periodic_scheduler_callback(ev_periodic *w, ev_tstamp now)
{
    return now + 3; //注意时间要加上一个now， 是一个绝对的时间
}

int 
main(int argc, char argv[])
{
    EV_P = ev_default_loop(0);
    ev_periodic periodic_wathcer;

    ev_init(&periodic_wathcer, periodic_callback);
    ev_periodic_set(&periodic_wathcer, 0, 3, 0);
    ev_periodic_start(EV_A, &periodic_wathcer);

    //如果时间周期计算方式，不能通过一个表达式表示，那么可以通过一个函数来表示放在set的第四个参数
    ev_init(&periodic_wathcer, periodic_callback);
    ev_periodic_set(&periodic_wathcer, 0, 0, periodic_scheduler_callback);
    ev_periodic_start(EV_A, &periodic_wathcer);

    ev_run(EV_A, 0);

    return 0;
}
