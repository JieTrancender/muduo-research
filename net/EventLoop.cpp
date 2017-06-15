/*************************************************************************
	> File Name: EventLoop.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月13日 星期二 15时03分41秒
 ************************************************************************/

#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"

#include <muduo/base/Logging.h>

#include <cassert>

using namespace research;

__thread EventLoop* t_loopInThisThread = 0;
const int kPollTimeMs = 10000;

EventLoop::EventLoop()
: looping_(false),
  quit_(false),
  threadId_(muduo::CurrentThread::tid()),
  poller_(new Poller(this))
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
    quit_ = false;

    while (!quit_)
    {
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, &activeChannels_);
        for (const auto& channel : activeChannels_)
        {
            channel->handleEvent();
        }
    }

    LOG_TRACE << "EventLoop " << this << " stop lopping";
    looping_ = false;
}

void EventLoop::quit()
{
    quit_ = true;
}

void EventLoop::updateChannel(Channel* channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}

void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
        << " was created in threadId_ = " << threadId_
    << ", current thread id = " << muduo::CurrentThread::tid();
}
