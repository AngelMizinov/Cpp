#ifndef __APPOINTMENT__HEADER__INCLUDED__
#define __APPOINTMENT__HEADER__INCLUDED__

#include "Timestamp.h"

class Appointment
{
private:
	Timestamp t;
	char* description;

public:
	//big four
	Appointment();
	Appointment(Timestamp, char*);
	Appointment(const Appointment&);
	Appointment& operator=(const Appointment&);
	~Appointment();

private:
	void clean();
	void copy(const Appointment&);

public:
	char* GetDescription() const;
	void SetDescription(char*);

public:
	friend std::istream& operator>>(std:: istream&, Appointment&);
	friend std::ostream& operator<<(std::ostream& ,const Appointment&);


};

#endif // !__APPOINTMENT__HEADER__INCLUDED__

