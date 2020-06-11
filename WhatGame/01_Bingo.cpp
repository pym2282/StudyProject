#include "stdafx.h"

void CheckBingo(int number[], int  &bingoCount)
{
	bool bBingo = true;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
			if (number[i + j * 5] != 0)	 bBingo = false; // 가로 빙고
		if (bBingo)	bingoCount++; bBingo = true;
	}

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
			if (number[i * 5 + j] != 0)	 bBingo = false; // 세로 빙고
		if (bBingo)	bingoCount++; bBingo = true;
	}

	for (int i = 0; i < 5; i++)
		if (number[i * 6] != 0)	 bBingo = false; // 대각선 빙고1
	if (bBingo)	bingoCount++; bBingo = true;

	for (int i = 0; i < 5; i++)
		if (number[4 + i * 4] != 0)	 bBingo = false; // 대각선 빙고2
	if (bBingo)	bingoCount++; bBingo = true;
}

int main()
{
	int bingoCount = 0;
	int number[25];
	int inputNumber = 0;
	srand(time(NULL));

	// initialization
	for (int i = 0; i < 25; i++) 
		number[i] = i + 1;

	// shuffle
	for (int i = 0; i < 100; i++)
	{
		int r1 = rand() % 25;
		int r2 = rand() % 25;
		
		int temp = number[r1];
		number[r1] = number[r2];
		number[r2] = temp;
	}

	while (true)
	{
		cout << "현재 빙고 상황 : " << bingoCount << " 빙고" << endl;
		cout << "-----------------------------------" << endl;

		// Render Screen
		for (int i = 0; i < 5; i++)		
		{
			for (int j = 0; j < 5; j++)
			{
				if (number[j + i * 5] == 0)
					cout << "○" << "\t";
				else
					cout << number[j + i * 5] << "\t";
			}
			cout << endl << endl;;
		}
		cout << "-----------------------------------" << endl;
		cout << "숫자를 입력해 주세요 : ";
		cin >> inputNumber;

		//Scan Bingo
		bingoCount = 0;
		for (int i = 0; i < 25; i++)	
		{
			if (number[i] == inputNumber)
				number[i] = 0;
		}
		CheckBingo(number, bingoCount);
		system("cls");

	}
	system("pause");
	return 0;
}