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

void threadFunc()
{
    printf("threadFunc(): pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());
    
    research::EventLoop loop;
    loop.loop();
}

int main(int argc, char* argv[])
{
    printf("threadFunc(): pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());

    research::EventLoop loop;
    muduo::Thread::ThreadFunc func(threadFunc);
    muduo::Thread thread(func);
    thread.start();

    loop.loop();
    pthread_exit(nullptr);
    
}
