#include "WritingInstrument.h"

WritingInstrument::WritingInstrument():brand(NULL)
{
}

WritingInstrument::WritingInstrument(char *brand, uint manYear):maunufYear(manYear)
{
	int size = strlen(brand) + 1;
	this->brand = new char[size];
	strcpy_s(this->brand, size, brand);
}

WritingInstrument::WritingInstrument(const WritingInstrument &obj)
{
	copy(obj);
}

WritingInstrument & WritingInstrument::operator=(const WritingInstrument &other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

WritingInstrument::~WritingInstrument()
{
	clean();
}

void WritingInstrument::clean()
{
	delete[] brand;
	brand = NULL;
}

void WritingInstrument::copy(const WritingInstrument &obj)
{
	int size = strlen(obj.brand) + 1;
	brand = new char[size];
	strcpy_s(brand, size, obj.brand);

	maunufYear = obj.maunufYear;
}
