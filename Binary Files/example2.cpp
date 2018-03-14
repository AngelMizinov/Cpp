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

const int MAX_INPUT_SIZE = 1024;

struct Student
{
	char* name;
	unsigned int fn;
};

int ReadFromFile(const char* file_name)
{
	std::ifstream ifs(file_name, std::ios::binary);

	if (!ifs.is_open())
	{
		cout << "ERROR!Cannot open the file!\n";
		return 1;
	}

	Student buffer;
	int length;
	while (!ifs.eof())
	{
		ifs.read((char*)&length, sizeof(int));
		
		if (ifs.eof())
			break;

		if (!ifs.good())
		{
			cout << "Error while reading the file!\n";
			return 1;
		}

		buffer.name = new char[length + 1];
		ifs.read(buffer.name, length);

		buffer.name[length] = '\0';

		if (!ifs.good())
		{
			cout << "Error while reading the file!\n";
			return 1;
		}

		ifs.read((char*)&buffer.fn, sizeof(unsigned int));

		if (!ifs.good())
		{
			cout << "Error while reading the file!\n";
			return 1;
		}

		cout << buffer.name << " " << buffer.fn << endl;

		delete[] buffer.name;
	}

	ifs.close();
	return 0;
}

int WriteInFile(const char* file_name)
{
	int N;
	cout << "Enter number of the students:\n";
	cin >> N;
	cin.ignore();

	std::ofstream ofs(file_name, std::ios::binary | std::ios::app);
	
	if (!ofs.is_open())
	{
		cout << "ERROR!Cannot open the file!\n";
		return 1;
	}

	Student *students = new Student[N];
	int* lengths = new int[N];

	char* buffer = new char[MAX_INPUT_SIZE];
	
	for (int i = 0; i < N; ++i)
	{
		cout << "Enter student name:\n";
		cin.getline(buffer, MAX_INPUT_SIZE - 1);
		
		lengths[i] = strlen(buffer);
		students[i].name = new char[lengths[i] + 1];
		strcpy_s(students[i].name, lengths[i] + 1, buffer);

		cout << "Enter student fn:\n";
		cin >> students[i].fn;
		cin.ignore();

		memset(buffer, 0, MAX_INPUT_SIZE - 1);

	}

	for (int i = 0; i < N; ++i)
	{
		ofs.write((const char*)&lengths[i], sizeof(int));

		ofs.write(students[i].name, lengths[i]);
		
		ofs.write((const char*)&students[i].fn, sizeof(unsigned int));

		if (!ofs.good())
		{
			cout << "Error while writing in the file!\n";
			return 1;
		}

	}
	
	for (int i = 0; i < N; ++i)
		delete[] students[i].name;
	
	delete[] students;
	
	delete[] lengths;
	
	delete[] buffer;

	ofs.close();
	return 0;
}

int main()
{
	//WriteInFile("data.bin");
	ReadFromFile("data.bin");
	
	return 0;
}
