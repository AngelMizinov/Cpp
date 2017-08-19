#include "Marker.h"
#include "Pencil.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	std::ofstream ofs("branded.txt");

	if (!ofs.is_open())
	{
		cout << "ERROR! Cannot open the file!\n";
		return 1;
	}

	cout << "markers: (brand,manufacture year,color) \n";
	Marker marks[5];

	for (int i = 0; i < 5; ++i)
		cin >> marks[i];
	
	cout << endl;
	cout << "pencils: (brand, manufacture year,substance) \n";
	Pencil pens[5];

	for (int i = 0; i < 5; ++i)
		cin >> pens[i];
	
	char* generalBrand = new char[1024];
	cout << "general brand: ";
	//cin.getline(generalBrand, 1024);
	cin >> generalBrand;

	for (int i = 0; i < 5; ++i)
	{
		if (strcmp(generalBrand, marks[i].GetBrand()) == 0) //check if is the same brand
			ofs << marks[i] << endl; //calls Marker::operator<< to output in the file
	}

	for (int i = 0; i < 5; ++i)
	{
		if (strcmp(generalBrand, pens[i].GetBrand()) == 0) //again check if is the same brand
			ofs << pens[i] << endl; //calls Pencil::operator<< to output in the file
	}

	ofs.close();

	return 0;
}
