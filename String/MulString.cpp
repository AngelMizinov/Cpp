#include "MulString.h"
#include <iostream>

MulString::MulString()
{
	myStr = NULL;
	size = 0;
}

MulString::MulString(char * inputStr, int inputSize)
{
	myStr = new char[inputSize+1];
	size = inputSize;

	int i = 0;
	while (i < size)
		myStr[i++] = inputStr[i];
	
	myStr[i] = '\0';
}

MulString::~MulString()
{
	delete[] myStr;
	myStr = NULL;
}

MulString::MulString(const MulString & obj)
{
	size = obj.size;
	myStr = new char[size+1];

	int i = 0;
	while (i < size)
		myStr[i++] = obj.myStr[i];

	myStr[i] = '\0';
	
}

MulString & MulString::operator=(const MulString & other)
{
	if (this != &other)
	{
		size = other.size;
		myStr = new char[size + 1];

		int i = 0;
		while (i < size)
			myStr[i++] = other.myStr[i];

		myStr[i] = '\0';
	}

	return *this;
}

MulString & MulString::operator*=(int k)
{
	MulString temp = *this;

	size = temp.size * k;
	myStr = new char[size + 1];

	int index = 0;

	for (int i = 1; i <= k; ++i)
	{
		for (int j=0; j < temp.size; ++j)
		{
			myStr[index] = temp.myStr[j];
			++index;
		}
	}
	myStr[size] = '\0';
	
	delete[] temp.myStr;
	temp.myStr = NULL;

	return *this;
}

//--------------------------------------------------------------------------------------------------
//Help Functions for operator %= and operator %

//return number of characters without repeating...
//for example NumOfChars("abbbbccccdddddd") return 4
int NumOfChars(char* input_str) 
{
	int counter = 0;
	for (int i = 0; input_str[i]; ++i)
	{
		if (input_str[i] != input_str[i + 1])
			++counter;
	}
	return counter;
}
//sort string...
//for example SortStr("cdbaab") return "aabbcd"
char* SortStr(char stat_param_str[]) //take statically allocated string for paramater
{
	int size = strlen(stat_param_str);
	bool flag = true;
	// Bubble sort with strings
	for (int i = 0; i < size && flag; ++i)
	{
		flag = false;
		for (int j = 0; j < size - 1; ++j)
		{
			if (stat_param_str[j] > stat_param_str[j + 1])
			{
				std::swap(stat_param_str[j], stat_param_str[j + 1]);
				flag = true;
			}
		}
	}
	return stat_param_str;
}

//Remove duplicate characters...
//for example RemoveDuplChars("ccdcdbabaaa") return "abcd"
char* RemoveDuplChars(char* input_str)
{
	char stat_str[101];
	strcpy(stat_str, input_str);
	SortStr(stat_str); 

	int chars_number = NumOfChars(stat_str);
	char* output_str = new char[chars_number];
	output_str[chars_number] = '\0';

	int i = 0, index = 0;
	while (stat_str[i])
	{
		if (stat_str[i] != stat_str[i + 1] && output_str[index]) //if we have different characters and output_str[index] != '\0'
		{
			output_str[index] = stat_str[i];
			++index;
		}
		++i;
	}
	return output_str;
}

//--------------------------------------------------------------------------------------------------

MulString & MulString::operator%=(const MulString & other)
{
	MulString temp;
	temp.myStr = new char[size + 1];
	temp.size = size;
	
	temp = *this;
	
	int tempSize = strlen(myStr) + strlen(other.myStr);
	delete[] myStr;
	
	*this = temp;
	strcat(myStr, other.myStr);
	size = tempSize;

	delete[] temp.myStr;
	temp.myStr = NULL;

	
	temp.myStr = RemoveDuplChars(myStr);
	temp.size = strlen(temp.myStr);

	*this = temp;
	temp.myStr = NULL;
	
	return *this;
}

MulString & MulString::operator+=(const MulString & other)
{
	MulString temp = *this;
	
	size += strlen(other.myStr);
	myStr = new char[size + 1];

	strcpy(myStr, temp.myStr);
	strcat(myStr, other.myStr);

	return *this;
}

//--------------------------------------------------------------------------------------------------
// Help Function for operator/= && operator/

//Substraction of two strings...
//for example SubstrStrs("ABCDEF","BCDGH") return "AEF"
char* SubstrStrs(char* str1, char* str2)
{
	char* output_str = new char[strlen(str1) + 1];

	bool flag = false;
	int index = 0;
	for (int i = 0; i < strlen(str1); ++i)  // str1[0]...str1[n]
	{
		flag = false;
		for (int j = 0; j < strlen(str2); ++j) // str2[0]...str2[n]
		{
			if (str1[i] == str2[j]) // (check1 is true) if we have the char in str2.. flag = true
				flag = true;
		}
		if (!flag) // if (check1) is false we haven't the char in str2
			output_str[index++] = str1[i];

	}
	output_str[index] = '\0';

	return output_str;
}

//--------------------------------------------------------------------------------------------------

MulString & MulString::operator/=(const MulString & other)
{
	MulString temp = *this;

	temp.myStr = SubstrStrs(myStr, other.myStr);
	
	*this = temp;
	delete[] temp.myStr;
	temp.myStr = NULL;

	return *this;
}

MulString operator*(const MulString & A, int k)
{
	MulString C = A;
	C *= k;
	
	return C;
}

MulString operator%(const MulString & A, const MulString & B)
{
	MulString C = A;
	C %= B;

	return C;
}

MulString operator+(const MulString & A, const MulString & B)
{
	MulString C = A;
	C += B;

	return C;
}

MulString operator/(const MulString & A, const MulString & B)
{
	MulString C = A;
	C /= B;

	return C;
}

std::ostream & operator<<(std::ostream & output, const MulString & obj)
{
	output << obj.myStr;
	return output;
}

std::istream & operator >> (std::istream & input, MulString & obj)
{
	std::cout << "Size of the string: ";
	input >> obj.size;

	obj.myStr = new char[obj.size + 1];

	std::cout << "String: ";
	input >> obj.myStr;

	return input;
}

//--------------------------------------------------------------------------------------------------
//Help Function for operator!=

//Sum of characters
int SumOfChars(char* str)
{
	int sum = 0;
	int i = 0;
	while (str[i])
	{
		sum += str[i];
		++i;
	}
	return sum;
}

//--------------------------------------------------------------------------------------------------

bool operator!=(const MulString & A, const MulString & B)
{
	// true if they have different weight
	int A_sum = SumOfChars(A.myStr);
	int B_sum = SumOfChars(B.myStr);

	return (A_sum != B_sum) ? true : false;
}

bool operator==(const MulString & A, const MulString & B)
{
	return !(A != B);
}