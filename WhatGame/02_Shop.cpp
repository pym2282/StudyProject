#include "stdafx.h"
#define BUG cout << "���״پƾƾƾƴپƾƾ�" << endl; Sleep(1000);
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

	Item FirstWeapon = { Weapon, "ù��° ����",	10, 0, 3, Shop, 1000 };
	Item SecondWeapon = { Weapon, "�ι�° ����",20, 0, 2, Shop, 2000 };
	Item ThirdWeapon = { Weapon, "����° ����", 30, 0, 1, Shop, 3000 };
															  
	Item FirstArmor = { Armor, "ù��° ��", 0, 10, 1, Shop, 1000 };
	Item SecondArmor = { Armor, "�ι�° ��",0, 20, 2, Shop, 2000 };
	Item ThirdArmor = { Armor, "����° ��", 0, 30, 3, Shop, 3000 };
	
	Item EquipWeapon = { Weapon,"�Ǽ�",1,0 ,0,Equip,0};
	Item EquipArmor = { Weapon,"����",0,1,0,Equip,0 };

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
	cout << "----<��Ÿ�� ���� ���Ű��� ȯ���մϴ�>----" << endl << endl;
	cout << "(1) ����(����)  (2) �κ��丮(�Ǹ�)  (3)����" << endl << endl;
	cout << "-------------------------------------------" << endl << endl;
	cout << "�Է� : ";
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
	cout << "------------------<�� ��>------------------" << endl << endl;
	cout << "(1) ����      (2) ��      (0) ���ư���" << endl << endl;
	cout << "-------------------------------------------" << endl << endl;
	cout << "�Է� : ";
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
	cout << "--------------<�� �� :: ����>--------------" << endl;
	for (int i = 0; i < data.shopweapons.size(); i++)
	{
		ShopItemState(count, data.ShopWeapon[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "���� �Ͻ� ������ ��ȣ�� �Է��ϼ��� ���ư��� Ű�� 0��" << endl;
	cout << "������ : " << data.money << endl;
	cout << "-------------------------------------------" << endl;
	cout << "�Է� : ";
	cin >> index;
	switch (index)
	{
	case 0: ShopScreen(data); return; break;
	}
	if (index > data.shopweapons.size())
	{
		cout << "�ٽ� �Է��� �ּ���" << endl;
		Sleep(1000);
		WeaponShop(data);
	}
	else if (data.money >= data.shopweapons[index - 1].price)
	{
		bool haveItem = false;
		data.money -= data.shopweapons[index - 1].price;

		for (int i = 0; i < data.invenweapons.size(); i++)
		{
			if (data.InvenWeapon[i].name == data.ShopWeapon[index - 1].name)	// ������ �������� ������â�� �̹� �ִٸ�
			{
				data.InvenWeapon[i].count++;									// ������ �ø���
				haveItem = true;
			}
		}
		if (!haveItem)														// ������ â�� ������
		{
			data.invenweapons.push_back(data.shopweapons[index - 1]);		// ������â�� ����
			data.InvenWeapon = data.invenweapons.begin();					// �ʱ�ȭ
			data.InvenWeapon[data.invenweapons.size() - 1].count = 1;	// ���� �ʱ�ȭ
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
	cout << "--------------<�� �� :: ��>--------------" << endl;
	for (int i = 0; i < data.shoparmors.size(); i++)
	{
		ShopItemState(count, data.ShopArmor[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "���� �Ͻ� ������ ��ȣ�� �Է��ϼ��� ���ư��� Ű�� 0��" << endl;
	cout << "������ : " << data.money << endl;
	cout << "-------------------------------------------" << endl;
	cout << "�Է� : ";
	cin >> index;
	switch (index)
	{
	case 0: ShopScreen(data); return; break;
	}
	if (index > data.shoparmors.size())
	{
		cout << "�ٽ� �Է��� �ּ���" << endl;
		Sleep(1000);
		ArmorShop(data);
	}
	else if (data.money >= data.shoparmors[index - 1].price)
	{
		bool haveItem = false;
		data.money -= data.shoparmors[index - 1].price;

		for (int i = 0; i < data.invenarmors.size(); i++)
		{
			if (data.InvenArmor[i].name == data.ShopArmor[index - 1].name)	// ������ �������� ������â�� �̹� �ִٸ�
			{
				data.InvenArmor[i].count++;									// ������ �ø���
				haveItem = true;
			}
		}
		if (!haveItem)														// ������ â�� ������
		{
			data.invenarmors.push_back(data.shoparmors[index - 1]);		// ������â�� ����
			data.InvenArmor = data.invenarmors.begin();					// �ʱ�ȭ
			data.InvenArmor[data.invenarmors.size() - 1].count = 1;	// ���� �ʱ�ȭ
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
	cout << "--------------<�� ��>--------------" << endl;
	for (int i = 0; i < data.invenweapons.size(); i++)
	{
		ShopItemState(count, data.InvenWeapon[i]);
	}	
	for (int i = 0; i < data.invenarmors.size(); i++)
	{
		ShopItemState(count, data.InvenArmor[i]);
	}
	cout << "-------------------------------------------" << endl;
	cout << "�Ǹ� �Ͻ� ������ ��ȣ�� �Է��ϼ��� ���ư��� Ű�� 0��" << endl;
	cout << "������ : " << data.money << endl;
	cout << "-------------------------------------------" << endl;
	cout << "�Է� : ";
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
			cout << "�ٽ� �Է��� �ּ���" << endl;
			Sleep(1000);
			Inventory(data);
		}
		else // �ݾ��� �´ٸ�
		{
			bool haveItem = false;
			data.money += data.invenarmors[index - 1].price;

			for (int i = 0; i < data.shoparmors.size(); i++)						// �ݴ����� ������ŭ
			{
				if (data.ShopArmor[i].name == data.InvenArmor[index - 1].name)	// ������ �������� ������â�� �̹� �ִٸ�
				{
					data.ShopArmor[i].count++;									// ������ �ø���
					haveItem = true;
				}
			}
			if (!haveItem)														// ������ â�� ������
			{
				data.shoparmors.push_back(data.invenarmors[index - 1]);		// �ݴ��� ����
				data.ShopArmor = data.shoparmors.begin();						// �ʱ�ȭ
				data.ShopArmor[data.shoparmors.size() - 1].count = 1;	// ���� �ʱ�ȭ
			}
			data.InvenArmor[index - 1].count--;								//���� �ϳ� ����
			if (data.InvenArmor[index - 1].count == 0)							//���� 0���� ����
				data.invenarmors.erase(data.InvenArmor + index - 1);
			data.InvenArmor = data.invenarmors.begin();
			Inventory(data);
		}
	}
	else 
	{
		if (index > data.invenweapons.size())
		{
			cout << "�ٽ� �Է��� �ּ���" << endl;
			Sleep(1000);
			Inventory(data);
		}
		else // �ݾ��� �´ٸ�
		{
			bool haveItem = false;
			data.money += data.invenweapons[index - 1].price;

			for (int i = 0; i < data.shopweapons.size(); i++)						// �ݴ����� ������ŭ
			{
				if (data.ShopWeapon[i].name == data.InvenWeapon[index - 1].name)	// ������ �������� ������â�� �̹� �ִٸ�
				{
					data.ShopWeapon[i].count++;									// ������ �ø���
					haveItem = true;
				}
			}
			if (!haveItem)														// ������ â�� ������
			{
				data.shopweapons.push_back(data.invenweapons[index - 1]);		// �ݴ��� ����
				data.ShopWeapon = data.shopweapons.begin();						// �ʱ�ȭ
				data.ShopWeapon[data.shopweapons.size() - 1].count = 1;	// ���� �ʱ�ȭ
			}
			data.InvenWeapon[index - 1].count--;								//���� �ϳ� ����
			if (data.InvenWeapon[index - 1].count == 0)							//���� 0���� ����
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
	cout << "��ȣ : " << count << endl;
	cout << "�̸� : " << item.name.c_str() << endl;
	cout << "���ݷ� : " << item.attackState << endl;
	cout << "���� : " << item.guardState << endl;
	cout << "���� : " << item.count << endl;
	cout << "���� : " << item.price << endl;
}
void EquipState(int count, Item &item)
{
	cout << "-------------------------------------------" << endl;
	cout << "��ȣ : " << count << endl;
	cout << "�̸� : " << item.name.c_str() << endl;
	cout << "���ݷ� : " << item.attackState << endl;
	cout << "���� : " << item.guardState << endl;
	cout << "���� : " << item.count << endl;
}
void Equipment(Data &data) 
{
	int count = 0;
	int index;
	system("cls");
	cout << "------------------<�� ��>------------------" << endl;
	cout << "����   : " << data.equip[0].name.c_str() << endl;
	cout << "�� : " << data.equip[1].name.c_str() << endl;
	cout << "-------------------------------------------" << endl;	
	cout << "���ݷ� : " << data.equip[0].attackState << endl;
	cout << "���� : " << data.equip[1].guardState << endl;
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
	cout << "������ �������� ��ȣ�� �Է��� �ּ��� ���ư��� Ű�� 0 ���Դϴ�" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "�Է� : ";
	cin >> index;
	if(index == 0)
	MainScreen(data);
	else if (index > data.invenarmors.size() + data.invenweapons.size()) {
		cout << "�ٽ� �Է��� �ּ���" << endl;
		Sleep(1000);
	}
	else
	{
		bool haveItem = false;
		if (index > data.invenweapons.size())	//�� ����
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