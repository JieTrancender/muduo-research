/*************************************************************************
	> File Name: EventLoop.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月13日 星期二 15时03分41秒
 ************************************************************************/

#include "EventLoop.h"

#include <muduo/base/Logging.h>

#include <cassert>
#include <poll.h>

using namespace muduo;
using namespace research;

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
: looping_(false), threadId_(CurrentThread::tid())
{
    LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;
    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop()
{
    assert(!looping_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;

    ::poll(nullptr, 0, 5 * 1000);

    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}

void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
        << " was created in threadId_ = " << threadId_
        << ", current thread id = " << CurrentThread::tid();
}
