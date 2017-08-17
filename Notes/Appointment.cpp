#include "Appointment.h"

const int DESCRIPTION_MAX_SIZE = 1024;

Appointment::Appointment():description(NULL)
{
	//..
}

Appointment::Appointment(Timestamp t, char * descr):t(t)
{
	description = new char[strlen(descr) + 1];
	strcpy_s(description, strlen(descr) + 1, descr);

}

Appointment::Appointment(const Appointment &obj)
{
	copy(obj);
}

Appointment & Appointment::operator=(const Appointment &other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

Appointment::~Appointment()
{
	clean();
}

void Appointment::clean()
{
	delete[] description;
	description = NULL;
}

void Appointment::copy(const Appointment &obj)
{
	t = obj.t;

	int size = strlen(obj.description)+1;
	description = new char[size];
	strcpy_s(description, size, obj.description);
}

char * Appointment::GetDescription() const
{
	return description;
}

void Appointment::SetDescription(char *descr)
{
	int size = strlen(descr) + 1;
	description = new char[size];
	strcpy_s(description, size, descr);
}


std::istream & operator >> (std::istream&input, Appointment &obj) 
{
	char* buffer = new char[1024];
	ulong st;

	input >> st; //read the stamp from the consolle
	input.getline(buffer, 1024); //read the description from the console

	delete[] obj.description;

	obj.description = new char[strlen(buffer) + 1];
	strcpy_s(obj.description, strlen(buffer) + 1, buffer);
	//strcpy(obj.description, buffer);

	obj.t.SetValue(st);

	return input;
}

std::ostream & operator<<(std::ostream& output,const Appointment &obj)
{
	output << obj.t.GetValue() << " ";
	output << obj.description<<'\n';

	return output;
}
