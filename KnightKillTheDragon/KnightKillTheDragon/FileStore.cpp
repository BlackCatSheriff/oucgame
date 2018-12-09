#include "FileStore.h"
#include "Container.h"
#include "Player.h"
#include "Error.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
void FileStore::StoreGameToFile(Map & m) {

	ofstream ofsMap("Map.dat", ios::binary);
	if (!ofsMap) {
		throw Error("�浵ʧ��,������!");
	}

	//��player������
	Player *p = m.getPlayer();
	PlayerAttr playerattr = {
		p->getName(),
		p->getPos_x(),p->getPos_y(),
			p->getLife(),
			p->getPower(),
			p->getExp(),
			p->getProtectPower(),
			p->getLevel(),
			p->getMoney(),
			p->getEnergy(),
			p->getMiss(),
			p->getMoveSpeed(),
			p->getNowPos()
	};
	int saveMap[MAPROW][MAPCOLUMN];
	m.getMapData(saveMap);
	//Container ������ʵ�ִ�ȡ
	int bagListCnt = m.getBag().getNowSize();
	int wareListCnt = m.getWare()->getNowSize();
	Equipment *bagList = new Equipment[bagListCnt];
	Equipment *wareList = new Equipment[wareListCnt];
	//init bagList
	for (int i = 0; i < bagListCnt; i++) {
		Item * it = m.getBag().getItemByIndex(i);
		Equipment *eq = dynamic_cast<Equipment*>(it);
		string name = eq->getId();
		int value = eq->getValue();
		int power = eq->getPower();
		int protectPower = eq->getProtectPower();
		int movePower = eq->getMovePower();
		int consu = eq->getConsume();
		bagList[i] = Equipment(name,value,power,consu,protectPower,movePower);
	}
	//init wareList
	for (int i = 0; i < wareListCnt; i++) {
		Item * it = m.getWare()->getItemByIndex(i);
		Equipment *eq = dynamic_cast<Equipment*>(it);
		string name = eq->getId();
		int value = eq->getValue();
		int power = eq->getPower();
		int protectPower = eq->getProtectPower();
		int movePower = eq->getMovePower();
		int consu = eq->getConsume();
		wareList[i] = Equipment(name, value, power, consu, protectPower, movePower);
	}

	AllDataSize allDataSize = { sizeof(playerattr),sizeof(Equipment)*bagListCnt ,sizeof(Equipment)*wareListCnt ,sizeof(saveMap) };

	//����������С
	ofsMap.write(reinterpret_cast<char *>(&allDataSize), sizeof(allDataSize));

	ofsMap.write(reinterpret_cast<char *>(&playerattr), allDataSize.playerAttr);

	//��bag
	//ofsMap.write(reinterpret_cast<char *>(m.getPlayer()->getBag()), sizeof(*m.getPlayer()->getBag()));
	ofsMap.write(reinterpret_cast<char *>(bagList),allDataSize.bag);
	
	//�� �ֿ�
	//ofsMap.write(reinterpret_cast<char *>(m.getWareshop()), sizeof(*m.getWareshop()));
	ofsMap.write(reinterpret_cast<char *>(wareList), allDataSize.ware);
	
	//�� map ��ͼ����

	ofsMap.write(reinterpret_cast<char *>(saveMap), sizeof(saveMap));
	ofsMap.close();
}


Map *FileStore::ReadGameFile()
{

	ifstream ifsMap("Map.dat", ios::binary);
	if (!ifsMap) {
		throw Error("����ʧ��,������!");
	}
	AllDataSize alldatasize;
	PlayerAttr playerattr;
	Container *bag = new Container(BAGCOUNTCAPACITY);
	Container *ware = new Container(WARESHOPCAPACITY);
	int mapData[MAPROW][MAPCOLUMN];
	//������������С
	ifsMap.read(reinterpret_cast<char *>(&alldatasize), sizeof(AllDataSize));

	Equipment *bagList = new Equipment[alldatasize.bag];
	Equipment *wareList = new Equipment[alldatasize.ware];


	//����Player ����
	ifsMap.read(reinterpret_cast<char *>(&playerattr), alldatasize.playerAttr);
	//���� BAG
	//ifsMap.read(reinterpret_cast<char *>(bag), alldatasize.bag);
	ifsMap.read(reinterpret_cast<char *>(bagList), alldatasize.bag);
	//���� wareshop
	//ifsMap.read(reinterpret_cast<char *>(ware), alldatasize.ware);
	ifsMap.read(reinterpret_cast<char *>(wareList), alldatasize.ware);
	//�����ͼ����
	ifsMap.read(reinterpret_cast<char *>(mapData), alldatasize.mapData);
	ifsMap.close();

	//init bag
	for (unsigned i = 0; i < alldatasize.bag/sizeof(Equipment); i++) {
		bag->push(&bagList[i]);
	}
	//init ware
	for (unsigned i = 0; i < alldatasize.ware / sizeof(Equipment); i++) {
		ware->push(&wareList[i]);
	}
	//���� Player
	Player::deletePlayer();
	Player *player = Player::creatPlayer(playerattr.name, playerattr.pos_x, playerattr.pos_y, playerattr.life, playerattr.power, playerattr.exp, playerattr.protectPower,
		playerattr.level, playerattr.money, playerattr.energy, playerattr.miss, playerattr.moveSpeed, playerattr.nowPos, *bag);

	//�����ͼ
	Map *map=new Map(*player, *ware, mapData);
	return map;

}
