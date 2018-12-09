#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Player.h"
#include "ConstTable.h"
#include "Container.h"
#include "Command.h"
#include "FileStore.h"
#include "Utill.h"
#include "ColorContainer.h"
#include "ColorSys.h"
#include "Error.h"
using namespace std;
int main() {

	//չʾ��ʼ����
	int type;
	Utill::HideCursor();
	try
	{
		while (true)
		{
			Map::showMenu();
			cout << "�����빦��:";
			cin >> type;
			if (type == 1)
				Command::newGame();
			else if (type == 2) {
				//����map ����
				try
				{
					Map *map = FileStore::ReadGameFile();
					int mapData[MAPROW][MAPCOLUMN];
					map->getMapData(mapData);
					Command::newerCountry(map->getPlayer(), mapData, map->getWare());
				}
				catch (Error &ex)
				{
					ColorContainer *c = new ColorSys();
					ostringstream oss;
					oss << ex.what() << endl;
					c->changeTextColor('R', oss);
					oss << "�뿪ʼ�µ���Ϸ��" << endl;
					c->changeTextColor('R', oss);
					delete c;
				}
			}
			else if (type == 3) {
				//�򿪶�ά��
				system("QR.png");
				cout << "���ص� Map.dat ���Ƶ���Ϸ��Ŀ¼���ɣ�" << endl;
				system("pause");
			}
			else
				exit(0);
		}


	}
	catch (const std::exception&)
	{
		ColorContainer *c = new ColorSys();
		ostringstream oss;
		oss << "\n��Ϸ�ļ��仵�������´�!��ʼ�µ����̣�\t���򼴽��˳�..." << endl;
		c->changeTextColor('R', oss);
		Sleep(1500);
		delete c;
		exit(0);
	}
	return 0;
};