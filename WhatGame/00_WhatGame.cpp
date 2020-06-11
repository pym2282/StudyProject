#include "stdafx.h"

struct Card
{
	int num; 
	void Tonumber()
	{
		char* number;
		switch (num % 13)
		{
		case 0:
			cout << "A";
			break;
		case 10:
			cout << "J";
			break;
		case 11:
			cout << "Q";
			break;
		case 12:
			cout << "K";
			break;
		default:
			cout << num % 13 + 1;
		}



		return;
	}
	char* Tostring()
	{
		char* shape = NULL;
		switch (num / 13)
		{
		case 0:
			shape = (char*)"◆";
			break;
		case 1:
			shape = (char*)"♠";
			break;
		case 2:
			shape = (char*)"♥";
			break;
		case 3:
			shape = (char*)"♣";
			break;
		}
		return shape;
	}
};
void RandomSwap(Card * card);
void Swap(int &a, int &b);

int main()
{
	Card* cards = new Card[52];

	for (int i = 0; i < 52; i++)
	{
		cards[i].num = i;
	}

	int playeranswer;

	for (int GameCount = 0; GameCount < 17; GameCount++) // 게임 시작
	{
		cout << "이름이 기억나지 않는 어떤 게임" << endl;
		cout << "------------------------------" << endl;
		RandomSwap(cards);

		cout << cards[GameCount * 1].Tostring(); cards[GameCount * 1].Tonumber(); cout << "\t";
		cout << cards[GameCount * 1 + 1].Tostring(); cards[GameCount * 1 + 1].Tonumber(); cout << "\t";
		cout << cards[GameCount * 1 + 2].Tostring(); cards[GameCount * 1 + 2].Tonumber(); cout << endl;
		cin >> playeranswer;
	}

	system("pause");
	return 0;
}

void RandomSwap(Card * card) {
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int r1 = rand() % 52;
		int r2 = rand() % 52;
		Swap(card[r1].num, card[r2].num);
	}
}


void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}