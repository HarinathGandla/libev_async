/*************************************************************************
	> File Name: ev_stat_test.c
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 17时03分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<ev.h>

static void
stat_callback(EV_P_ ev_stat *w, int revents)
{
    if (w->attr.st_nlink) {
        printf("The file size %ld\n", (long)w->attr.st_size);
    } else {
        printf("文件不存在\n");
    }
}

int 
main(int argc, char argv[])
{
    EV_P = ev_default_loop(0);
    ev_stat stat_watcher;
    ev_init(&stat_watcher, stat_callback);
    ev_stat_set(&stat_watcher, "/home/dj/my/workspace/my_prj/libev_prj/hello.txt", 0);
    ev_stat_start(EV_A, &stat_watcher);

    ev_run(EV_A, 0);

    return 0;
}

