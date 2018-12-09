#ifndef MAP_H
#define MAP_H
#include "Player.h"
#include "Container.h"
#include "ConstTable.h"
class Map {
public:
	Map(Player& p,Container &wareshop);
	Map(Player& p, Container &wareshop,int (&backupMap)[MAPROW][MAPCOLUMN]);
	void showMapOne();  //��ͼ1
	void showMapTwo();	//��ͼ2
	void showMapThree();  //��ͼ3
	int mapMove(char dir);  //�ƶ�
	void battleFinish(bool status);
	static void showMenu();
	Container *getWareshop()const;//��ȡ�ֿ�
	void showNowposMap();//���µ�ǰ��ͼ
	Player *getPlayer();//��ȡplayer
	int getManPos();
	void setManPos(int x);
	Container& getBag();	//���ر���
	Container* getWare();	//���زֿ�
	void getMapData(int backupMapData[][MAPCOLUMN]);//���ص�ͼ���ݵ�������
	void setMapData(int(&backupMap)[MAPROW][MAPCOLUMN]);//���ö����ͼ����
	void gameEnd(); //��ܶ������

private:
	void DataRead(char *file);
	void show(char* file);   //��ȡfile�еĵ�ͼ���ݲ���ʾ
	void show(int x, int y, char* file);  //��ʾ��ͼ��(x,y)�������ڵ�ͼ�ϵ�����  ����
	void showMonster(int x, int y, char* file); 
	void monserGenerator();	//�ڵ�ǰ��ͼ���ɹ���
	int mapData[MAPROW][MAPCOLUMN];   //��ͼ����   0ǽ 1· 2�ɷ���NPC 3�� -1����
	Player& man;
	Container &wareshop;
};

#endif
