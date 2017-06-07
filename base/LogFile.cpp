#include "LogFile.h"

#include <muduo/base/FileUtil.h>
#include <muduo/base/ProcessInfo.h>

#include <cassert>
#include <cstdio>
#include <ctime>

using namespace muduo;
using namespace research;

LogFile::LogFile(const string& basename, size_t rollSize, bool threadSafe, int flushInterval, int checkEveryN)
	: basename_(basename), rollSize_(rollSize), flushInterval_(flushInterval), checkEveryN_(checkEveryN_),
	  count_(0),
	  mutex_(threadSafe ? new MutexLock : nullptr),
	  startOfPeriod_(0),
	  lastRoll_(0),
	  lastFlush_(0)
{
	// only create log file in current dir
	assert(basename.find('/') == string::npos);
	rollFile();
}

LogFile::~LogFile()
{};  // no content

void LogFile::append(const char* logline, int len)
{
	if (mutex_)
	{
		MutexLockGuard lock(*mutex_);
		append_unlocked(logline, len);
	}
	else
	{
		append_unlocked(logline, len);
	}
}

void LogFile::flush()
{
	if (mutex_)
	{
		MutexLockGuard lock(*mutex_)
		{
			file_->flush();
		}
	}
	else
	{
		file_->flush();
	}
}

void LogFile::append_unlocked(const char* logline, int len)
{
	file_->append(logline, len);

	if (file_->writtenBytes() > rollSize_)
	{
		rollFile();
	}
	else
	{
		++count_;
		if (count_ >= checkEveryN_)
		{
			count_ = 0;
			time_t now = ::time(nullptr);
			time_t thisPeriod = now / kRollPerSeconds_ * kRollPerSeconds_;
			if (thisPeriod_ != startOfPeriod_)
			{
				rollFile();
			}
			else if (now - lastFlush_ > flushInterval_)
			{
				lastFlush_ = now;
				file_->flush();
			}
		}
	}
}

bool LogFile::rollFile()
{
	time_t now = 0;
	string filename = getLogFileName(basename_, &now);
	time_t start = now / kRollPerSeconds_ * kRollPerSeconds_;

	if (now > lastRoll_)
	{
		lastRoll_ = now;
		lastFlush_ = now;
		startOfPeriod_ = start;
		file_.reset(new FileUtil::AppendFile(filename));
		return true;
	}
}

string LogFile::getLogFileName(const string& basename, time_t* now)
{
	string filename;
	filename.reserve(basename.size() + 64);
	filename = basename;

	char timebuf[32];
	struct tm tm;
	*now = time(nullptr);
}