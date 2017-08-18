#include <iostream>

using std::cout;
using std::cin;
using std::endl;

char grid[20][20];
int n;
int target;
bool way = false;

void init() //input the grid
{
	do
	{
		cout << "n = ";
		cin >> n;
	} while (n < 1 || n > 20);

	do
	{
		cout << "target = ";
		cin >> target;
	} while (target < 0 || target >= n);

	do
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				cin >> grid[i][j];
		}
	} while (grid[0][0] != '0'); //if the initial element is '1' we can't get out from this square 

}

void writeLab() //output the grid with the path marked with '*' (if there is exists such a path)
{
	cout << endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}

void labyrinth(int i, int j)
{
	if (i == target && j == target) //chek if we have reached target
	{
		grid[i][j] = '*';
		way = true;
		writeLab();
	}
	else
	{
		if (i >= 0 && i < n && j >= 0 && j < n)
		{
			if (grid[i][j] == '0')
			{
				grid[i][j] = '*';
				labyrinth(i + 1, j); //one step down
				labyrinth(i, j + 1); //one step right
				labyrinth(i - 1, j); //one step up
				labyrinth(i, j - 1); //one step left
				grid[i][j] = '0'; //we reach this if the current element is '1'
			}
		}
	}
}

int main()
{
	init();

	labyrinth(0, 0);

	if (!way)
		cout << "There is no path.\n";

	return 0;
}