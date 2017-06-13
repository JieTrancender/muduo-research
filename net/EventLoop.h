/*************************************************************************
	> File Name: EventLoop.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月13日 星期二 14时55分10秒
 ************************************************************************/

#ifndef _NET_EVENTLOOP_H
#define _NET_EVENTLOOP_H

#include "../core/noncopyable.hpp"

#include <muduo/base/CurrentThread.h>
#include <muduo/base/Thread.h>

namespace research
{

class EventLoop : noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    static EventLoop* getEventLoopOfCurrentThread();

    void assertInLoopThread()
    {
        if (!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    bool isInLoopThread() const
    {
        return threadId_ == muduo::CurrentThread::tid();
    }

private:
    void abortNotInLoopThread();

    bool looping_;
    const pid_t threadId_;
};

}

#endif
