//
//Напишете програма,която записва N на брой числа в двоичен файл, въведени от клавиатурата
//и след това отпечатва на екрана всяко трето число от файла.
//

#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	std::ofstream ofs("numbers.bin", std::ios::binary | std::ios::trunc);

	if (!ofs.is_open())
	{
		cout << "ERROR!Cannot open the file!\n";
		return 1;
	}

	int N;
	cout << "Enter N:\n";
	cin >> N;
	
	int num;
	for (int i = 0; i < N; ++i)
	{
		cin >> num;
		ofs.write((const char*)&num, sizeof(int));

		if (!ofs.good()) //проверяваме дали информацията е записана успешно във файла
		{
			cout << "Error while writing in the file!\n";
			break;
		}
	}

	ofs.close();

	std::ifstream ifs("numbers.bin", std::ios::binary); //отваряме същия файл, но този път да четем от него

	if (!ifs.is_open())
	{
		cout << "ERROR!Cannot open the file!\n";
		return 1;
	}

	int buffer;
	while (!ifs.eof())
	{
		//
		//преместваме get pointer-а с 2 числа от тип int,
		//за да може да стои точно "пред" 3-тото число,което трябва да прочетем
		//
		ifs.seekg(2 * sizeof(int), std::ios::cur); 

		ifs.read((char*)&buffer, sizeof(int));

		if (ifs.eof())
			break;

		if (!ifs.good())
		{
			cout << "Error while reading in the file!\n";
			break;
		}

		cout << buffer << " ";
	}
	
	ifs.close();

	return 0;
}
