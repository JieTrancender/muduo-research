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

#include <memory>
#include <vector>

namespace research
{

class Channel;
class Poller;

class EventLoop : noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void quit();

    void updateChannel(Channel* channel);

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

    using ChannelList = std::vector<Channel*>;

    bool looping_;
    bool quit_;
    const pid_t threadId_;
    std::unique_ptr<Poller> poller_;
    ChannelList activeChannels_;
};

}

#endif
