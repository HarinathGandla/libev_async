/*************************************************************************
	> File Name: mysql_test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年04月08日 星期三 11时51分47秒
 ************************************************************************/

#include<stdio.h>
#include<mysql.h>
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
    MYSQL conn;
    int res;

    mysql_init(&conn);
    if (mysql_real_connect(&conn, "localhost", "root", "d6556j","test", 0, NULL, 0)) {
        printf("connect success!\n");
        res = mysql_query(&conn, "insert into test values('user', '123456')");
        if (res) {
            printf("error\n");
        } else {
            printf("OK\n");
        }

        mysql_close(&conn);
    }

    return 0;
}
