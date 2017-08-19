#ifndef __MARKER__HEADER__INCLUDED__
#define __MARKER__HEADER__INCLUDED__

#include "WritingInstrument.h"

class Marker : public WritingInstrument
{
private:
	char* color;

public:
	//big four
	Marker();
	Marker(char*, uint, char*);
	Marker(const Marker&);
	Marker& operator=(const Marker&);
	~Marker();

private:
	void clean();
	void copy(const Marker&);

public:
	void SetBrand(char*);
	char* GetBrand() const;

	friend std::istream& operator >> (std::istream&, Marker&);
	friend std::ostream& operator << (std::ostream&, const Marker&);

};

#endif // !__MARKER__HEADER__INCLUDED__

