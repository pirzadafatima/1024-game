
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int col, row;
const int columns = 4;
const int rows = 4;
int arr[rows][columns];
int checkarr[rows][columns];

void InitializeBoard(int Arr[][columns]);
void PrintBoard(int Arr[][columns]);
void Move();
void InitializeNewBlock(int Arr[][columns]);
void RightShift(int Arr[][columns]);
void LeftShift(int Arr[][columns]);
void DownShift(int Arr[][columns]);
void UpShift(int Arr[][columns]);
bool SearchBoard(int Arr[][columns]);
bool GameOver(int Arr[][columns]);
bool SearchEmptyBlock(int Arr[][columns]);
void CopyArray(int Arr[][columns], int charr[][columns]);
bool HelpCompare(int Arr[][columns], int ca[][columns]);

int main()
{
	srand(time(0));

	InitializeBoard(arr);
	PrintBoard(arr);
	
	while ((!SearchBoard(arr)) && (!GameOver(arr)))
	{
		CopyArray(arr, checkarr);

		Move();
		system("cls");

		if (SearchEmptyBlock(arr) && HelpCompare(arr, checkarr))
		{
			InitializeNewBlock(arr);
			PrintBoard(arr);
		}
		else
		{
			PrintBoard(arr);
			continue;
		}

	}

	system("pause");
	return 0;
}

void InitializeBoard(int Arr[][columns])
{
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < columns; col++)
		{
			Arr[row][col] = 0;
		}

	}

	int temp1 = 0, temp2 = 0;
	for (int k = 0; k < 2; k++)
	{
		row = rand() % 4;
		col = rand() % 4;

		if (temp1 == row && temp2 == col)
		{
			k = k - 1;
			continue;
		}
		temp1 = row;
		temp2 = col;
		Arr[row][col] = 1 + (rand() % 2);
	}

}

void PrintBoard(int Arr[][columns])
{
	for (int row = 0; row < 4; row++)
	{
		cout << "---------------------" << endl;
		for (int col = 0; col < columns; col++)
		{
			if (Arr[row][col] == 0)
				cout << "|    ";
			else
			{
				if ((Arr[row][col]) >= 10)
					cout << "|  " << Arr[row][col];
				else if ((Arr[row][col]) >= 100)
					cout << "|" << Arr[row][col];
				else if ((Arr[row][col]) >= 1000)
					cout << "|" << Arr[row][col];
				else if ((Arr[row][col]) < 10 && (Arr[row][col]) >0)
					cout << "|   " << Arr[row][col];

			}

		}
		cout << "|" << endl;
	}
	cout << "---------------------" << endl;
}

void Move()
{
	char move;

	cout << "Press 'l' to swipe left." << endl;
	cout << "Press 'r' to swipe right." << endl;
	cout << "Press 'u' to swipe up." << endl;
	cout << "Press 'd' to swipe down." << endl;
	cout << "Enter your move: ";
	cin >> move;
	cout << endl;

	while (move != 'l' && move != 'r' && move != 'd' && move != 'u')
	{
		cout << "You can only move left(l), right(r), up(u) or down(d). Enter your move again. " << endl;
		cin >> move;
	}

	if (move == 'r')
		RightShift(arr);
	if (move == 'l')
		LeftShift(arr);
	if (move == 'u')
		UpShift(arr);
	if (move == 'd')
		DownShift(arr);
}

void InitializeNewBlock(int Arr[][columns])
{
	row = rand() % 4;
	col = rand() % 4;
	if (Arr[row][col] == 0)
	{
		Arr[row][col] = 1 + (rand() % 2);
	}
	else
		InitializeNewBlock(Arr);
}

void RightShift(int Arr[][columns])
{

	for (row = 0; row < 4; row++)
	{
		int placeholder = 3;
		for (int col = 2; col >= 0; col--)
		{
			if (Arr[row][col] != 0)
			{
				if (Arr[row][col + 1] == 0 || Arr[row][col + 1] == Arr[row][col])
				{
					if (Arr[row][placeholder] == Arr[row][col])
					{
						Arr[row][placeholder] = (Arr[row][placeholder]) + (Arr[row][placeholder]);
						Arr[row][col] = 0;
						placeholder--;
					}
					else
					{
						if (Arr[row][placeholder] == 0)
						{
							Arr[row][placeholder] = Arr[row][col];
							Arr[row][col] = 0;
						}
						else
						{
							Arr[row][--placeholder] = Arr[row][col];
							Arr[row][col] = 0;
						}
					}
				}
				else placeholder--;
			}
		}
	}
}


void LeftShift(int Arr[][columns])
{

	for (row = 0; row < 4; row++)
	{
		int placeholder = 0;
		for (int col = 1; col <= 3; col++)
		{
			if (Arr[row][col] != 0)
			{
				if (Arr[row][col - 1] == 0 || Arr[row][col - 1] == Arr[row][col])
				{
					if (Arr[row][placeholder] == Arr[row][col])
					{
						Arr[row][placeholder] = (Arr[row][placeholder]) + (Arr[row][placeholder]);
						Arr[row][col] = 0;
						placeholder++;
					}
					else
					{
						if (Arr[row][placeholder] == 0)
						{
							Arr[row][placeholder] = Arr[row][col];
							Arr[row][col] = 0;
						}
						else
						{

							Arr[row][++placeholder] = Arr[row][col];
							Arr[row][col] = 0;

						}
					}
				}
				else placeholder++;
			}
		}
	}

}

void DownShift(int Arr[][columns])
{

	for (col = 0; col < 4; col++)
	{
		int placeholder = 3;
		for (row = 2; row >= 0; row--)
		{
			if (Arr[row][col] != 0)
			{
				if (Arr[row + 1][col] == 0 || Arr[row + 1][col] == Arr[row][col])
				{
					if (Arr[placeholder][col] == Arr[row][col])
					{
						Arr[placeholder][col] = (Arr[placeholder][col]) + (Arr[placeholder][col]);
						Arr[row][col] = 0;
						placeholder--;
					}
					else
					{
						if (Arr[placeholder][col] == 0)
						{
							Arr[placeholder][col] = Arr[row][col];
							Arr[row][col] = 0;
						}
						else
						{
							Arr[--placeholder][col] = Arr[row][col];
							Arr[row][col] = 0;
						}
					}
				}
				else placeholder--;
			}
		}
	}
}

void UpShift(int Arr[][columns])
{

	for (int col = 0; col < 4; col++)
	{
		int placeholder = 0;
		for (row = 1; row <= 3; row++)
		{
			if (Arr[row][col] != 0)
			{
				if (Arr[row - 1][col] == 0 || Arr[row - 1][col] == Arr[row][col])
				{
					if (Arr[placeholder][col] == Arr[row][col])
					{
						Arr[placeholder][col] = (Arr[placeholder][col]) + (Arr[placeholder][col]);
						Arr[row][col] = 0;
						placeholder++;
					}
					else
					{
						if (Arr[placeholder][col] == 0)
						{
							Arr[placeholder][col] = Arr[row][col];
							Arr[row][col] = 0;
						}
						else
						{
							Arr[++placeholder][col] = Arr[row][col];
							Arr[row][col] = 0;
						}
					}
				}
				else placeholder++;

			}
		}
	}

}

bool SearchBoard(int Arr[][columns])
{
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			if (Arr[row][col] == 1024)
			{
				cout << "\n\n\t\t\tYou Won" << endl;
				return true;
			}
			else
				continue;
		}
	}

	return false;
}

bool GameOver(int Arr[][columns])
{
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 3; col++)
		{
			if ((arr[row][col] == 0) || (arr[row][col + 1] == 0) || (arr[col + 1][row] == 0))
			{
				return false;
			}
			if ((arr[row][col] == arr[row][col + 1]) || (arr[col][row] == arr[col + 1][row]))
			{
				return false;
			}


		}
	}
	cout << "\n\n\t\t\tGame Over" << endl;
	return true;

}
bool SearchEmptyBlock(int Arr[][columns])
{
	bool result;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			if (Arr[row][col] == 0)
			{
				return true;

			}
			else
			{
				result = false;
				continue;
			}
		}
	}
	return result;
}

void CopyArray(int Arr[][columns], int charr[][columns])
{
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			charr[row][col] = Arr[row][col];
		}
	}
}

bool HelpCompare(int Arr[][columns], int charr[][columns])
{
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			if (charr[row][col] != Arr[row][col]) 
			 return true;
		}
	}
	return false; 
}
