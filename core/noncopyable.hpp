#ifndef _NONCOPYABLE_HPP
#define _NONCOPYABLE_HPP

namespace research
{

namespace noncopyable_
{

class noncopyable
{
protected:
	constexpr noncopyable() = default;
	~noncopyable() = default;

private:
	noncopyable(const noncopyable*) = delete;
	noncopyable& operator=(const noncopyable&) = delete;
};

}

typedef noncopyable_::noncopyable noncopyable;

}

#endif  //_NONCOPYABLE_HPP