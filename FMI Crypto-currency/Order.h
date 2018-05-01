#ifndef __ORDER__HEADER__INCLUDED__
#define __ORDER__HEADER__INCLUDED__

#include "Constants.h"
#include "Wallet.h"

struct Order
{
	Type type;
	unsigned int walletId;
	double fmiCoins;
};

void MakeDefault(Order&);
bool isDefault(Order&);

const char* TypeOrderToChar(Type&); //return type as a char*
Type ReadTypeOrder(); //read type from the console(as a char*) and converts it to Type

int MakeOrder();
void HelperOrder(Order*, size_t); //helper for MakeOrder()
int OverwriteOrdersFile(Order&);

bool CheckIfTheNameExist(char [MAX_NAME_SIZE]); //check if the given name exist in "wallets.dat"

int GenerateOrderReport(Order&);


#endif // !__ORDER__HEADER__INCLUDED__
