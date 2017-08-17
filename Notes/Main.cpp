#include "Appointment.h"
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;


int main()
{
	std::ifstream ifs("calendar.txt");

	if (!ifs.is_open())
	{
		cout << "ERROR! Cannot open the file\n";
		return 1;
	}
	
	Appointment buffer;
	
	while (!ifs.eof())
	{
		ifs >> buffer; //call operator>>
		cout << buffer;
	}

	ifs.close();
	
	return 0;
}