#ifndef __WRITINGINSTRUMENT__HEADER__INCLUDED__
#define __WRITINGINSTRUMENT__HEADER__INCLUDED__

#include <iostream>
#define uint unsigned long

class WritingInstrument
{
protected:
	char* brand;
	uint maunufYear;

protected:
	//big four
	WritingInstrument();
	WritingInstrument(char*, uint);
	WritingInstrument(const WritingInstrument&);
	WritingInstrument& operator= (const WritingInstrument&);
	~WritingInstrument();

private:
	void clean();
	void copy(const WritingInstrument&);



};


#endif // !__WRITINGINSTRUMENT__HEADER__INCLUDED__
