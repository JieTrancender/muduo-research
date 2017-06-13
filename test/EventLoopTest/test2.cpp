/*************************************************************************
	> File Name: test1.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月13日 星期二 17时42分27秒
 ************************************************************************/

#include "../../net/EventLoop.h"
#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>

#include <cstdio>

research::EventLoop* g_loop;

void threadFunc()
{
    g_loop->loop();
}

int main(int argc, char* argv[])
{
    research::EventLoop loop;
    g_loop = &loop;

    muduo::Thread::ThreadFunc func(threadFunc);
    muduo::Thread thread(func);
    thread.start();
    thread.join();
}
