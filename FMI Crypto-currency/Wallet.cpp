#include "Wallet.h"

using std::ios;
using std::cout;
using std::cin;
using std::endl;

bool IsCapitalLetter(char c)
{
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}

bool ValidName(char name[MAX_NAME_SIZE])
{
	if (IsCapitalLetter(name[0]))
	{
		int counter = 0;
		while (name[counter])
		{
			if (name[counter] == ' ')
			{
				++counter;
				if (!IsCapitalLetter(name[counter]))
					return false;
				return true;
			}
			++counter;
		}
	}
	if (!IsCapitalLetter(name[0])) //if we have only one word we check it
		return false;
}

bool ValidID(unsigned int ID)
{
	std::ifstream ifs(IDS_FILE, ios::binary);

	if (!ifs.is_open())
	{
		cout << "Cannot open " << IDS_FILE << endl;
		return false;
	}

	unsigned int currID;
	while (!ifs.eof())
	{
		ifs.read((char*)&currID, sizeof(unsigned int));

		if (ifs.eof())
			break;

		if (!ifs.good())
		{
			cout << "Error while reading " << IDS_FILE << endl;
			return false;
		}

		if (ID == currID)
			return true;
	}
	cout << "This ID does not exist! Please try again.\n";
	return false;
}

unsigned int GenerateUniqueID()
{
	//The first part of code is when we open the file for first time
	std::ofstream firstOpenFile(IDS_FILE, ios::binary | ios::app);
	
	if (!CheckOfsFileIsOpen(firstOpenFile, IDS_FILE))
		return ERROR_OPENING_FILE;
	
	firstOpenFile.seekp(0, ios::end);
	int fileSize = firstOpenFile.tellp();

	if (fileSize == 0)
	{
		int firstNum = 0;
		firstOpenFile.write((const char*)&firstNum, sizeof(int));
		firstOpenFile.close();
		return SUCCESS;
	}

	firstOpenFile.close();

	//========================================================================

	std::ifstream ifs(IDS_FILE, ios::binary);

	if (!CheckIfsFileIsOpen(ifs, IDS_FILE))
		return ERROR_OPENING_FILE;
	
	ifs.seekg(-4, ios::end); //move the get-pointer before the last integer
	
	int lastID;
	ifs.read((char*)&lastID, sizeof(int)); //now read the last unsigned integer we had written

	if (!ifs.good())
	{
		cout << "Error while reading " << IDS_FILE << endl;
		ifs.close();
		return ERROR_READING_FILE;
	}

	ifs.close();

    //========================================================================

	std::ofstream ofs(IDS_FILE, ios::binary | ios::app);

	if (!CheckOfsFileIsOpen(ofs, IDS_FILE))
		return ERROR_OPENING_FILE;

	lastID++;
	ofs.write((const char*)&lastID, sizeof(int));

	if (!ofs.good())
	{
		cout << "Error while writing in " << IDS_FILE << endl;
		ofs.close();
		return ERROR_WRITING_FILE;
	}

	ofs.close();
	return lastID;
}

Wallet ReturnWalletByID(unsigned int walletId)
{
	std::ifstream ofs(WALLETS_FILE, ios::binary);

	Wallet buffer;
	while (!ofs.eof())
	{
		ofs.read((char*)&buffer, sizeof(Wallet));

		if (walletId == buffer.id)
			break;
	}
	return buffer;
}

int WalletInfo()
{
	unsigned int walletId;
	cin >> walletId;
	
	if (!ValidID(walletId))
		return ERROR_INVALID_INFORMATION;

	std::ifstream ifs(WALLETS_FILE, std::ios::binary);

	if (!CheckIfsFileIsOpen(ifs, WALLETS_FILE))
		return ERROR_OPENING_FILE;
	
	Wallet currentWallet;
	while (!ifs.eof())
	{
		ifs.read((char*)&currentWallet, sizeof(Wallet));

		if (ifs.eof())
			break;

		if (!ifs.good())
		{
			cout << "Error while reading " << WALLETS_FILE << endl;
			ifs.close();
			return ERROR_READING_FILE;
		}

		if (walletId == currentWallet.id)
			cout << "Name:" << currentWallet.ownerName << "  ";
	}

	cout << WalletBalance(walletId, false) << "BGN  " << WalletBalance(walletId, true) << "fmiCoins" << endl;

	ifs.close();
	return SUCCESS;
}

bool CheckOfsFileIsOpen(std::ofstream &ofs, const char *file_name)
{
	if (!ofs.is_open())
	{
		cout << "Error while opening " << file_name << endl;
		return false;
	}
	return true;
}

bool CheckIfsFileIsOpen(std::ifstream &ifs, const char *file_name)
{
	if (!ifs.is_open())
	{
		cout << "Error while opening " << file_name << endl;
		return false;
	}
	return true;
}

Wallet ReadWallet()
{
	Wallet wallt;
	
	cin >> wallt.fiatMoney;
	
	cin.ignore();
	cin.getline(wallt.ownerName, MAX_NAME_SIZE - 1);

	if (!ValidName(wallt.ownerName) )
		cout << "Invalid name! Please try again.\n";
	
	wallt.id = GenerateUniqueID();

	return wallt;
}

int AddWallet()
{
	Wallet wallt = ReadWallet();

	std::ofstream ofs(WALLETS_FILE, ios::binary | ios::app);
	
	if (!CheckOfsFileIsOpen(ofs, WALLETS_FILE))
		return ERROR_OPENING_FILE;

	ofs.write((const char*)&wallt, sizeof(Wallet));

	if (!ofs.good())
	{
		cout << "Error while writing in " << WALLETS_FILE << endl;
		ofs.close();
		return ERROR_WRITING_FILE;
	}
	
	MakeTransaction(SYSTEM_WALLET_ID,wallt.id,wallt.fiatMoney);

	cout << "Wallet create successfully! Balance: "
		 << std::setprecision(6)
		 << (wallt.fiatMoney / FMICoin) << " FMICoins." << endl;
	
	return SUCCESS;
}

int AttractInvestors()
{
	std::ifstream ifs(WALLETS_FILE, std::ios::binary);

	if (!CheckIfsFileIsOpen(ifs, WALLETS_FILE))
		return ERROR_OPENING_FILE;

	//number of wallets
	ifs.seekg(0, std::ios::end);
	int fileSize = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	int walletsNum = fileSize / sizeof(Wallet);

	Wallet buffer;
	if (walletsNum <= 10)
	{
		for (int i = 0; i < walletsNum; ++i)
		{
			ifs.read((char*)&buffer, sizeof(Wallet));

			cout << buffer.fiatMoney;
			OutputNumOrdersAndTime(buffer.id);
			cout << endl;
		}
	}
	else
	{
		Wallet wallets[10];
		for (int i = 0; i < 10; ++i)
			ifs.read((char*)&wallets[i], sizeof(Wallet));

		OutputTenInvestors(wallets,walletsNum);
	}
	ifs.close();
}

double WalletBalance(unsigned int walletId, bool fmiCoins)
{
	double balance = 0;

	std::ifstream ifs(TRANSACTIONS_FILE, std::ios::binary);

	if (!CheckIfsFileIsOpen(ifs, TRANSACTIONS_FILE))
		return ERROR_OPENING_FILE;

	Transaction currTr;
	while (!ifs.eof())
	{
		ifs.read((char*)&currTr, sizeof(Transaction));

		if (ifs.eof())
			break;

		if (!ifs.good())
		{
			cout << "Error while reading " << TRANSACTIONS_FILE << endl;
			ifs.close();
			return ERROR_READING_FILE;
		}
		if (!fmiCoins)
		{
			if (currTr.senderId != SYSTEM_WALLET_ID)
			{
				if (walletId == currTr.receiverId) //if walletId has received coins
					balance -= currTr.fmiCoins * FMICoin; //we take the fiatMoney on the price of the fmiCoin
				if (walletId == currTr.senderId) //if walletId has sended coins
					balance += currTr.fmiCoins * FMICoin; //we add the fiatMoney on the price of the fmiCoin
			}
			if (walletId == currTr.receiverId && currTr.senderId == SYSTEM_WALLET_ID)
				balance += currTr.fmiCoins * FMICoin; //add the fiatMoney from the creating of the wallet
		}
		else
		{
			if (currTr.senderId != SYSTEM_WALLET_ID)
			{

				if (walletId == currTr.receiverId)
					balance += currTr.fmiCoins; //we add the coins to the balance
				if (walletId == currTr.senderId)
					balance -= currTr.fmiCoins; //we take the coins from the balance
			}
			if (walletId == currTr.receiverId && currTr.senderId == SYSTEM_WALLET_ID)
				balance += currTr.fmiCoins; //add the fiatMoney (in fmiCoins) from the creating of the wallet
		}
	}
	ifs.close();
	return balance;
}

int OverwriteWalletsFile()
{
	std::ifstream ifs(WALLETS_FILE, ios::binary);

	if (!CheckIfsFileIsOpen(ifs, WALLETS_FILE))
		return ERROR_OPENING_FILE;

	//check file size
	ifs.seekg(0, ios::end);
	int fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

	int walletsNum = fileSize / sizeof(Wallet);

	Wallet* allWallets = new Wallet[walletsNum];

	if (allWallets == NULL)
		return ERROR_MEMORY_ALLOCATION;

	//read from file in allWallets
	for (size_t i = 0; i < walletsNum; ++i)
	{
		ifs.read((char*)&allWallets[i], sizeof(Wallet));

		if (!ifs.good())
		{
			cout << "Error while reading " << WALLETS_FILE << endl;
			ifs.close();
			return ERROR_READING_FILE;
		}
	}

	//upgrade wallets
	double newBalance = 0;
	for (size_t i = 0; i < walletsNum; ++i)
	{
		newBalance = WalletBalance(allWallets[i].id, false); //fmiCoins = false (we want return fiatMoney)
		allWallets[i].fiatMoney = newBalance;
	}

	ifs.close();

	//=========================================================================

	std::ofstream ofs(WALLETS_FILE, ios::binary | ios::trunc);

	if (!CheckOfsFileIsOpen(ofs, WALLETS_FILE))
		return ERROR_OPENING_FILE;

	//write upgraded wallets back in the file
	for (size_t i = 0; i < walletsNum; ++i)
	{
		ofs.write((const char*)&allWallets[i], sizeof(Wallet));

		if (!ofs.good())
		{
			cout << "Error while writing in " << WALLETS_FILE << endl;
			ifs.close();
			return ERROR_WRITING_FILE;
		}
	}

	ofs.close();
	delete[] allWallets;
	//return SUCCESS;
}

int numOfDigits(unsigned int num)
{
	int counter = 0;
	while (num != 0)
	{
		++counter;
		num /= 10;
	}
	return counter;
}

void returnDigits(unsigned int num, int* digits)
{
	for (size_t i = 0; num != 0; i++)
	{
		digits[i] = num % 10;
		num /= 10;
	}
}

char* numberToStr(unsigned int num)
{
	int size = numOfDigits(num);
	int* digits = new int[size];

	returnDigits(num, digits);

	char* str = new char[size + 1];

	int index = 0;
	for (int i = size - 1; i >= 0; --i)
	{
		switch (digits[i])
		{
		case 1:str[index] = '1';
			break;
		case 2:str[index] = '2';
			break;
		case 3:str[index] = '3';
			break;
		case 4:str[index] = '4';
			break;
		case 5:str[index] = '5';
			break;
		case 6:str[index] = '6';
			break;
		case 7:str[index] = '7';
			break;
		case 8:str[index] = '8';
			break;
		case 9:str[index] = '9';
			break;
		case 0:str[index] = '0';
			break;
		default:
			break;
		}
		++index;
	}
	str[index] = '\0';

	return str;
}

char* ReturnReportFileName(unsigned int walletId, long long time)
{
	char* fileName = new char[MAX_FILE_NAME_SIZE];

	strcpy(fileName, numberToStr(walletId));
	strcat(fileName, "_");
	strcat(fileName, numberToStr(time));
	strcat(fileName, ".txt");

	return fileName;
}

void OutputTenInvestors(Wallet wallets[10], int walletsNum)
{
	std::ifstream ifs(WALLETS_FILE, std::ios::binary);

	int minIndex = 0;
	Wallet minWallet;
	Wallet buffer;
	while (true)
	{
		if (ifs.eof())
			break;

		minWallet = wallets[0];
		
		//find the min money wallet in the first 10
		for (int i = 0; i < 10; ++i)
		{
			if (minWallet.fiatMoney > wallets[i].fiatMoney)
			{
				minWallet = wallets[i];
				minIndex = i;
			}
		}
	
		ifs.read((char*)&buffer, sizeof(Wallet));

		if (wallets[minIndex].fiatMoney < buffer.fiatMoney)
			wallets[minIndex] = buffer;
	}

	for (int i = 0; i < 10; ++i)
	{
		ifs.read((char*)&wallets[i], sizeof(Wallet));

		cout << wallets[i].fiatMoney;
		OutputNumOrdersAndTime(wallets[i].id);
		cout << endl;
	}

	ifs.close();
}