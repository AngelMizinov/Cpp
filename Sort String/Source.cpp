#include <iostream>

using std::cout;
using std::cin;
using std::endl;

bool isChar(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return true;
	return false;
}

//
//if is capital letter return 2
//if is lowercase letter return 1
//if is not letter return 0
short isLetter(char c)
{
	if (c >= 'A' && c <= 'Z')
		return 2;
	if (c >= 'a' && c <= 'z')
		return 1;
	return 0;
}

const int INPUT_MAX_SIZE = 1024;

int main()
{
	char* text = new char[INPUT_MAX_SIZE + 1];
	cin.getline(text, INPUT_MAX_SIZE);

	int length = strlen(text);

	
	short arr[INPUT_MAX_SIZE];
	for (int i = 0; i < length; ++i)
		arr[i] = 0;

	//
	// first for Capital letters
	// for arr:
	//	if some letter is unused is 2
	//	if some letter is used   is 1
	//	if is not letter for use is 0
	//
	if (isLetter(text[0]) == 2) //if is Capital letter
		arr[0] = 2;

	int i = 0;
	while (text[i])
	{
		if (text[i] == ' ')
		{
			++i;
			if (isLetter(text[i]) == 2)
				arr[i] = 2;
		}
		++i;
	}

	i = 0;
	char min = 'Z';
	int j, k;
	while (text[i])
	{
		if (arr[i] == 1 || arr[i] == 2) // if arr[i] is Capital letter and is first letter of the word
		{
			j = 0;
			while (j < length)
			{
				if (arr[j] == 2)
				{
					if (text[j] <= min)
					{
						min = text[j];
						k = j;
					}
				}
				++j;
			}
			arr[k] = 1; // mark this letter for used
			while (isChar(text[k]))
			{
				cout << text[k];
				++k;
			}
			cout << " ";
			min = 'Z';
		}
		++i;
	}

	//
	// now for lowercase
	//

	for (int i = 0; i < length; ++i)
		arr[i] = 0;

	if (isLetter(text[0]) == 1) // if the letter is lowercase
		arr[0] = 2;

	i = 0;
	while (text[i])
	{
		if (text[i] == ' ')
		{
			++i;
			if (isLetter(text[i]) == 1)
				arr[i] = 2;
		}
		++i;
	}

	i = 0, min = 'z';
	while (text[i])
	{
		if (arr[i] == 1 || arr[i] == 2) // if arr[i] is Capital letter and is first letter of the word
		{
			j = 0;
			while (j < length)
			{
				if (arr[j] == 2)
				{
					if (text[j] <= min)
					{
						min = text[j];
						k = j;
					}
				}
				++j;
			}
			arr[k] = 1; // mark this letter for used
			while (isChar(text[k]))
			{
				cout << text[k];
				++k;
			}
			cout << " ";
			min = 'z';
		}
		++i;
	}

	cout << endl;

	delete[] text;

	return 0;
}
