#include "Marker.h"

Marker::Marker():color(NULL)
{
}

Marker::Marker(char *brand, uint manYear, char *color):WritingInstrument(brand,manYear)
{
	int size = strlen(color) + 1;
	this->color = new char[size];
	strcpy_s(this->color, size, color);
}

Marker::Marker(const Marker &obj)
{
	copy(obj);
}

Marker & Marker::operator=(const Marker &other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

Marker::~Marker()
{
	clean();
}

void Marker::clean()
{
	delete[] color;
	color = NULL;
}

void Marker::copy(const Marker &obj)
{
	color = new char[strlen(obj.color) + 1];
	strcpy_s(color, strlen(obj.color) + 1, obj.color);
}

void Marker::SetBrand(char *br)
{
	brand = new char[strlen(br) + 1];
	strcpy_s(brand, strlen(br) + 1, br);
}

char * Marker::GetBrand() const
{
	return brand;
}

std::istream & operator >> (std::istream &input, Marker &obj)
{
	char* buffer = new char[1024];

	input >> buffer;
	int size = strlen(buffer) + 1;
	obj.brand = new char[size];
	strcpy_s(obj.brand, size, buffer);
	
	input >> obj.maunufYear;

	input >> buffer;
	size = strlen(buffer) + 1;
	obj.color = new char[size];
	strcpy_s(obj.color, size, buffer);

	delete[] buffer;

	return input;
}

std::ostream & operator<<(std::ostream &output, const Marker &obj)
{
	output << obj.brand << " " << obj.maunufYear << " " << obj.color;
	return output;
}
