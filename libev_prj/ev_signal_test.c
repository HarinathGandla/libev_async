/*************************************************************************
	> File Name: ev_signal_test.c
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 16时14分20秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<ev.h>

static void 
signal_callback(EV_P_ ev_signal *w, int revents)
{
    //可以用这个判断进来的是不是ev_signal 如果一个callback回调函复用的话，就可以用这个来做区分
    if (revents & EV_SIGNAL) {
        printf("signal SIGINT\n");
        ev_break(EV_A_ EVBREAK_ALL);
    }
}

static void
sigquit_callback(EV_P_ ev_signal *w, int revents)
{
    printf("signal SIGQUIT\n");
    ev_break(EV_A_ EVBREAK_ALL);
}

int 
main(int argc, char argv[])
{
    EV_P = ev_default_loop(0);
    ev_signal sigint_watcher;
    ev_signal sigquit_watcher;

    ev_init(&sigint_watcher, signal_callback);
    ev_signal_set(&sigint_watcher, SIGINT/*other want to catch*/);//这里多个信号不能用或符号|连起来
    ev_signal_start(EV_A, &sigint_watcher);

    ev_init(&sigquit_watcher, sigquit_callback);
    ev_signal_set(&sigquit_watcher,SIGQUIT);
    ev_signal_start(EV_A, &sigquit_watcher);

    ev_run(EV_A, 0);

    return 0;
}
