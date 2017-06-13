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

int main(int argc, char* argv[])
{
    research::EventLoop loop, loop2;


    loop.loop();
    loop2.loop();

}
