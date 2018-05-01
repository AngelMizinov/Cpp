#include "Menu.h"

void Menu()
{
	char input[MAX_INPUT_SIZE];

	std::cout
		<< "==================================================================="
		<< "\nSelect command:\n"
		<< "add-wallet fiatMoney name\n"
		<< "make-order type fmiCoins walletId\n"
		<< "wallet-info walletId\n"
		<< "attract-investors\n"
		<< "quit\n"
		<< "==================================================================="
		<< std::endl;

	do
	{
		std::cin >> input;

		if (strcmp(input, "quit") == 0)
			break;

		if (strcmp(input, "add-wallet") == 0)
			AddWallet();
		if (strcmp(input, "make-order") == 0)
			MakeOrder();
		if (strcmp(input, "wallet-info") == 0)
			WalletInfo();
		if (strcmp(input, "attract-investors") == 0)
			AttractInvestors();
				

	} while (true);
}
