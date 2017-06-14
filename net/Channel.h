/*************************************************************************
	> File Name: Channel.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月14日 星期三 23时16分11秒
 ************************************************************************/

#ifndef _RESEARCH_NET_CHANNEL_H
#define _RESEARCH_NET__CHANNEL_H

#include "../core/noncopyable.hpp"

#include <functional>

namespace research
{

class EventLoop;

    
class Channel : noncopyable
{
public:
    //typedef std::function<void()> EventCallback;
    using EventCallback = std::function<void()>;

    Channel(EventLoop* loop, int fd);

    // called by loop, call different callback according to revents_
    void handleEvent();

    void setReadCallback(const EventCallback& cb)
    {
        readCallback_ = cb;
    }

    void setWriteCallback(const EventCallback cb)
    {
        writeCallback_ = cb;
    }

    void setErrorCallback(const EventCallback cb)
    {
        errorCallback_ = cb;
    }

    int fd() const
    {
        return fd_;
    }

    int events() const
    {
        return events_;
    }

    void set_revents(int revt)
    {
        revents_ = revt;
    }

    bool isNoneEvent() const
    {
        return events_ == kNoneEvent;
    }

    void enableReading()
    {
        events |= kReadEvent;
        update();
    }

    // void enableWriting();
    // void disableWriting();
    // void disableAll();
    
    //for Poller
    int index()
    {
        return index_;
    }

    void set_index(int idx)
    {
        index_ = idx;
    }

    EventLoop* ownerLoop()
    {
        return loop_;
    }

private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};

}

#endif  // _RESEARCH_NET_CHANNERL_H
