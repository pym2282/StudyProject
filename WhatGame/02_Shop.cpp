#include "stdafx.h"
#define BUG cout << "버그다아아아아다아아아" << endl; Sleep(1000);
enum ItemType { None, Weapon, Armor };
enum State { Shop, Player, Equip };
struct Item
{
	ItemType type;
	string name;
	UINT attackState;
	UINT guardState;
	UINT count;
	State position;
	UINT price;
};

struct Data
{
	int money;
	vector<Item> shopweapons;
	vector<Item> shoparmors;
	vector<Item> equip;
	vector<Item> invenweapons;
	vector<Item> invenarmors;
	vector<Item>::iterator ShopWeapon = shopweapons.begin();
	vector<Item>::iterator ShopArmor = shoparmors.begin();
	vector<Item>::iterator InvenWeapon = invenweapons.begin();
	vector<Item>::iterator InvenArmor = invenarmors.begin();
};

void MainScreen(Data &data);
void ShopScreen(Data &data);
void WeaponShop(Data &data);
void ArmorShop(Data &data);
void Inventory(Data &data);
void Equipment(Data &data);
void ShopItemState(int &count, Item &item);



int main()
{
 	int screenIndex = 0;
	int money = 100000;
	vector<Item> weapons;
	vector<Item> armors;
	vector<Item> equip;

	Item FirstWeapon = { Weapon, "첫번째 무기",	10, 0, 3, Shop, 1000 };
	Item SecondWeapon = { Weapon, "두번째 무기",20, 0, 2, Shop, 2000 };
	Item ThirdWeapon = { Weapon, "세번째 무기", 30, 0, 1, Shop, 3000 };
															  
	Item FirstArmor = { Armor, "첫번째 방어구", 0, 10, 1, Shop, 1000 };
	Item SecondArmor = { Armor, "두번째 방어구",0, 20, 2, Shop, 2000 };
	Item ThirdArmor = { Armor, "세번째 방어구", 0, 30, 3, Shop, 3000 };
	
	Item EquipWeapon = { Weapon,"맨손",1,0 ,0,Equip,0};
	Item EquipArmor = { Weapon,"몸통",0,1,0,Equip,0 };

	weapons.push_back(FirstWeapon);
	weapons.push_back(SecondWeapon);
	weapons.push_back(ThirdWeapon);
	armors.push_back(FirstArmor);
	armors.push_back(SecondArmor);
	armors.push_back(ThirdArmor);

	equip.push_back(EquipWeapon);
	equip.push_back(EquipArmor);

	Data data = { money,weapons ,armors, equip};

	while (true)
	{
		MainScreen(data);
	}

	system("pause");
	return 0;
}
void MainScreen(Data &data)
{
	int index;
	system("cls");
	cout << "----<판타지 세상에 오신것을 환영합니다>----" << endl << endl;
	cout << "(1) 상점(구매)  (2) 인벤토리(판매)  (3)장착" << endl << endl;
	cout << "-------------------------------------------" << endl << endl;
	cout << "입력 : ";
	cin >> index;
	switch (index)
	{
	case 1: ShopScreen(data); break;
	case 2: Inventory(data); break;
	case 3: Equipment(data); break;
	}
}
void ShopScreen(Data &data)
{
	int index;
	system("cls");
	cout << "------------------<상 점>------------------" << endl << endl;
	cout << "(1) 무기      (2) 방어구      (0) 돌아가기" << endl << endl;
	cout << "-------------------------------------------" << endl << endl;
	cout << "입력 : ";
	cin >> index;
	switch (index)
	{
	case 0: MainScreen(data); break;
	case 1: WeaponShop(data); break;
	case 2: ArmorShop(data); break;
	}
}
void WeaponShop(Data &data)
{
	int index;
	int count = 0;
	system("cls");
	cout << "--------------<상 점 :: 무기>--------------" << endl;
	for (int i = 0; i < data.shopweapons.size(); i++)
	{
		ShopItemState(count, data.ShopWeapon[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "구매 하실 무기의 번호를 입력하세요 돌아가기 키는 0번" << endl;
	cout << "소지금 : " << data.money << endl;
	cout << "-------------------------------------------" << endl;
	cout << "입력 : ";
	cin >> index;
	switch (index)
	{
	case 0: ShopScreen(data); return; break;
	}
	if (index > data.shopweapons.size())
	{
		cout << "다시 입력해 주세용" << endl;
		Sleep(1000);
		WeaponShop(data);
	}
	else if (data.money >= data.shopweapons[index - 1].price)
	{
		bool haveItem = false;
		data.money -= data.shopweapons[index - 1].price;

		for (int i = 0; i < data.invenweapons.size(); i++)
		{
			if (data.InvenWeapon[i].name == data.ShopWeapon[index - 1].name)	// 구매한 아이템이 아이템창에 이미 있다면
			{
				data.InvenWeapon[i].count++;									// 갯수를 늘린다
				haveItem = true;
			}
		}
		if (!haveItem)														// 아이템 창에 없으면
		{
			data.invenweapons.push_back(data.shopweapons[index - 1]);		// 아이템창에 전송
			data.InvenWeapon = data.invenweapons.begin();					// 초기화
			data.InvenWeapon[data.invenweapons.size() - 1].count = 1;	// 갯수 초기화
		}
		data.ShopWeapon[index - 1].count--;
		if (data.ShopWeapon[index - 1].count == 0)
			data.shopweapons.erase(data.ShopWeapon + index - 1);
		data.ShopWeapon = data.shopweapons.begin();
		WeaponShop(data);
	}
}
void ArmorShop(Data &data)
{
	int index;
	int count = 0;
	system("cls");
	cout << "--------------<상 점 :: 방어구>--------------" << endl;
	for (int i = 0; i < data.shoparmors.size(); i++)
	{
		ShopItemState(count, data.ShopArmor[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "구매 하실 무기의 번호를 입력하세요 돌아가기 키는 0번" << endl;
	cout << "소지금 : " << data.money << endl;
	cout << "-------------------------------------------" << endl;
	cout << "입력 : ";
	cin >> index;
	switch (index)
	{
	case 0: ShopScreen(data); return; break;
	}
	if (index > data.shoparmors.size())
	{
		cout << "다시 입력해 주세용" << endl;
		Sleep(1000);
		ArmorShop(data);
	}
	else if (data.money >= data.shoparmors[index - 1].price)
	{
		bool haveItem = false;
		data.money -= data.shoparmors[index - 1].price;

		for (int i = 0; i < data.invenarmors.size(); i++)
		{
			if (data.InvenArmor[i].name == data.ShopArmor[index - 1].name)	// 구매한 아이템이 아이템창에 이미 있다면
			{
				data.InvenArmor[i].count++;									// 갯수를 늘린다
				haveItem = true;
			}
		}
		if (!haveItem)														// 아이템 창에 없으면
		{
			data.invenarmors.push_back(data.shoparmors[index - 1]);		// 아이템창에 전송
			data.InvenArmor = data.invenarmors.begin();					// 초기화
			data.InvenArmor[data.invenarmors.size() - 1].count = 1;	// 갯수 초기화
		}
		data.ShopArmor[index - 1].count--;
		if (data.ShopArmor[index - 1].count == 0)
			data.shoparmors.erase(data.ShopArmor + index - 1);
		data.ShopArmor = data.shoparmors.begin();
		ArmorShop(data);
	}
}
void Inventory(Data &data)
{
	int index;
	int count = 0;
	system("cls");
	cout << "--------------<판 매>--------------" << endl;
	for (int i = 0; i < data.invenweapons.size(); i++)
	{
		ShopItemState(count, data.InvenWeapon[i]);
	}	
	for (int i = 0; i < data.invenarmors.size(); i++)
	{
		ShopItemState(count, data.InvenArmor[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "판매 하실 무기의 번호를 입력하세요 돌아가기 키는 0번" << endl;
	cout << "소지금 : " << data.money << endl;
	cout << "-------------------------------------------" << endl;
	cout << "입력 : ";
	cin >> index;
	switch (index)
	{
	case 0: MainScreen(data); return; break;
	}
	if (index > data.invenweapons.size())
	{
		index -= data.invenweapons.size();		
		if (index > data.invenarmors.size())
		{
			cout << "다시 입력해 주세용" << endl;
			Sleep(1000);
			Inventory(data);
		}
		else // 금액이 맞다면
		{
			bool haveItem = false;
			data.money += data.invenarmors[index - 1].price;

			for (int i = 0; i < data.shoparmors.size(); i++)						// 반대편의 갯수만큼
			{
				if (data.ShopArmor[i].name == data.InvenArmor[index - 1].name)	// 구매한 아이템이 아이템창에 이미 있다면
				{
					data.ShopArmor[i].count++;									// 갯수를 늘린다
					haveItem = true;
				}
			}
			if (!haveItem)														// 아이템 창에 없으면
			{
				data.shoparmors.push_back(data.invenarmors[index - 1]);		// 반대편에 전송
				data.ShopArmor = data.shoparmors.begin();						// 초기화
				data.ShopArmor[data.shoparmors.size() - 1].count = 1;	// 갯수 초기화
			}
			data.InvenArmor[index - 1].count--;								//본인 하나 제거
			if (data.InvenArmor[index - 1].count == 0)							//본인 0개면 제거
				data.invenarmors.erase(data.InvenArmor + index - 1);
			data.InvenArmor = data.invenarmors.begin();
			Inventory(data);
		}
	}
	else 
	{
		if (index > data.invenweapons.size())
		{
			cout << "다시 입력해 주세용" << endl;
			Sleep(1000);
			Inventory(data);
		}
		else // 금액이 맞다면
		{
			bool haveItem = false;
			data.money += data.invenweapons[index - 1].price;

			for (int i = 0; i < data.shopweapons.size(); i++)						// 반대편의 갯수만큼
			{
				if (data.ShopWeapon[i].name == data.InvenWeapon[index - 1].name)	// 구매한 아이템이 아이템창에 이미 있다면
				{
					data.ShopWeapon[i].count++;									// 갯수를 늘린다
					haveItem = true;
				}
			}
			if (!haveItem)														// 아이템 창에 없으면
			{
				data.shopweapons.push_back(data.invenweapons[index - 1]);		// 반대편에 전송
				data.ShopWeapon = data.shopweapons.begin();						// 초기화
				data.ShopWeapon[data.shopweapons.size() - 1].count = 1;	// 갯수 초기화
			}
			data.InvenWeapon[index - 1].count--;								//본인 하나 제거
			if (data.InvenWeapon[index - 1].count == 0)							//본인 0개면 제거
				data.invenweapons.erase(data.InvenWeapon + index - 1);
			data.InvenWeapon = data.invenweapons.begin();
			Inventory(data);
		}
	}
}
void ShopItemState(int &count, Item &item)
{
	count++;
	cout << "-------------------------------------------" << endl;
	cout << "번호 : " << count << endl;
	cout << "이름 : " << item.name.c_str() << endl;
	cout << "공격력 : " << item.attackState << endl;
	cout << "방어력 : " << item.guardState << endl;
	cout << "수량 : " << item.count << endl;
	cout << "가격 : " << item.price << endl;
}
void EquipState(int count, Item &item)
{
	cout << "-------------------------------------------" << endl;
	cout << "번호 : " << count << endl;
	cout << "이름 : " << item.name.c_str() << endl;
	cout << "공격력 : " << item.attackState << endl;
	cout << "방어력 : " << item.guardState << endl;
	cout << "수량 : " << item.count << endl;
}
void Equipment(Data &data) 
{
	int count = 0;
	int index;
	system("cls");
	cout << "------------------<장 비>------------------" << endl;
	cout << "무기   : " << data.equip[0].name.c_str() << endl;
	cout << "방어구 : " << data.equip[1].name.c_str() << endl;
	cout << "-------------------------------------------" << endl;	
	cout << "공격력 : " << data.equip[0].attackState << endl;
	cout << "방어력 : " << data.equip[1].guardState << endl;
	cout << "-------------------------------------------" << endl;
	for (int i = 0; i < data.invenweapons.size(); i++)
	{
		EquipState((i + 1), data.InvenWeapon[i]);
	}
	for (int i = 0; i < data.invenarmors.size(); i++)
	{
		EquipState(i+ 1 + data.invenweapons.size(), data.InvenArmor[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "장착할 아이템의 번호를 입력해 주세요 돌아가는 키는 0 번입니다" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "입력 : ";
	cin >> index;
	if(index == 0)
	MainScreen(data);
	else if (index > data.invenarmors.size() + data.invenweapons.size()) {
		cout << "다시 입력해 주세요" << endl;
		Sleep(1000);
	}
	else
	{
		bool haveItem = false;
		if (index > data.invenweapons.size())	//방어구 장착
		{
			index -= data.invenweapons.size();			
			for (int i = 0; i < data.invenarmors.size(); i++)
			{
				if (data.invenarmors[i].name == data.equip[1].name)
				{
					haveItem = true;
					data.invenarmors[i].count++;
				}
			}
			if (data.equip[1].count != 0 && !haveItem)
			data.invenarmors.push_back(data.equip[1]);

			data.equip[1] = data.invenarmors[index - 1];

			data.InvenArmor = data.invenarmors.begin();
			if (data.invenarmors[index - 1].count > 1)
				data.invenarmors[index - 1].count--;
			else
				data.invenarmors.erase(data.InvenArmor + index - 1);


			data.InvenArmor = data.invenarmors.begin();
			Equipment(data);
		}
		else
		{
			for (int i = 0; i < data.invenweapons.size(); i++)
			{
				if (data.invenweapons[i].name == data.equip[0].name)
				{
					haveItem = true; 
					data.invenweapons[i].count++;
				}
			}
			if(data.equip[0].count != 0 && !haveItem)
			data.invenweapons.push_back(data.equip[0]);	

			data.equip[0] = data.invenweapons[index - 1];

			data.InvenWeapon = data.invenweapons.begin();
			if (data.invenweapons[index - 1].count > 1)
				data.invenweapons[index - 1].count--;
			else
				data.invenweapons.erase(data.InvenWeapon + index - 1);

			data.InvenWeapon = data.invenweapons.begin();
			Equipment(data);
		}
	}
}