#include "Battle.h"
#include "ConstTable.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "ConstTable.h"
using namespace std;

Battle::Battle(Player & player) :player(player) {
	unsigned seed = static_cast<unsigned>(time(NULL));
	srand(seed);
	if (player.getNowPos() == 3)
	{
		//����BOSS
		Equipment *equipment = new Equipment();
		equipment->initEquipment(rand() % SHOPLISTCOUNT, rand() % 20 + 1);
		monster = new Monster(equipment);
		monster->setName("BOSS: DRAGON!");
		monster->setLife(DRAGONLIFE);
		monster->setPower(DRAGONPOWER);
		monster->setProtectPower(DRAGONPROTECTPOWER);
		monster->setMoney(DRAGONMONEY);
		monster->setExp(DRAGONEXP);
		monster->setLevel(DRAGONLEVEL);
		this->backupPlayerLife = player.getLife();
		this->backupPlayerEnergy = player.getEnergy();
	}
	else
	{
		//�������������Ʒ
		Equipment *equipment = new Equipment();
		equipment->initEquipment(rand() % SHOPLISTCOUNT, rand() % 20 + 1);
		//������ɹ���
		monster = new Monster(equipment);
		monster->setName(MONSTERLIST[rand() % MONSTERLISTCOUNT]);
		monster->setLife(static_cast<int> (INITMONSTERLIFE*(1 + player.getLevel()*0.1)));
		monster->setPower(static_cast<int> (INITMONSTERPOWER*(1 + player.getLevel()*0.1)));
		monster->setProtectPower(static_cast<int> (INITMONSTERPOWER*(1 + player.getLevel()*0.1)));
		monster->setMoney(static_cast<int> (INITMONSTERMONEY*(1 + player.getLevel()*0.1)));
		monster->setExp(static_cast<int> (INITMONSTEREXP*(1 + player.getLevel()*0.1)));
		monster->setLevel(player.getLevel() - 1);
		this->backupPlayerLife = player.getLife();
		this->backupPlayerEnergy = player.getEnergy();
	}
}

Battle::~Battle()
{
	if (monster != NULL)
		delete monster;
}

void Battle::beginBattle()
{
	unsigned seed = static_cast<unsigned>(time(NULL));
	int nowAttacker = PLAYER;
	//��ʼ���������
	srand(seed);
	showAttrPanel();
	cout << monster->getName() << ":��Ҫ��ʼ�����ˣ�" << endl;
	cout << player.getName() << ":come on!" << endl;
	cout << endl;
	while (!judegeEnd()) {
		if (nowAttacker == PLAYER) {
			cout << "��ѡ�񹥻���ʽ:1.����  2.��ͨ����" << endl;
			cout << "������ѡ��:";
			int attackType = 0;
			int totalPower = player.getPower();
			cin >> attackType;
			if (attackType == 1) {
				if (player.getEnergy() < player.getSkillComsume())
				{
					cout << "MP�����޷�ʹ�ü��ܣ��Զ�תΪ��ͨ����" << endl;
					Sleep(1000);
				}
				else {
					int playerLevel = player.getLevel();
					if (playerLevel > 8)
					{
						cout << "��ʹ���˼��� �ٲ�����";
						Sleep(1000);
					}
					if (playerLevel > 5)
					{
						cout << "��ʹ���˼��� С��ɵ�";
						Sleep(1000);
					}
					if (playerLevel > 2)
					{
						cout << "��ʹ���˼��� ţ��С��";
						Sleep(1000);
					}
					totalPower += player.getSkillPower();
					player.setEnergy(player.getEnergy() - player.getSkillComsume());
				}
			}
			int injuryValue = totalPower - monster->getProtectPower();
			//�������̫�ߣ�������Ҫ����˺�������Ϸ���ܽ���
			if (injuryValue <= 0)
				injuryValue =static_cast<int>(ceil(player.getPower()*0.6));
			monster->setLife(monster->getLife() - injuryValue);
			cout << player.getName() << "��" << monster->getName() << "��� " << injuryValue << " ���˺���" << endl;
			Sleep(1000);
		}
		else
		{
			bool isMiss = false;
			//�������ֵ����������ֵ�Ƚϣ����������ʧ��,����ҿ�
			isMiss = player.getMiss() > (rand() % (MISSUPPER - MISSLOWER)) + MISSLOWER;
			if (!isMiss) {
				int injuryValue = monster->getPower() - player.getProtectPower();
				//�������̫�ߣ�������Ҫ����˺�������Ϸ���ܽ���
				if (injuryValue <= 0)
					injuryValue =static_cast<int>(ceil(monster->getPower()*0.6));
				player.setLife(player.getLife() - injuryValue);
				cout << monster->getName() << "��" << player.getName() << "��� " << injuryValue << " ���˺���" << endl;
				Sleep(1000);
			}
			else
			{
				cout <<"���Խý������ɹ����ܹ��޵Ĺ�����" << endl;
				Sleep(1000);
			}

		}
		//ת��������
		nowAttacker = -nowAttacker;
		showAttrPanel();
	}
}

int Battle::judegeEnd()
{
	if (player.getLife()<=0)
		return -1;
	if (monster->getLife()<=0)
		return 1;
	return 0;
}

bool Battle::showResult()
{
	cout << "����ս��������" << endl;
	if (judegeEnd() == 1) {
		player.setExp(player.getExp() + monster->getExp());
		player.setMoney(player.getMoney() + monster->getMoney());
		//����һ��װ������Ϊ���˳�ս��ϵͳ��ʱ��MONSTER����������Ʒָ����ʧ
		Equipment *backupEquipmet = new Equipment(*(monster->getItem()));
		player.pushBag(backupEquipmet);
		cout << "��ϲ����ʤ��!" << endl;;
		cout << "��ã�" << "���飺" << monster->getExp() <<
			"\t��Ǯ:" << monster->getMoney() <<
			"\t��Ʒ��" << monster->getItem()->getId() << endl;
		Sleep(1500);
		//�ص����֮ǰ��һ��ͼ��������һ��ͼ������ʧ
		return true;
	}
	else {
		cout << "����ս�����������������ִ帴�" << endl;
		Sleep(1000);
		player.initRevive(backupPlayerLife, backupPlayerEnergy);
		//���ĵ�ͼ�����޸���������
		return false;
	}
}

void Battle::showAttrPanel()
{
	if (monster->getLife() < 0)
		monster->setLife(0);
	if (player.getLife() < 0)
		player.setLife(0);
	system("cls");
	cout << monster->getName() << ":" << endl;
	monster->showInfo();
	cout << endl;
	cout << player.getName() << ":" << endl;
	player.showInfo();
	cout << endl;
}
