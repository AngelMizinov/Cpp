#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int INPUT_MAX_SIZE = 1024;
const int WORD_MAX_SIZE = 128;

bool equalWords(char* str1, char* str2)
{
	if (strlen(str1) != strlen(str2))
		return false;

	int i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return false;
		++i;
	}
	return true;
}

bool isInSortedStr(char** str,int size, char* word)
{
	int element = 0;
	while (element<size)
	{
		if (equalWords(str[element], word))
			return true;
		++element;
	}
	return false;
}

int main()
{
	char* inputStr = new char[INPUT_MAX_SIZE + 1];

	cin.getline(inputStr, INPUT_MAX_SIZE);

	int i = 0, numOfWords = 1;
	while (inputStr[i])
	{
		if (inputStr[i] == ' ')
			++numOfWords;
		++i;
	}

	char** sortedStr = new char*[numOfWords + 1];
	
	for (int i = 0; i < numOfWords; ++i)
		sortedStr[i] = new char[WORD_MAX_SIZE + 1];

	bool isInStr = false;
	i = 0;
	int indexOfMin = 0, j = 0;
	char* currentWord = new char[WORD_MAX_SIZE + 1];
	int sortArrInd = 0;

	for (int i = 0; i < 5; ++i)
	{
		while (inputStr[i])
		{
			if (inputStr[i] == ' ')
			{
				++i;
				//problem 1
				j = 0;
				while (inputStr[i] != ' ' && inputStr[i] != '\0')
				{
					currentWord[j] = inputStr[i];
					++j;
					++i;
				}
				currentWord[j] = '\0';

				if (isInSortedStr(sortedStr,numOfWords, currentWord))
					isInStr = true;

				//problem 2
				if (inputStr[indexOfMin] > inputStr[i] && !isInStr)
					indexOfMin = i;
			}
			++i;
		}
		

	}

	return 0;
}