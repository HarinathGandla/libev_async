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
        printf("The file st_dev %d\n", (int)w->attr.st_dev);
        printf("The file st_ino %d\n", (int)w->attr.st_ino);
        printf("The file st_mode %d\n", (int)w->attr.st_mode);
        printf("The file st_nlink %d\n", (int)w->attr.st_nlink);
        printf("The file st_uid %d\n", (int)w->attr.st_uid);
        printf("The file st_gid %d\n", (int)w->attr.st_gid);
        printf("The file st_rdev %d\n", (int)w->attr.st_rdev);
        printf("The file st_size %d\n", (int)w->attr.st_size);
        printf("The file st_atime %d\n", (int)w->attr.st_atime);
        printf("The file st_mtime %d\n", (int)w->attr.st_mtime);
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

