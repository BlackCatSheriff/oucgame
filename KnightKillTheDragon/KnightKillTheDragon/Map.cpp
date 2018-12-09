#include "Map.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ctime>
#include <string>
#include "ConstTable.h"
#include "Utill.h"
using namespace std;


Map::Map(Player& p,Container &wareshop) :man(p), wareshop(wareshop) {}

Map::Map(Player & p, Container & wareshop, int(&backupMap)[MAPROW][MAPCOLUMN]) : man(p), wareshop(wareshop)
{
	memcpy(mapData, backupMap, sizeof(backupMap));
}

void Map::showMapOne() {
	char* file;
	int nowPos = man.getNowPos();
	if (nowPos == 0)  //����
	{
		file = "MapOneData.txt";
		this->DataRead(file);  //��ȡ��ͼ����
		man.setNowPos(1);
	}
	else if (nowPos == 2)   //��2��ͼ��1��ͼ
	{
		file = "MapOneData.txt";
		this->DataRead(file);  //��ȡ��ͼ����
		man.setNowPos(1);
		man.move(5, 47);   //������
	}
	else
	{
		file = "MapOneData.txt";
		this->DataRead(file);  //��ȡ��ͼ����
	}
	file = "MapOne.txt";
	this->show(man.getPos_x(), man.getPos_y(), file);  //��ȡ��ͼ��ʾ����
}

void Map::showMapTwo() {
	char* file;
	int nowPos = man.getNowPos();
	if (nowPos == 1) //��1��ͼ��2��ͼ
	{
		file = "MapTwoData.txt";
		this->DataRead(file);	//��ȡ������ͼ��Ϣ
		man.setNowPos(2);
		man.move(5, 3);	//������
		this->monserGenerator();	//���ɹ����޸ĵ�ͼ��Ϣ
	}
	if (nowPos == 3) //��3��ͼ��2��ͼ
	{
		file = "MapTwoData.txt";
		this->DataRead(file);	//��ȡ������ͼ��Ϣ
		man.setNowPos(2);
		man.move(5, 46);	//������
		this->monserGenerator();	//���ɹ����޸ĵ�ͼ��Ϣ
	}
	if(nowPos == 4)
	{
		file = "MapTwoData.txt";
		this->DataRead(file);	//��ȡ������ͼ��Ϣ
		man.setNowPos(2);
		this->monserGenerator();	//���ɹ����޸ĵ�ͼ��Ϣ
	}
	file = "MapTwo.txt";
	this->showMonster(man.getPos_x(),man.getPos_y(), file);
}

void Map::showMapThree() {
	char* file;
	int nowPos = man.getNowPos();
	file = "MapThreeData.txt";
	this->DataRead(file);  //��ȡ��ͼ����
	for (int i = 0; i < 11; i++)
		mapData[i][15] = -1;
	if (nowPos == 2)  //��2��ͼ��3��ͼ
	{
		man.setNowPos(3);
		man.move(5, 3);		//������
	}
	file = "MapThree.txt";
	this->show(man.getPos_x(), man.getPos_y(), file); //��ȡ��ͼ��ʾ����
}

int Map::mapMove(char dir) {
	int x = man.getPos_x();
	int y = man.getPos_y();
	Utill::gotoxy(x, y);
	putchar(' ');
	switch (dir) {
	case 'w':
		x--;
		if (mapData[x][y])
		{
			man.move(x, y);
			Utill::gotoxy(x, y);
			putchar('o');
			//showNowposMap();
			Utill::gotoxy(13, 0);
			return mapData[x][y];
		}
		Utill::gotoxy(x+1, y);
		putchar('o');
		Utill::gotoxy(13, 0);
		return mapData[x+1][y];
	case 'a':
		y--;
		if (mapData[x][y])
		{
			man.move(x, y);
			//showNowposMap();
			Utill::gotoxy(x, y);
			putchar('o');
			Utill::gotoxy(13, 0);
			return mapData[x][y];
		}
		//showNowposMap();
		Utill::gotoxy(x, y+1);
		putchar('o');
		Utill::gotoxy(13, 0);
		return mapData[x][y+1];
	case 's':
		x++;
		if (mapData[x][y])
		{
			man.move(x, y);
			//showNowposMap();
			Utill::gotoxy(x, y);
			putchar('o');
			Utill::gotoxy(13, 0);
			return mapData[x][y];
		}
		//showNowposMap();
		Utill::gotoxy(x+1, y);
		putchar('o');
		Utill::gotoxy(13, 0);
		return mapData[x + 1][y];
	case 'd':
		y++;
		if (mapData[x][y])
		{
			man.move(x, y);
			//showNowposMap();
			Utill::gotoxy(x, y);
			putchar('o');
			Utill::gotoxy(13, 0);
			return mapData[x][y];
		}
		//showNowposMap();
		Utill::gotoxy(x, y-1);
		putchar('o');
		Utill::gotoxy(13, 0);
		return mapData[x][y-1];
	default:
		break;
	}
	return mapData[x][y];
}

void Map::showMenu() {
	system("cls");
	Utill::changeForeground('R');
	char* file = "WelcomeMenu.txt";
	ifstream fin(file);   //��ȡ����ʾ��ӭ����
	char data[100];
	for (int i = 0; i < 18; i++) {
		fin.getline(data, 100);
		cout << data << endl;
		if (i == 13)
			Utill::ForegroundRGS();
	}
	Utill::ForegroundALL();
}

Container * Map::getWareshop() const
{
	return &wareshop;
}

void Map::DataRead(char *file) {  //��ȡ��ͼ������Ϣ
	ifstream ifs(file);
	int i = 0;
	if (ifs) {
		for (int i = 0; i < MAPROW; i++){
			string str;
			getline(ifs, str);
			for (int j = 0; j < MAPCOLUMN; j++){
				mapData[i][j] = (int)str[j]-48;
			}
		}
	}
}

void Map::show(char* file) {
	system("cls");
	ifstream fin(file);
	string str;
	if (fin) {
		for (int i = 0; i < MAPROW; i++)
		{
			getline(fin, str);
			cout << str << endl;
		}
	}
	fin.close();
}

void Map::show(int x, int y, char* file) 
{
	system("cls");
	ifstream fin(file);
	string str;
	if (fin) {
		for (int i = 0; i < MAPROW; i++)
		{
			getline(fin, str);
			if (x == i)
				str[y] = 'o';
			cout << str << endl;
		}
	}
	fin.close();
}

void Map::showMonster(int x, int y, char * file)
{
	system("cls");
	ifstream fin(file);
	string str;
	if (fin) {
		for (int i = 0; i < MAPROW; i++)
		{
			getline(fin, str);
			for (int j = 0; j < MAPCOLUMN; j++)
				if (mapData[i][j] == -1)
					str[j] = 'x';
			if (x == i)
				str[y] = 'o';
			cout << str << endl;
		}
	}
	fin.close();
}

void Map::gameEnd()
{
	system("cls");
	Utill::ForegroundGBS();
	cout << "��ϲ��ɹ������˶�����" << endl;
	Sleep(800);
	cout << "�������Ӷ����ĳ�Ѩ���ȳ����������ص��������ߣ�" << endl;
	Sleep(500);
	cout << "����";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << "." << endl;
	Sleep(2000);
	Utill::ForegroundRGS();
	cout << "���ð�ջ�û�н���!" << endl;
	Sleep(2000);
	Utill::ForegroundALL();
	system("cls");

}
void Map::battleFinish(bool status) {
	if (status) {  //ս��ʤ��  ��������
		int manPosx = man.getPos_x();
		int manPosy = man.getPos_y();
		mapData[manPosx][manPosy] = 1;
	}
	else  //ս��ʧ��  ��������
	{
		man.setNowPos(1); //��ʼ��ͼ1
		man.move(BORNX, BORNY);  //�����ڳ�ʼ��ͼλ��
	}
}

void Map::monserGenerator() {
	srand((unsigned)time(NULL));
	int monPosx, monPosy;
	int cnt(0); //��¼�ѳɹ����ɵĹ�������
	while(true)
	{
		monPosx = (rand() % 11) + 1;
		monPosy = (rand() % 48) + 1;
		if (mapData[monPosx][monPosy] == 1)
		{
			mapData[monPosx][monPosy] = -1;
			cnt++;
		}
		if (cnt == MONSTERMAXNUM)
			return;
	}
}

void Map::showNowposMap()
{
	int nowPos = man.getNowPos();
	if (nowPos == 1 || !nowPos)
	{
		showMapOne();
	}
	else if (nowPos == 2 || nowPos ==4)
	{
		showMapTwo();
	}
	else if (nowPos == 3)
	{

		showMapThree();
	}
	else
		return;
}

void Map::setManPos(int x)
{
	man.setNowPos(x);
}

Container & Map::getBag()
{
	return *man.getBag();
}

Container * Map::getWare()
{
	return &(this->wareshop);
}

void Map::getMapData(int backupMapData[][MAPCOLUMN])
{
	memcpy(backupMapData, mapData, sizeof(mapData));
}

void Map::setMapData(int(&backupMap)[MAPROW][MAPCOLUMN])
{
	memcpy(mapData, backupMap, sizeof(backupMap));
}


int Map::getManPos()
{
	return man.getNowPos();
}

Player * Map::getPlayer()
{
	return &man;
}

