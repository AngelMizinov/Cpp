//
//Напишете програма, която прочита от стандартния си вход информация за N на брой студенти.
//За всеки - име(символен низ с произволна дължина) и факултетен номер, след което ги сераиализира по подходящ начин
//в двоичен файл, като за стринговете се запазва място с точната им дължина.
//Да се реализира така, че данните да могат да бъдат възстановени обратно, т.е. прочетени от файла.
//

#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

struct Student
{
	char* name;
	unsigned int fn;
};


int main()
{
	std::ofstream ofs("data.bin", std::ios::binary | std::ios::app);

	if (!ofs.is_open())
	{
		cout << "ERROR!Cannot open the file!\n";
		return 1;
	}

	int N;
	cin >> N;
	cin.ignore();

	Student* students = new Student[N];

	char* buffer = new char[1024];
	int length;

	for (int i = 0; i < N; ++i)
	{
		cout << "Enter student name:\n";
		cin.getline(buffer, 1023);

		length = strlen(buffer) + 1;
		students[i].name = new char[length];
		strcpy_s(students[i].name, length, buffer);

		cout << "Enter student fn:\n";
		cin >> students[i].fn;
		cin.ignore();

	}

	for (int i = 0; i < N; ++i)
	{
		length = strlen(students[i].name);

		ofs.write((const char*)&students[i], sizeof(Student));

		if (!ofs.good())
		{
			cout << "Error while writing in the file!\n";
			break;
		}
	}

	ofs.close();
	delete[] buffer;
	
	//
	//Отварям същия файл "data.bin", но този път,за да четем от него.
	//Създаваме текстов файл за писане "example2_textFile.txt" в него, в който пишем информацията от файла "data.bin"
	//
	//--------------------------------------------------------------------------------
	/*

	std::ifstream ifs("data.bin", std::ios::binary | std::ios::app);
	std::ofstream ofs_txt("example2_textFile.txt");

	if (!ifs.is_open() || !ofs_txt.is_open())
	{
	cout << "ERROR!Cannot open the file!\n";
	return 1;
	}

	Student buff;
	buff.name = new char[64];

	while (!ifs.eof())
	{
	ifs.read((char*)&buff, sizeof(Student));

	if (ifs.eof())
	break;

	if (!ifs.good())
	{
	cout << "Error while reading the file!\n";
	return 1;
	}

	ofs_txt << buff.name << " fn: " << buff.fn << endl;

	}

	ifs.close();
	ofs_txt.close();

	*/
	//---------------------------------------------------------------------------------

	for (int i = 0; i < N; ++i)
		delete[] students[i].name;

	delete[] students;

	return 0;
}
