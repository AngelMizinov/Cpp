#include "Pencil.h"

Pencil::Pencil()
{
	//..
}

Pencil::Pencil(char *brand, uint manYear, short subst):WritingInstrument(brand,manYear)
{
	SetSubstance(subst);
}

void Pencil::SetSubstance(short subst)
{
	if (subst >= 0 && subst <= 14)
		substance = subst;
}

short Pencil::GetSubstance() const
{
	return substance;
}

void Pencil::SetBrand(char *br)
{
	brand = new char[strlen(br) + 1];
	strcpy_s(brand, strlen(br) + 1, br);
}

char * Pencil::GetBrand() const
{
	return brand;
}

std::istream & operator >> (std::istream &input, Pencil &obj)
{
	char* buffer = new char[1024];
	
	input >> buffer;
	int size = strlen(buffer) + 1;
	obj.brand = new char[size];
	strcpy_s(obj.brand, size, buffer);

	input >> obj.maunufYear;
	
	int subst;
	input >> subst;
	obj.SetSubstance(subst);

	delete[] buffer;
	
	return input;
}

std::ostream & operator<<(std::ostream &output, const Pencil &obj)
{
	output << obj.brand << " " << obj.maunufYear << " " << obj.substance;
	return output;
}
