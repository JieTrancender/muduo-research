#ifndef _BASE_ASYNCLOGGING_H
#define _BASE_ASYNCLOGGING_H

#include "../core/noncopyable.hpp"

#include <muduo/base/BlockingQueue.h>
#include <muduo/base/BoundedBlockingQueue.h>
#include <muduo/base/CountDownLatch.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Thread.h>

#include <muduo/base/LogStream.h>

#include <boost/bind.hpp>
// #include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace research
{

class AsyncLogging : noncopyable
{
public:
	AsyncLogging(const string& basename, size_t rollSize, int flushInterval = 3);

	~AsyncLogging()
	{
		if (running_)
		{
			stop();
		}
	}

	void append(const char* logline, int len);

	void start()
	{
		running_ = true;
		thread_.start();
		latch_.wait();
	}

	void stop()
	{
		running_ = false;
		cond_.notify();
		thread_.join();
	}

private:
	// declare but not define, prevent compiler-synthesized functions
	// in my idea, these are not necessary because noncopyable
	AyncLogging(const AsyncLogging&);  // ptr_container
	void operator=(const AsyncLogging&)  // ptr_container

	void threadFunc();

	typedef muduo::detail::FixedBuffer<muduo::detail::kLargeBuffer> Buffer;
	typedef boost::ptr_vector<Buffer> BufferVector;  // ptr_vector指针容器，Buffer呗vecotr独占
	typedef BufferVector::auto_type BufferPtr;

	const int flushInterval_;
	bool running_;
	string basename_;
	size_t rollSize_;
	muduo::Thread thread_;
	muduo::CountDownLatch latch_;
	muduo::MutexLock mutex_;
	muduo::Condition cond_;
	BufferPtr currentBuffer_;
	BufferPtr nextBuffer_;
	BufferVector buffers_;
};
}

#endif  //_BASE_ASYNCLOGGING_H