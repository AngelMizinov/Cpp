#ifndef __TRANSACTION__HEADER__INCLUDED__
#define __TRANSACTION__HEADER__INCLUDED__

#include <ctime>

#include "Constants.h"
#include "Wallet.h"
#include "Order.h"

struct Transaction
{
	long long time;
	unsigned int senderId;
	unsigned int receiverId;
	double fmiCoins;
};

int MakeTransaction(unsigned int,unsigned int,double);

void OutputNumOrdersAndTime(unsigned int);

long long ReturnTimeByID(unsigned int);


#endif // !__TRANSACTION__HEADER__INCLUDED__
