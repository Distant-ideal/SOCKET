/*************************************************************************
	> File Name: Daemon.h
	> Author: gongpixi
	> Mail: 1371854096@qq.com
	> Created Time: 2018年12月23日 星期日 19时24分05秒
 ************************************************************************/

#ifndef _DAEMON_H
#define _DAEMON_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void create_daemon(void)//将一般进程变为守护进程
{
    pid_t pid = 0;
    pid = fork();//创建子进程
    if(pid<0) {
    perror("fork");
    exit(-1);
    }
    else if (pid > 0)
    {
    printf("The program has been converted to a daemon\n");
    exit(-1);
    }
    else if (pid == 0) {
        pid = setsid();//子进程脱离控制台创建新的会话期
        if(pid < 0) {
            perror("setsid");
        }
        chdir("/");//脱离文件系统
        umask(0);//用umas函数取消任何文件的权限屏蔽
        int i = sysconf(_SC_OPEN_MAX);//得到系统最大的文件描述符个数
    for (;i>0;i--)//关闭所有文件描述符
    {
        close(i);
    }
    open("/dev/null",O_RDWR);//将0,1,2定位到/dev/null
    open("/dev/null",O_RDWR);
    open("/dev/null",O_RDWR);
    }
}


#endif
