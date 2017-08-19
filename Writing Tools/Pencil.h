#ifndef __PENCIL__HEADER__INCLUDED__
#define __PENCIL__HEADER__INCLUDED__

#include "WritingInstrument.h"

class Pencil: public WritingInstrument
{
private:
	short substance;

public:
	Pencil();
	Pencil(char*, uint, short);

public:
	void SetSubstance(short);
	short GetSubstance() const;

	void SetBrand(char*);
	char* GetBrand() const;

	friend std::istream& operator >> (std::istream&, Pencil&);
	friend std::ostream& operator <<(std::ostream&, const Pencil&);
};

#endif // !__PENCIL__HEADER__INCLUDED__

