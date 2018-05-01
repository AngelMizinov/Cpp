#include "Order.h"

using std::cin;
using std::cout;
using std::endl;

void MakeDefault(Order &ord)
{
	ord.type = INVALID_TYPE_ORDER;
	ord.fmiCoins = 0;
	
}

bool isDefault(Order &ord)
{
	if (ord.type == INVALID_TYPE_ORDER && ord.fmiCoins == 0)
		return true;
	return false;
}

const char* TypeOrderToChar(Type &ord)
{
	if (ord == SELL)
		return "SELL";
	if (ord == BUY)
		return "BUY";
	return "INVALID_TYPE_ORDER";
}

Type ReadTypeOrder()
{
	char inputOrder[MAX_TYPE_ORDER_SIZE + 1];
	cin.ignore();
	cin >> inputOrder;

	if (strcmp(inputOrder, "SELL") == 0)
		return SELL;
	if (strcmp(inputOrder, "BUY") == 0)
		return BUY;

	return INVALID_TYPE_ORDER;
}
	
int MakeOrder()
{
	Order ord;
	ord.type = ReadTypeOrder();
	
	//check for valid order type
	if (ord.type == INVALID_TYPE_ORDER)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n'); //discard INT_MAX of number symbols, or until '\n'
		cout << "Invalid type order! Please try again.\n";
		return ERROR_READING_FILE;
	}

	cin >> ord.fmiCoins;
	
	cin >> ord.walletId;

	if(!ValidID(ord.walletId)) //here check if the ID exist i.e. if the wallet exist
		return ERROR_INVALID_INFORMATION;
	
	//check if there are no orders yet and if so, write the first order
	{
		std::ofstream ofs(ORDERS_FILE, std::ios::binary | std::ios::app);

		if (!CheckOfsFileIsOpen(ofs, ORDERS_FILE))
			return ERROR_OPENING_FILE;

		ofs.seekp(0, std::ios::end);
		int fileSize = ofs.tellp();

		ofs.seekp(0, std::ios::beg);

		if (fileSize == 0)
		{
			ofs.write((const char*)&ord, sizeof(Order));

			if (!ofs.good())
			{
				cout << "Error while writing in " << ORDERS_FILE << endl;
				ofs.close();
				return ERROR_WRITING_FILE;
			}
		}
		else
			return OverwriteOrdersFile(ord);
	}
	return SUCCESS;
}

bool CheckIfTheNameExist(char name[MAX_NAME_SIZE])
{
	std::ifstream ifs(WALLETS_FILE, std::ios::binary);

	if (!ifs.is_open())
	{
		cout << "Error while opening " << WALLETS_FILE << endl;
		ifs.close();
		return false;
	}

	bool theNameExist = false;

	Wallet buffer;
	while (!ifs.eof())
	{
		ifs.read((char*)&buffer, sizeof(Wallet));

		if (ifs.eof())
			break;

		if (!ifs.good())
		{
			cout << "Error while reading " << WALLETS_FILE << endl;
			ifs.close();
			return false;
		}

		if (strcmp(name, buffer.ownerName) == 0)
			theNameExist = true;

	}

	if (!theNameExist)
	{
		cout << "There is no wallet with this name!\n";
		return false;
	}

	ifs.close();
	return true;
}

void HelperOrder(Order* orders, size_t ordersNum, Order ord)
{
	bool sameType = true;
	for (size_t i = 0; i <= ordersNum && ord.fmiCoins > 0; i++)
	{
		if (ord.type != orders[i].type && ord.walletId != orders[i].walletId && orders[i].type != INVALID_TYPE_ORDER)
		{
			sameType = false;
			//if our orderer have more fmiCoins
			if (ord.fmiCoins > orders[i].fmiCoins)
			{
				ord.fmiCoins -= orders[i].fmiCoins;
				double priceInFMICoins = orders[i].fmiCoins;
				
				//make transaction
				if (ord.type == SELL)
					MakeTransaction(ord.walletId, orders[i].walletId, priceInFMICoins*FMICoin);
				else //if ord.type == BUY
					MakeTransaction(orders[i].walletId, ord.walletId, priceInFMICoins*FMICoin);

				MakeDefault(orders[i]); //orders[i] is completed
				
			}
			//if our orderer have less fmiCoins
			else if (ord.fmiCoins < orders[i].fmiCoins)
			{
				orders[i].fmiCoins -= ord.fmiCoins; //reduce the other orderer fmiCoins
				double priceInFMICoins = ord.fmiCoins;
				ord.fmiCoins = 0; //the ord is completed

				if (ord.type == SELL)
					MakeTransaction(ord.walletId, orders[i].walletId, priceInFMICoins*FMICoin);
				else
					MakeTransaction(orders[i].walletId, ord.walletId, priceInFMICoins*FMICoin);
			
			}
			//if our order and the buyer order match
			else if (ord.fmiCoins == orders[i].fmiCoins)
			{
				double priceInFMICoins = ord.fmiCoins;
				ord.fmiCoins = 0; //the ord is completed

				if (ord.type == SELL)
					MakeTransaction(ord.walletId, orders[i].walletId, priceInFMICoins*FMICoin);
				else
					MakeTransaction(orders[i].walletId, ord.walletId, priceInFMICoins*FMICoin);

				MakeDefault(orders[i]); //remove orders[i] from our ORDERS_FILE
			}
		}
	}
	if (sameType || ord.fmiCoins > 0)
		orders[ordersNum] = ord;

	orders = NULL;
}

int OverwriteOrdersFile(Order& ord)
{
	double ordererBalance = 0; 

	if (ord.type == SELL)
	{
		ordererBalance = WalletBalance(ord.walletId, true); //return the orderer balance in FMICoins
		
		if (ordererBalance < ord.fmiCoins)
		{
			cout << "You don't have enough fmiCoins!\n";
			return ERROR_INVALID_INFORMATION;
		}
	}
	else
	{
		ordererBalance = WalletBalance(ord.walletId, false); //return the orderer balance in fiatMoney

		if (ordererBalance < ord.fmiCoins*FMICoin)
		{
			cout << "You don't enough money!\n";
			return ERROR_INVALID_INFORMATION;
		}
	}
	
	Order* allOrders;
	size_t ordersNum;

	//read from ORDERS_FILE
	{
		std::ifstream ifs(ORDERS_FILE, std::ios::binary);

		if (!CheckIfsFileIsOpen(ifs, ORDERS_FILE))
		{
			cout << "Cannot open the file!\n";
			return ERROR_OPENING_FILE;
		}

		ifs.seekg(0, std::ios::end);
		int fileSize = ifs.tellg();
		ordersNum = fileSize / sizeof(Order);

		ifs.seekg(0, std::ios::beg);

		//this 1 is one more order for HelperOrder() if the order is the same type
		allOrders = new Order[ordersNum + 1]; 

		if (allOrders == NULL)
			return ERROR_MEMORY_ALLOCATION;

		//read from file in allOrders
		for (int i = 0; i < ordersNum; ++i)
		{
			ifs.read((char*)&allOrders[i], sizeof(Order));

			if (!ifs.good())
			{
				cout << "Error while reading " << ORDERS_FILE << endl;
				ifs.close();
				return ERROR_READING_FILE;
			}
		}

		MakeDefault(allOrders[ordersNum]);

		ifs.close();
	}

	//open for writing TRANSACTIONS_FILE
	std::ofstream ofstr(TRANSACTIONS_FILE, std::ios::binary | std::ios::app);
	{
		if (!CheckOfsFileIsOpen(ofstr, TRANSACTIONS_FILE))
			return ERROR_OPENING_FILE;
	}
	
	HelperOrder(allOrders, ordersNum, ord);

	//write in ORDERS_FILE
	{
		std::ofstream ofs(ORDERS_FILE, std::ios::binary | std::ios::trunc);

		if (!CheckOfsFileIsOpen(ofs, ORDERS_FILE))
			return ERROR_OPENING_FILE;

		for (int i = 0; i < ordersNum + 1; ++i)
		{
			if (!isDefault(allOrders[i]))
			{
				ofs.write((const char*)&allOrders[i], sizeof(Order));

				if (!ofs.good())
				{
					cout << "Error while writing in " << ORDERS_FILE << endl;
					ofs.close();
					return ERROR_WRITING_FILE;
				}
			}
		}
		ofs.close();
		delete[] allOrders;
	}
	ofstr.close();
	
	//upgrade WALLETS_FILE
	OverwriteWalletsFile(); 
	
	GenerateOrderReport(ord);

	return SUCCESS;
}

int GenerateOrderReport(Order& ord)
{
	char* fileName = new char[MAX_FILE_NAME_SIZE];
	
	long long time = ReturnTimeByID(ord.walletId);

	fileName = ReturnReportFileName(ord.walletId, time);
	
	std::ofstream ofs_report(fileName, std::ios::trunc);
	

	if (!CheckOfsFileIsOpen(ofs_report, fileName))
		return ERROR_OPENING_FILE;

	ofs_report << "receiver  |  sender  |  fmiCoins" << endl;

	std::ifstream ifs_tr(TRANSACTIONS_FILE, std::ios::binary);

	if (!CheckIfsFileIsOpen(ifs_tr, TRANSACTIONS_FILE))
		return ERROR_OPENING_FILE;

	int transactionsNum = 0;
	double allMoney = 0;

	Transaction currTr;
	while (!ifs_tr.eof())
	{
		ifs_tr.read((char*)&currTr, sizeof(Transaction));

		if (ifs_tr.eof())
			break;
		
		if (currTr.senderId != SYSTEM_WALLET_ID)
		{
			if (ord.walletId == currTr.receiverId)
			{
				ofs_report << ReturnWalletByID(ord.walletId).ownerName << "     "
					<< ReturnWalletByID(currTr.senderId).ownerName << "	    "
					<< currTr.fmiCoins << endl;

				++transactionsNum;
				allMoney += currTr.fmiCoins;
			}
			if (ord.walletId == currTr.senderId)
			{
				ofs_report << ReturnWalletByID(currTr.receiverId).ownerName << "     "
					<< ReturnWalletByID(ord.walletId).ownerName << "     "
					<< currTr.fmiCoins << endl;

				++transactionsNum;
				allMoney += currTr.fmiCoins;
			}
		}
	}
	
	allMoney *= FMICoin;

	ofs_report << transactionsNum << "     " << allMoney << endl;
	
	delete[] fileName;

	ofs_report.close();
	ifs_tr.close();
	
	return SUCCESS;
}