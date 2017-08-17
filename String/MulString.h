#pragma once

#include <iostream>

class MulString
{
private:
	char* myStr;
	int size;

public:
	MulString();  /// MulString A;
	MulString(char* inputStr, int inputSize); //Mulstring A("adada",6);
	~MulString();
	MulString(const MulString& obj); 
	MulString& operator=(const MulString& other); 
	
	friend std::ostream& operator<<(std::ostream& output,const MulString& obj);
	friend std::istream& operator>>(std::istream& input, MulString& obj);

	MulString& operator*=(int k);
	
	friend bool operator!=(const MulString& A, const MulString& B);
	
	MulString& operator%=(const MulString& other);

	MulString& operator+=(const MulString& other);

	MulString& operator/=(const MulString& other);

};

MulString operator*(const MulString& A , int k);

MulString operator%(const MulString& A, const MulString& B);

MulString operator+(const MulString& A, const MulString& B);

MulString operator/(const MulString& A, const MulString& B);

bool operator==(const MulString& A, const MulString& B);