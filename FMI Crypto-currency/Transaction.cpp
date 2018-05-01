#include "Transaction.h"

int MakeTransaction(unsigned int senderId, unsigned int receivderId, double fiatMoney)
{
	Transaction tr;
	
	tr.time = time(NULL);
	tr.senderId = senderId;
	tr.receiverId = receivderId;
	tr.fmiCoins = fiatMoney/FMICoin;

	std::ofstream ofs(TRANSACTIONS_FILE, std::ios::binary | std::ios::app);

	if (!CheckOfsFileIsOpen(ofs, TRANSACTIONS_FILE))
		return ERROR_OPENING_FILE;

	ofs.write((const char*)&tr, sizeof(Transaction));

	if (!ofs.good())
	{
		std::cout << "Error while writing in " << TRANSACTIONS_FILE << std::endl;
		return ERROR_READING_FILE;
	}

	ofs.close();
	return SUCCESS;
}

void OutputNumOrdersAndTime(unsigned int walletId)
{
	std::ifstream ifs_tr(TRANSACTIONS_FILE, std::ios::binary);
	if (!CheckIfsFileIsOpen(ifs_tr, TRANSACTIONS_FILE))
		std::cout << "Error while opening " << TRANSACTIONS_FILE << std::endl;

	double ordersNumber = 0;
	bool isFirstOrder = true;
	
	long long firstOrderTime = 0;
	long long lastOrderTime = 0;
	
	Transaction currTr;
	while (ifs_tr.good())
	{
		ifs_tr.read((char*)&currTr, sizeof(Transaction));

		if (ifs_tr.eof())
			break;
		
		if (currTr.senderId != SYSTEM_WALLET_ID)
		{
			if (currTr.receiverId == walletId || currTr.senderId == walletId)
			{
				if (isFirstOrder)
				{
					isFirstOrder = false;
					firstOrderTime = currTr.time;
				}
				++ordersNumber;
				lastOrderTime = currTr.time;
			}
		}
	}
	

	std::cout << "  " << ordersNumber << "  " << firstOrderTime << "  " << lastOrderTime;

	ifs_tr.close();
}

long long ReturnTimeByID(unsigned int walletId)
{
	std::ifstream ifs(TRANSACTIONS_FILE, std::ios::binary);

	if (!CheckIfsFileIsOpen(ifs, TRANSACTIONS_FILE))
		return ERROR_OPENING_FILE;

	long long time = 0;

	Transaction tr;
	while (ifs.good())
	{
		if (ifs.eof())
			break;

		ifs.read((char*)&tr, sizeof(Transaction));

		if (tr.senderId != SYSTEM_WALLET_ID)
		{
			if (tr.receiverId == walletId || tr.senderId == walletId)
				time = tr.time;
		}
	}
	ifs.close();

	return time;
}