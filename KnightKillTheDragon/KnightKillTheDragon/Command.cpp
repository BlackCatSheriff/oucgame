#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <limits>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "Command.h"
#include "Player.h"
#include "ConstTable.h"
#include "Map.h"
#include "Error.h"
#include "Container.h"
#include "Equipment.h"
#include "FileStore.h"
#include "Battle.h"
#include "Utill.h"
#include "ColorContainer.h"
#include "ColorSys.h"
using namespace std;
ColorContainer *c = new ColorSys();
ostringstream oss;
void Command::newGame()
{
	//ɾ��֮ǰ���
	Player::deletePlayer();
	string name;
	Utill::changeForeground('G');
	cout << "���䵽���������ʿ����ȥ��ܶ���������Ĺ����ɣ�" << endl;
	cout << "������֣�";
	Utill::ForegroundALL();
	clearCin();
	cin >> name;
	Player *player = Player::creatPlayer(name, BORNX, BORNY, BORNLIFE, BORNPOWER, BORNEXP, BORNPROTECTPOWER,
		BORNLEVEL, BORNMONEY, BORNENERGY, BORNMISS, BORNSPEED, 0, Container(BAGCOUNTCAPACITY));
	cout << player->getName() << "  ������̼�����ʼ��" << endl;
	Sleep(100);
	system("cls");
	//�������ִ�
	
	//����һ����ͼ���飬Ϊ�˽����ָ֭�봫�ݶ�ά����ʧ�ܣ�����ʹ������ʵ��
	int laji[MAPROW][MAPCOLUMN] = { 0 };
	newerCountry(player,laji);
}

void Command::newerCountry(Player *player, int(&backupMap)[MAPROW][MAPCOLUMN], Container *ware)
{
	//Container wareCon = (backupMap->getWare() ? Container(*backupMap->getWare()) : Container(WARESHOPCAPACITY));
	Container wareCon = (ware ? Container(*ware) : Container(WARESHOPCAPACITY));
	Map map(*player,wareCon);
	if (ware)
		map.setMapData(backupMap);
	int nowPos = 0;
	do
	{
		map.showNowposMap();
		oss << "�ƶ���W A S D  �鿴��������:T  �򿪱���:B  �����棺M";
		c->changeTextColor('Y', oss);
		//oss.str("");
		try {
			//���� w a s d
			char dir, choice;
			dir = _getch();
			//��׼������
			dir=tolower(dir);
			if (dir == 'w' || dir == 'a' || dir == 's' || dir == 'd') {
				//��Ҫ���� mapmove ������Ҫ�з���ֵ
				int moveType = map.mapMove(dir);
				switch (moveType)
				{
				case ROAD:
					map.showNowposMap();
					//���µ�ͼ
					break;
				case WAREHOUSE:
					//ѯ���Ƿ�򿪲ֿ�
					oss << "�Ƿ�򿪲ֿ�? (Y/N)";
					c->changeTextColor('Y', oss);
					//oss.str("");
					clearCin();
					cin >> choice;
					choice=tolower(choice);
					if (choice == 'y')
						wareshop(map,player);
					break;
				case WEAPONHOUSE:
					//ѯ���Ƿ�������
					oss << "�Ƿ�������? (Y/N)";
					c->changeTextColor('Y', oss);
					//oss.str("");
					clearCin();
					cin >> choice;
					choice=tolower(choice);
					if (choice == 'y')
						weapon(player);
						break;

				case HOSPITAL:
					//ѯ���Ƿ����ҽ��
					oss << "�Ƿ����ҽ��? (Y/N)";
					c->changeTextColor('Y', oss);
					//oss.str("");
					clearCin();
					cin >> choice;
					choice=tolower(choice);
					if (choice == 'y')
						hospital(player);
					break;

				case DOOR:
					//�л���ͼ
					nowPos = player->getNowPos();
					if (nowPos == 1)
						map.showMapTwo();
					else if (nowPos == 2 && player->getPos_y() == 0)
						map.showMapOne();
					else if (nowPos == 2 && player->getPos_y() == 47)
						map.showMapThree();
					else if (nowPos == 3)
						map.showMapTwo();
					break;
				case MONSTER:
					//ѯ���Ƿ���
					oss << "�Ƿ����ս��? (Y/N)";
					c->changeTextColor('Y', oss);
					//oss.str("");
					clearCin();
					cin >> choice;
					choice=tolower(choice);
					if (choice == 'y') {
						Battle battle(*player);
						battle.beginBattle();
						map.battleFinish(battle.showResult());
						if (player->getNowPos() == 3)
						{
							map.gameEnd();
							//FileStore::StoreGameToFile(map);
							//��ʾ����
							system("cls");
							Map::showMenu();
							return;
						}
						system("pause");
					}
					break;
				default:
					break;
				}
			}
			else if (dir == PLAYERATTR) {
				//����������
				cout << endl;
				player->showInfo();
				system("pause");
			}
			else if (dir == PLAYERBAG) {
				//�򿪱���
				cout << endl;
				oss << "����:";
				c->changeTextColor('Y', oss);
				//oss.str("");
				player->showBag();
				system("pause");

			}
			else if (dir == MAINMENUE) {
				//�ص����˵�
				//�浵
				FileStore::StoreGameToFile(map);
				//��ʾ����
				system("cls");
				Map::showMenu();
				return;
			}
			else {
				throw Error("��������");
			}

		}
		catch (Error &ex) {
			cout << ex.what() << endl;
		}
	} while (true);
}

void Command::wareshop(Map &map,Player *player)
{
	Container *wareshop = map.getWareshop();//map �����ֿ��Ա�����زֿ�ָ��
	int choice;
	do
	{
		cout << "�ֿ�������" << wareshop->getNowSize() << "/" << wareshop->getTotalSize() << endl;
		cout << "�ֿ���Ʒ��" << endl;
		wareshop->showGoods();
		if (!wareshop->getNowSize())
			cout << "��" << endl;
		cout << "1.ȡ����Ʒ  2.�����Ʒ  3.�뿪" << endl;
		int number;
		cout << "��ѡ��";
		clearCin();
		cin >> choice;

		try
		{
			if (choice == 1) {
				cout << "������ȡ����Ʒ���,ֻ������һ����Ʒ��" << endl;
				cout << "�����룺";
				clearCin();
				cin >> number;
				if (number > wareshop->getNowSize() && number>0)
					throw Error("��������ȷ����Ʒ��ţ�");
				Item *item = wareshop->getItemByIndex(number - 1);
				//�ֿ���������Ʒ�����ڱ��������ж��Ƿ���װ����
				if (player->pushBag(item)) {
					wareshop->remove(item);
					cout << item->getId() << "�ɹ�������ı�����" << endl;
				}
				else {
					cout << "�������ˣ������Լ��붫��!" << endl;
				}
			}
			else if (choice == 2) {
				if (wareshop->getNowSize() >= wareshop->getTotalSize()) {
					cout << "�ֿ��������ܴ����Ʒ���Ƿ�����Ʒ��Y/N��";
					char yesOrNo;
					clearCin();
					cin >> yesOrNo;
					yesOrNo=tolower(yesOrNo);
					if (yesOrNo == 'y') {
						cout << "�����붪����Ʒ���,ֻ������һ����Ʒ��" << endl;
						cout << "�����룺";
						clearCin();
						cin >> number;
						if (number > wareshop->getNowSize() && number>0)
							throw Error("��������ȷ����Ʒ��ţ�");
						Item *item = wareshop->getItemByIndex(number - 1);
						wareshop->remove(item);
						cout << item->getId() << "�Ѿ���������" << endl;
					}
				}
				else {
					cout << "������Ʒ:";
					Container *bag = player->getBag();
					bag->showGoods();
					if (bag->getNowSize()) {
						cout << "�����������Ʒ���,ֻ������һ����Ʒ��" << endl;
						cout << "�����룺";
						clearCin();
						cin >> number;
						if (number > bag->getNowSize() && number>0)
							throw Error("��������ȷ����Ʒ��ţ�");
						Item *item = bag->getItemByIndex(number - 1);
						//����ֿ⣬��������
						wareshop->push(item);
						player->removeBag(item);
						cout << item->getId() << "�ɹ�������Ĳֿ⣡" << endl;
					}
					else {
						cout << "��" << endl;
					}
				}

			}
			else if(choice!=3) {
				throw Error("��������ȷ�Ĺ��ܣ�");
			}
		}
		catch (Error &ex)
		{
			cout << ex.what() << endl;
		}
		Sleep(1000);
		system("cls");
		map.showNowposMap();
	} while (choice!=3);
}

void Command::weapon(Player * player)
{

	int choice;
	do
	{
		cout << "��ӭ����������~" << endl;
		cout << "1.����  2.�뿪" << endl;
		clearCin();
		cout << "ѡ��:";
		cin >> choice;
		try {
			if (choice == 1) {
				cout << "��Ʒ�嵥" << endl;
				for (int i = 1; i <= SHOPLISTCOUNT; i++)
					cout << i << "." << SHOPLIST[i - 1] << "\t\t";
				cout << endl;
				cout << "������Ҫ������������:";
				int number;
				clearCin();
				cin >> number;
				if (number > 0 && number <= SHOPLISTCOUNT) {
					cout << "�������";
					int  money;
					clearCin();
					cin >> money;
					if (money<0 || money>player->getMoney()) {
						ostringstream oss;
						oss << "����Ǯ�����ˣ����� " << player->getMoney() << " ��";
						throw Error(oss.str());
					}
					else {
						//������һ���ն���Ȼ��ֵ����
						Equipment *weapon=new Equipment();
						weapon->initEquipment(number-1, money);
						//�õ�һ��������װ��,���뱳��
						//�ж��Ƿ�ŵĽ�ȥ
						Container *bag = player->getBag();
						if (!player->pushBag(weapon)) {
							cout << "��ı������ˣ������Թ���";
							char yOn;
							cout << "�Ƿ��ӵ���Ʒ(Y/N):" ;
							clearCin();
							cin >> yOn;
							yOn=tolower(yOn);
							if (yOn == 'y') {
								cout << "��ı�����Ʒ��";
								bag->showGoods();
								if (bag->getNowSize()) {
									cout << "��ѡ��������Ʒ���:";
									int number;
									clearCin();
									cin >> number;
									if (number > 0 && number < bag->getNowSize()) {
										Item *item = bag->getItemByIndex(number - 1);
										player->removeBag(item);
										cout << item->getId() << " �����ɹ���" << endl;

									}
									else {
										throw Error("�����������Ʒ��ţ�");
									}
								
								}
								else {
									cout << "��" << endl;
								}
							}
						}
						else {
							cout << "����ɹ��� " << endl;
							weapon->showInfo();
							player->setMoney(player->getMoney() - money);
						}

					}
				}
				else
					throw Error("���������������ţ�");
			}
			else if (choice != 2)
				throw Error("��������ȷ�Ĺ��ܣ�");
		}
		catch (Error &ex) {
			cout << ex.what() << endl;
		}
		Sleep(1000);
		system("cls");
	} while (choice!=2);
}

void Command::hospital(Player * player)
{
	int choice;
	do
	{
	cout << "��ӭ������٢��ҽ�ݣ��������㽫���Իָ�����ֵ������ֵ!" << endl;
		cout << "1.�ָ�����ֵ 2.�ָ�����ֵ 3.�뿪" << endl;
		cout << "�����빦��:";
		cin >> choice;
		try
		{
			if (choice == 3) break;
			cout << "������:";
			int money;
			cin >> money;
			if (money<0 || money>player->getMoney()) {
				ostringstream oss;
				oss << "��������ȷ���" << "�������� " << player->getMoney() << endl;
				throw Error(oss.str());
			}
			double proportion = money % 99 / 100.0;
			if (choice == 1) {
				player->setLife(static_cast<int>(ceil( player->getLife()*(1+proportion))));
				if (player->getLife() > MAXLIFE)
					player->setLife(MAXLIFE);
				player->setMoney(player->getMoney() - money);
			}
			else if (choice == 2) {
				player->setEnergy(static_cast<int>(ceil(player->getEnergy()*(1+proportion))));
				if (player->getEnergy() > MAXLIFE)
					player->setEnergy(MAXLIFE);
				player->setMoney(player->getMoney() - money);
			}
			else if (choice != 3)
				throw Error("��������ȷ��ѡ��");
			cout << "���״̬��" << endl;;
			player->showInfo();
		}
		catch (Error &ex)
		{
			cout << ex.what() << endl;
		}
		Sleep(1000);
		system("cls");
	} while (choice!=3);
}

void Command::clearCin()
{
	//����������ĳ�����Ϣ
	cin.clear();
	//�������������Ч������Ϣ

	// numeric_limits<streamsize>::max() �������뻺��Ĵ�С��
	// ignore �����ڴ˽����������е�������ա�
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	//system("pause");
	//system("cls");

}
