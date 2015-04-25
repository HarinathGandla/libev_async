/*************************************************************************
	> File Name: ev_async_test.c
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 17时33分28秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<ev.h>

ev_async async_watcher;

static void
sigint_callback(EV_P_ ev_signal *w, int revents)
{
    if (revents & EV_SIGNAL) {
        printf("Call signal_callback\n");
        printf("ev_async_send 调用前%d\n", ev_async_pending(&async_watcher));
        ev_async_send(EV_A, &async_watcher); //这里回调用async_callback
        printf("ev_async_send 调用后%d\n", ev_async_pending(&async_watcher));
    }
}

static void
sigquit_callback(EV_P_ ev_signal *w, int revents)
{
    printf("Call sigquit_callback\n");
    ev_break(EV_A, EVBREAK_ALL);
}

static void
async_callback(EV_P_ ev_async *w, int revents)
{
    if (revents & EV_ASYNC) {
        printf("Call async_callback\n");
    }
}

int 
main(int argc, char argv[])
{
    EV_P = ev_default_loop(0);

    ev_init(&async_watcher, async_callback);
    ev_async_start(EV_A, &async_watcher);

    ev_signal sigint_watcher;
    ev_init(&sigint_watcher, sigint_callback);
    ev_signal_set(&sigint_watcher, SIGINT);
    ev_signal_start(EV_A, &sigint_watcher);

    ev_signal sigquit_watcher;
    ev_init(&sigquit_watcher, sigquit_callback);
    ev_signal_set(&sigquit_watcher, SIGQUIT);
    ev_signal_start(EV_A, &sigquit_watcher);
    
    ev_run(EV_A, 0);
    return 0;
}













































