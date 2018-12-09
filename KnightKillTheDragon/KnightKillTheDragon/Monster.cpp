#include "Monster.h"
#include "ConstTable.h"
#include <iostream>
#include <ctime>
using namespace std;
Monster::Monster(Equipment *equipment) : equipment(equipment) {
	
}

Monster::~Monster()
{
}

void Monster::showInfo() const
{
	cout << "HP:" << getLife() << "\t\t" << "������:" << getPower() << endl
		<< "������:" << getProtectPower() << "\t" << "�ȼ�:" << getLevel() << endl;

}

Equipment *Monster::getItem() const
{
	return this->equipment;
}

