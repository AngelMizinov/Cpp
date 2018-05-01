#ifndef __WALLET__HEADER__INCLUDED__
#define __WALLET__HEADER__INCLUDED__

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Constants.h"
#include ".\Transaction.h"

struct Wallet
{
	char ownerName[MAX_NAME_SIZE];
	unsigned int id;
	double fiatMoney;
};

//CHECK FOR VALID INFORMATION
bool IsCapitalLetter(char);
bool ValidName(char [MAX_NAME_SIZE]); //check if the name starts with capital letters
bool ValidID(unsigned int); //check if the ID exist in our database

unsigned int GenerateUniqueID(); //generate ID and writes it in "ids.dat"

Wallet ReadWallet(); //read wallet from the console

int AddWallet();
int WalletInfo();
int AttractInvestors();
Wallet ReturnWalletByID(unsigned int);

//HELPERS
bool CheckOfsFileIsOpen(std::ofstream&,const char*);
bool CheckIfsFileIsOpen(std::ifstream&, const char*);

//returns balance in fiatMoney when the bool variable is false
//and balance in fmiCoins when the bool variable is true
double WalletBalance(unsigned int,bool); 

int OverwriteWalletsFile();

//help functions for report file name
int numOfDigits(unsigned int);
void returnDigits(unsigned int, int*);
char* numberToStr(unsigned int);

char* ReturnReportFileName(unsigned int, long long);

void OutputTenInvestors(Wallet [10], int);

#endif // !__WALLET__HEADER__INCLUDED__
