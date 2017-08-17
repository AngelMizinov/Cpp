#include "Timestamp.h"

Timestamp::Timestamp():stamp(time_t(NULL))
{
	//..
}

Timestamp::Timestamp(ulong stamp):stamp(stamp)
{
	//..
}	

ulong Timestamp::GetValue() const
{
	return stamp;
}

void Timestamp::SetValue(ulong stamp)
{
	this->stamp = stamp;
}

bool operator<(const Timestamp &lhs, const Timestamp &rhs)
{
	return lhs.stamp < rhs.stamp ? true : false;
}

bool operator==(const Timestamp &lhs, const Timestamp &rhs)
{
	return lhs.stamp == rhs.stamp ? true : false;
}

bool operator>(const Timestamp &lhs, const Timestamp &rhs)
{
	return (!(lhs < rhs) && !(lhs == rhs)) ? true : false;
}

bool operator<=(const Timestamp &lhs, const Timestamp &rhs)
{
	return (lhs < rhs || lhs == rhs) ? true : false;
}

bool operator>=(const Timestamp &lhs, const Timestamp &rhs)
{
	return (lhs > rhs || lhs == rhs) ? true : false;
}

bool operator!=(const Timestamp &lhs, const Timestamp &rhs)
{
	return !(lhs == rhs) ? true : false;
}
