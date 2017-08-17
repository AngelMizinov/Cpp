#ifndef __TIMESTAMP__HEADER__INCLUDED__
#define __TIMESTAMP__HEADER__INCLUDED__

#include <iostream>
#include <ctime>

#define ulong unsigned long

class Timestamp
{
private:
	ulong stamp;

public:
	Timestamp();
	Timestamp(ulong stamp);

public:
	ulong GetValue() const;
	void SetValue(ulong stamp);

	//< > <= >= == !=
	friend bool operator<(const Timestamp&, const Timestamp&);
	friend bool operator==(const Timestamp&, const Timestamp&);
};

bool operator>(const Timestamp&, const Timestamp&);
bool operator<=(const Timestamp&, const Timestamp&);
bool operator>=(const Timestamp&, const Timestamp&);

bool operator!=(const Timestamp&, const Timestamp&);

#endif // !__TIMESTAMP__HEADER__INCLUDED__
