#include "MulString.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	char* text = new char[6];
	text = "ABCDE";

	MulString A(text, 5);

	MulString B = A;
	cout << "B = A (c-ctor): " << B << endl; // B = A (c-ctor): ABCDE 

	MulString C;
	C = A;
	cout << "C = A (operator=): " << C << endl; // C = A (operator=): ABCDE

	B = C;
	cout << "if B==C // B = C : " << B << endl; // if B==C // B = C : ABCDE

	B *= 4;
	cout << "B*=4 : " << B << endl; // B*=4 : ABCDEABCDEABCDEABCDE

	MulString D("Text", 4);
	D = D * 4;
	cout <<"D*4 : "<< D << endl; // D*4 : TextTextTextText 

	cout << A << " " << B << " "; // ABCDE ABCDEABCDEABCDEABCDE 
	cout <<"A!=B : "<< (A != B) << endl; // A!=B : 1

	MulString obj1("Text", 4);
	MulString obj2("Text", 4);
	cout << "\"Text\" != \"Text\" : " << (obj1 != obj2) << endl; // "Text" != "Text" : 0

	cout << "\"Text\" == \"Text\" : " << (obj1 == obj2) << endl; // "Text" == "Text" : 1

	MulString M("ABCDCFEA", 8);
	MulString N("CDEF", 4);
	M %= N;
	cout <<"\"ABCDCFEA\" %= \"CDEF\" : "<< M << endl; // "ABCDCFEA" %= "CDEF" : ABCDEF

	MulString P("ABCDAE", 6);
	MulString Q("DBCAAEEA", 8);
	MulString R;
	R = P % Q;
	cout << "R = \"ABCDAE\" % \"DBCAAEEA\" : " << R << endl; // R = "ABCDAE" % "DBCAAEEA" : ABCDE

	MulString name1("Angel ", 6);
	MulString name2("Mizinov", 7);
	name1 += name2;
	cout << "\"Angel \" += \"Mizinov\" : " << name1 << endl; // "Angel " += "Mizinov" : Angel Mizinov

	MulString name3("Samo ", 5);
	MulString name4("Levski", 6);
	MulString name5(" !!!", 4);
	MulString name;
	name = name3 + name4 + name5;
	cout << "name = \"Samo \" + \"Levski\" + \" !!!\" : " << name << endl; // name = "Samo " + "Levski" + " !!!" : Samo Levski !!!

	MulString a("ABCDFG", 6);
	MulString b("BCDHJ", 5);
	a /= b;
	cout << "\"ABCDFG\" / \"BCDHJ\" : " << a << endl; // "ABCDFG" / "BCDHJ" : AFG

	MulString c("ACFKL", 5);
	MulString d;
	d = b / c;
	cout << " d = \"BCDHJ\" / \"ACFKL\" : " << d << endl; // d = "BCDHJ" / "ACFKL" : BDHJ

	MulString e;
	cout << "cin>> " << endl;
	cin >> e;
	cout << e << endl;
	
	delete[] text;
	
	return 0;
}
