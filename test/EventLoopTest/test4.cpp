/*************************************************************************
	> File Name: test4.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月15日 星期四 10时19分04秒
 ************************************************************************/

#include "../../net/EventLoop.h"
#include "../../net/Channel.h"

#include <cstdio>
#include <sys/timerfd.h>

research::EventLoop* g_loop;

void timeout()
{
    printf("Timeout!\n");
    g_loop->quit();
}


int main(int argc, char* argv[])
{
    research::EventLoop loop;
    g_loop = &loop;

    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    research::Channel channel(&loop, timerfd);
    channel.setReadCallback(timeout);
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong, sizeof howlong);
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timerfd, 0, &howlong,  nullptr);

    loop.loop();

    ::close(timerfd);

}
