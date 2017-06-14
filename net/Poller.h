/*************************************************************************
	> File Name: Poller.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月14日 星期三 23时55分33秒
 ************************************************************************/

#ifndef _RESEARCH_NET_POLLER_H
#define _RESEARCH_NET_POLLER_H

#include "EventLoop.h"

#include <muduo/base/Timestamp.h>

#include <map>
#include <vector>

struct pollfd;

namespace research
{

class Channel;

class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop);
    ~Poller();

    // must be called in the loop thread.
    Timestamp poll(int timeoutMs, ChannelList* activeChannels);

    //must be called in the loop thread.
    void updateChannel(Channel* channel);

    void assertInLoopThread()
    {
        ownerLoop_->assertInLoopThread();
    }

private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    using PollFdList = std::vector<struct pollfd>;
    using ChannelMap = std::map<int, Channel*>;

    EventLoop* ownerLoop_;
    PollFdList pollfds_;
    ChannelMap channels_;
};

}


#endif  // _RESEARCH_NET_POLLER_H
